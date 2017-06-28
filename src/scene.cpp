/**
 * The MIT License (MIT)
 *
 * Copyright (C) 2012 by INdT
 * Copyright (C) 2014 Bacon2D Project
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @author Rodrigo Goncalves de Oliveira <rodrigo.goncalves@openbossa.org>
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

#include "scene.h"

#include "game.h"
#include "bacon2dlayer.h"
#include "viewport.h"

#include <QtCore/QtGlobal>
#include <QtQml/QQmlEngine>

#include "../../3rdparty/qml-box2d/box2dbody.h"

/*!
  \qmltype Scene
  \inqmlmodule Bacon2D
  \inherits Item
  \brief The root view in the Game.

  The Scene component is the root view for the \l Game.

  The size of the Scene can be larger than the size of the \l Game, accessible 
  using a \l Viewport.  The \l Viewport provides xOffset and yOffset properties
  which can be used to control movement of the Viewport.

  Example usage:
  \qml
   import QtQuick 2.0
   import Bacon2D 1.0

   Game {
       id: game
       width: 800
       height: 600

       Scene {
           id: scene
           width: 1200
           height: 800
           physics: true
           viewport: Viewport {
               yOffset: player.y - 100
           }
           Entity {
               id: player
           }
       }
   }
   \endqml
*/
Scene::Scene(Game *parent)
    : QQuickItem(parent)
    , m_running(false)
    , m_viewport(0)
    , m_game(parent)
    , m_world(0)
    , m_physics(false)
    , m_debugDraw(0)
    , m_debug(false)
    , m_enterAnimation(0)
    , m_exitAnimation(0)
{
    setVisible(false);

    connect(this, SIGNAL(worldChanged()), SLOT(onWorldChanged()));
}

Scene::~Scene()
{
}

void Scene::updateEntities(QQuickItem *parent, const int &delta)
{
    QQuickItem *item;
    foreach (item, parent->childItems()) {
        if (Entity *entity = qobject_cast<Entity *>(item))
            entity->update(delta);
        else if (Bacon2DLayer *layer = qobject_cast<Bacon2DLayer *>(item))
            layer->update(delta);
    }
}

void Scene::update(const int &delta)
{
    if (!m_running) // TODO: stop Qt animations as well
        return;

    updateEntities(this, delta);
}

/*!
  \qmlproperty Animation Scene::enterAnimation
  \brief Animation that will be triggered when the Scene become the current Scene.

  While Scene is executing the enter animation, running, enabled and focus
  properties will be set to false and there will be no user interaction until
  the animation is completed. It is also important to now that properties changed
  during enter and exit animation will be persisted when the Scene become the current Scene.

  Example usage:
  \qml
   import QtQuick 2.0
   import Bacon2D 1.0

   Game {
       id: game
       width: 800
       height: 600

       Scene {
           id: scene
           width: 300
           height: 300

           enterAnimation: NumberAnimation{ target:scene; property: "x"; from: 500; to: 0; duration: 300}
           enterAnimation: NumberAnimation{ target:scene; property: "x"; from: 0; to: 500; duration: 300}
       }
   }
   \endqml
 */
QObject *Scene::enterAnimation() const
{
    return m_enterAnimation;
}

void Scene::setEnterAnimation(QObject *animation)
{
    const QMetaObject *meta = animation->metaObject();
    do{
        if(QString("QQuickAbstractAnimation") == QString::fromLocal8Bit(meta->className())){
            m_enterAnimation = animation;
            break;
        }
    }
    while( (meta = meta->superClass()) != 0);
}

/*!
  \qmlproperty Animation Scene::exitAnimation
  \brief Animation that will be triggered when the Scene exits the screen.
  While Scene is executing the exit animation, running, enabled and focus
  properties will be set to false and there will be no user interaction until
  the animation is completed, but the Scene continue to be visible untile the animation ends.
  It is also important to now that properties changed by the enter and exit animation will be persisted when the Scene become the current Scene.

  Example usage:
  \qml
   import QtQuick 2.0
   import Bacon2D 1.0

   Game {
       id: game
       width: 800
       height: 600

       Scene {
           id: scene
           width: 300
           height: 300

           enterAnimation: NumberAnimation{ target:scene; property: "x"; from: 500; to: 0; duration: 300}
           enterAnimation: NumberAnimation{ target:scene; property: "x"; from: 0; to: 500; duration: 300}
       }
   }
   \endqml
 */
QObject *Scene::exitAnimation() const
{
    return m_exitAnimation;
}

