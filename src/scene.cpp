/**
 * Copyright (C) 2012 by INdT
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * @author Rodrigo Goncalves de Oliveira <rodrigo.goncalves@openbossa.org>
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

#include "scene.h"

#include "game.h"
#include "layer.h"
#include "box2dcontactlistener.h"
#include "box2dcontact.h"
#include "box2ddebugdraw.h"
#include "box2djoint.h"

#include <QtCore/QtGlobal>

#if QT_VERSION >= 0x050000
#include <QtQml/QQmlEngine>
#else
#include <QtDeclarative/QDeclarativeEngine>
#endif

#include <Box2D/Box2D.h>

static void deleteWorld(b2World *world)
{
    delete world;
}

Scene::Scene(Game *parent)
    : QuasiDeclarativeItem(parent)
    , m_running(true)
    , m_game(parent)
    , m_debug(false)
    , m_world(0)
    , m_gravity(qreal(0), qreal(-10))
    , m_debugDraw(0)
    , m_physicsTimeStep(0.0)
    , m_physicsVelocityIterations(10)
    , m_physicsPositionIterations(10)
{
    setVisible(false);

    const b2Vec2 gravity(m_gravity.x(), m_gravity.y());

    m_world = QSharedPointer<b2World>(new b2World(gravity), deleteWorld);

    ContactListener *contactListener = new ContactListener(this);
    m_world->SetContactListener(contactListener);

    connect(this, SIGNAL(debugChanged()), SLOT(onDebugChanged()));
}

Scene::~Scene()
{
    m_world.clear();
}

void Scene::update(const int &delta)
{
    if (!m_running) // TODO: stop Qt animations as well
        return;

#if QT_VERSION >= 0x050000
    QQuickItem *item;
#else
    QGraphicsItem *item;
#endif
    foreach (item, childItems()) {
        if (Entity *entity = qobject_cast<Entity *>(item))
            entity->update(delta);
        else if (Layer *layer = qobject_cast<Layer *>(item))
            layer->update();

        if (Box2DBase *box2DItem = dynamic_cast<Box2DBase *>(item))
            box2DItem->synchronize();
    }

    m_world->Step(m_physicsTimeStep, m_physicsVelocityIterations, m_physicsPositionIterations);
    if (m_debugDraw)
        m_debugDraw->step();
}

bool Scene::running() const
{
    return m_running;
}

void Scene::setRunning(const bool &running)
{
    if (m_running == running)
        return;

    m_running = running;

    emit runningChanged();
}

Game *Scene::game() const
{
    return m_game;
}

void Scene::setGame(Game *game)
{
    m_game = game;
    if (!m_game)
        return;

    if (!qFuzzyCompare(0.0, m_physicsTimeStep))
        return;

    qreal fps = m_game->fps();
    if (qFuzzyCompare(0.0, fps))
        return;

    m_physicsTimeStep = 1.0 / m_game->fps();
}

bool Scene::debug() const
{
    return m_debug;
}

void Scene::setDebug(const bool &debug)
{
    if (m_debug == debug)
        return;

    m_debug = debug;

    emit debugChanged();
}

void Scene::componentComplete()
{
    QuasiDeclarativeItem::componentComplete();

#if QT_VERSION >= 0x050000
    QQuickItem *item;
#else
    QGraphicsItem *item;
#endif

    QList<Box2DJoint *> jointItems;

    foreach (item, childItems()) {
        if (Entity *entity = dynamic_cast<Entity *>(item))
            entity->setScene(this);

        if (Box2DBase *box2DItem = dynamic_cast<Box2DBase *>(item)) {
            box2DItem->setWorld(m_world);

            if (Box2DJoint *box2DJointItem = dynamic_cast<Box2DJoint *>(item))
                jointItems << box2DJointItem;
            else
                box2DItem->initialize();
        }
    }

    foreach (Box2DJoint *box2DJointItem, jointItems) {
        box2DJointItem->initialize();
    }

    if (m_debugDraw) {
        m_debugDraw->setWidth(width());
        m_debugDraw->setHeight(height());
    }
}

#if QT_VERSION >= 0x050000
void Scene::itemChange(ItemChange change, const ItemChangeData &data)
#else
QVariant Scene::itemChange(GraphicsItemChange change, const QVariant &value)
#endif
{
    if (isComponentComplete() && change == ItemChildAddedChange) {
#if QT_VERSION >= 0x050000
        QQuickItem *child = data.item;
#else
        QGraphicsItem *child = value.value<QGraphicsItem *>();
#endif
        if (Entity *entity = dynamic_cast<Entity *>(child))
            entity->setScene(this);

        if (Box2DBase *box2DBaseItem = dynamic_cast<Box2DBase *>(child)) {
            box2DBaseItem->setWorld(m_world);
            box2DBaseItem->initialize();
        }
    }

#if QT_VERSION >= 0x050000
    QuasiDeclarativeItem::itemChange(change, data);
#else
    return QuasiDeclarativeItem::itemChange(change, value);
#endif
}

b2World *Scene::world() const
{
    return m_world.data();
}

void Scene::setGravity(const QPointF &gravity)
{
    m_gravity = gravity;

    m_world->SetGravity(b2Vec2(gravity.x(), gravity.y()));
}

QPointF Scene::gravity() const
{
    return m_gravity;
}


void Scene::onDebugChanged()
{
    if (m_debugDraw)
        delete m_debugDraw;

    m_debugDraw = new Box2DDebugDraw(this);
    m_debugDraw->setOpacity(0.7);

    m_debugDraw->setWidth(width());
    m_debugDraw->setHeight(height());
}

void Scene::onPostSolve(Box2DContact *contact)
{
    emit contactPostSolve(contact);
}

void Scene::onPreSolve(Box2DContact *contact)
{
    emit contactPreSolve(contact);
}

void Scene::onBeginContact(Box2DContact *contact)
{
    emit contactBegin(contact);
}

void Scene::onEndContact(Box2DContact *contact)
{
    emit contactEnd(contact);
}


qreal Scene::physicsTimeStep() const
{
    return m_physicsTimeStep;
}

void Scene::setPhysicsTimestep(const qreal &physicsTimeStep)
{
    if (m_physicsTimeStep == physicsTimeStep)
        return;

    m_physicsTimeStep = physicsTimeStep;

    emit physicsTimeStepChanged();
}

int Scene::physicsVelocityIterations() const
{
    return m_physicsVelocityIterations;
}

void Scene::setPhysicsVelocityIterations(const int &physicsVelocityIterations)
{
    if (m_physicsVelocityIterations == physicsVelocityIterations)
        return;

    m_physicsVelocityIterations = physicsVelocityIterations;

    emit physicsVelocityIterationsChanged();
}

int Scene::physicsPositionIterations() const
{
    return m_physicsPositionIterations;
}

void Scene::setPhysicsPositionIterations(const int &physicsPositionIterations)
{
    if (m_physicsPositionIterations == physicsPositionIterations)
        return;

    m_physicsPositionIterations = physicsPositionIterations;

    emit physicsPositionIterationsChanged();
}