void Scene::setExitAnimation(QObject *animation)
{
    const QMetaObject *meta = animation->metaObject();
    do{
        if(QString("QQuickAbstractAnimation") == QString::fromLocal8Bit(meta->className())){
            m_exitAnimation = animation;
            break;
        }
    }
    while( (meta = meta->superClass()) != 0);
}

/*!
 * \qmlproperty bool Scene::running
 * \brief The current running state of Scene
 */
bool Scene::running() const
{
    return m_running;
}

void Scene::setRunning(const bool &running)
{
    if (m_running == running)
        return;

    m_running = running;
    if (m_physics && m_world)
        m_world->setRunning(m_running);

    emit runningChanged();
}

/*!
 * \qmlproperty Viewport Scene::viewport
 * \brief Holds the a reference to the Viewport for the current Scene.
 */
Viewport *Scene::viewport() const
{
    return m_viewport;
}

void Scene::setViewport(Viewport *viewport)
{
    if (m_viewport == viewport)
        return;

    m_viewport = viewport;
    m_viewport->setScene(this);

    emit viewportChanged();
}

/*!
 * \qmlproperty Game Scene::game
 * \brief Holds the a reference to the Game that contains the Scene.
 */
Game *Scene::game() const
{
    return m_game;
}

void Scene::setGame(Game *game)
{
    m_game = game;
}

/*!
 * \qmlproperty World Scene::world
 * \brief Holds the a reference to the World attached to the Scene.
 */
Box2DWorld *Scene::world() const
{
    return m_world;
}

void Scene::createWorld()
{
    if (m_physics && !m_world) {
        m_world = new Box2DWorld(this);
        m_world->setRunning(m_running);
        //force debug draw update
        setDebug(m_debug);
        emit worldChanged();
    }
}

/*!
 * \qmlproperty bool Scene::physics
 * \brief This property determines if the Scene contains a Box2D physics world
 */
bool Scene::physics() const
{
    return m_physics;
}

void Scene::setPhysics(const bool &physics)
{
    if (m_physics == physics)
        return;

    m_physics = physics;

    if (m_physics && !m_world) {
        createWorld();
    }
}

/*!
 * \qmlproperty bool Scene::debug
 * \brief This property allows toggling debug mode, if enabled along with 
   physics, an overlay showing fixtures will be shown.
 */
bool Scene::debug() const
{
    return m_debug;
}

void Scene::setDebug(const bool &debug)
{
    if (debug && m_physics && !m_debugDraw){
        m_debugDraw = new Box2DDebugDraw(this);
        m_debugDraw->setWorld(m_world);
        m_debugDraw->setParentItem(this);
        if (this->childItems().indexOf(m_debugDraw) != (this->childItems().length()-1))
            m_debugDraw->stackAfter(this->childItems().last());
        m_debugDraw->setOpacity(0.3);
        m_debugDraw->setWidth(width());
        m_debugDraw->setHeight(height());
        m_debugDraw->setVisible(true);
    }

    if(!debug && m_debugDraw) {
        m_debugDraw->setVisible(false);
        m_debugDraw->deleteLater();
        m_debugDraw = 0;
    }

    if(debug != m_debug){
        m_debug = debug;
        emit debugChanged();
    }
}

/* These are wrapped around Box2DWorld */

float Scene::timeStep() const
{
    if (!m_world)
        return 0;

    return m_world->timeStep();
}

void Scene::setTimeStep(float timeStep)
{
    if (!m_world)
        return;

    m_world->setTimeStep(timeStep);
}

int Scene::velocityIterations() const
{
    if (!m_world)
        return 0;

    return m_world->velocityIterations();
}

void Scene::setVelocityIterations(int iterations)
{
    if (!m_world)
        return;

    m_world->setVelocityIterations(iterations);
}

int Scene::positionIterations() const
{
    if (!m_world)
        return 0;

    return m_world->positionIterations();
}

void Scene::setPositionIterations(int iterations)
{
    if (!m_world)
        return;

    m_world->setPositionIterations(iterations);
}

/*!
  \qmlproperty QPointF Scene::gravity
  \brief This property holds the global gravity vector.
  
   The gravity property only applies if physics is enabled.
*/
QPointF Scene::gravity() const
{
    if (!m_world)
        return QPointF(0, 0);

    return m_world->gravity();
}

void Scene::setGravity(const QPointF &gravity)
{
    if (!m_world)
        return;

    m_world->setGravity(gravity);
}

bool Scene::autoClearForces() const
{
    if (!m_world)
        return false;

    return m_world->autoClearForces();
}

void Scene::setAutoClearForces(bool autoClearForces)
{
    if (!m_world)
        return;

    m_world->setAutoClearForces(autoClearForces);
}

Box2DProfile *Scene::profile() const
{
    if (!m_world)
        return NULL;

    return m_world->profile();
}

/*!
  \qmlproperty float Scene::pixelsPerMeter
  \brief This property holds the number of pixels per meter.

   The physics world uses meters to measure velocity, movement, etc.  This
   property only applies with physics enabled.
*/
float Scene::pixelsPerMeter() const
{
    if (!m_world)
        return 0;

    return m_world->pixelsPerMeter();
}
void Scene::setPixelsPerMeter(float pixelsPerMeter)
{
    if (!m_world)
        return;

    m_world->setPixelsPerMeter(pixelsPerMeter);
}

void Scene::step() 
{
    if (!m_world)
        return;

    m_world->step();
}

void Scene::clearForces()
{
    if (!m_world)
        return;

    m_world->clearForces();
}

/*!
  \qmlmethod void Scene::rayCast(RayCast *rayCast, const QPointF &point1, const QPointF &point2)
  \brief The rayCast method can be used to do line-of-sight checks, fire guns, etc.
 
   The rayCast method is only useful with physics is enabled.
*/
void Scene::rayCast(Box2DRayCast *rayCast, const QPointF &point1, const QPointF &point2)
{
    if (!m_world)
        return;

    m_world->rayCast(rayCast, point1, point2);
}
/* End wrapped Box2DWorld  */

void Scene::initializeEntities(QQuickItem *parent)
{
    QQuickItem *child;
    foreach (child, parent->childItems()) {
        if (Entity *entity = dynamic_cast<Entity *>(child)) {
            entity->setScene(this);
        } else if (Bacon2DLayer *layer = dynamic_cast<Bacon2DLayer *>(child)) {
            layer->setScene(this);
        }

        if (m_physics && m_world) {
            foreach (Box2DBody *body, child->findChildren<Box2DBody *>(QString(), Qt::FindDirectChildrenOnly)) {
                body->setWorld(m_world);
            }
        }

        initializeEntities(child);
    }
}

void Scene::componentComplete()
{
    QQuickItem::componentComplete();
    initializeEntities(this);

    if (m_world)
        m_world->componentComplete();

    if (m_viewport)
        m_viewport->setScene(this);
}

void Scene::itemChange(ItemChange change, const ItemChangeData &data)
{

    if (isComponentComplete() && change == ItemChildAddedChange) {
        QQuickItem *child = data.item;
        if (Entity *entity = dynamic_cast<Entity *>(child)) {
            entity->setScene(this);
        } else if (Bacon2DLayer *layer = dynamic_cast<Bacon2DLayer *>(child)) {
            layer->setScene(this);
        }

        if (m_physics && m_world) {
            foreach (Box2DBody *body, child->findChildren<Box2DBody *>(QString(), Qt::FindDirectChildrenOnly)) {
                body->setWorld(m_world);
            }
        }

        initializeEntities(child);
    }

    QQuickItem::itemChange(change, data);
}

void Scene::onWorldChanged()
{
    if (m_world) {
        /* Wrap signals from Box2DWorld */
        connect(m_world, SIGNAL(preSolve(Box2DContact *)), this, SIGNAL(preSolve(Box2DContact *)));
        connect(m_world, SIGNAL(postSolve(Box2DContact *)), this, SIGNAL(postSolve(Box2DContact *)));
        connect(m_world, SIGNAL(timeStepChanged()), this, SIGNAL(timeStepChanged()));
        connect(m_world, SIGNAL(velocityIterationsChanged()), this, SIGNAL(velocityIterationsChanged()));
        connect(m_world, SIGNAL(positionIterationsChanged()), this, SIGNAL(positionIterationsChanged()));
        connect(m_world, SIGNAL(gravityChanged()), this, SIGNAL(gravityChanged()));
        connect(m_world, SIGNAL(autoClearForcesChanged()), this, SIGNAL(autoClearForcesChanged()));
        connect(m_world, SIGNAL(stepped()), this, SIGNAL(stepped()));
        connect(m_world, SIGNAL(pixelsPerMeterChanged()), this, SIGNAL(pixelsPerMeterChanged()));
        /* End wrapped signals from Box2DWorld */

        /* if debug is enabled, create a DebugDraw */
        if (m_debug && !m_debugDraw) {
            m_debugDraw = new Box2DDebugDraw(this);
            emit debugChanged();
        }
    }
}

void Scene::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
    if (newGeometry.isEmpty() || !isComponentComplete() || (newGeometry == oldGeometry))
        return;

    if (m_viewport && m_running) {
        m_viewport->setScene(this);
    }
    if (m_debug && m_debugDraw) {
        emit debugChanged();
    }
}

