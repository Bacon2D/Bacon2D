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
#include "box2ddebugdrawitem.h"
#include "viewport.h"

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
    , m_viewport(0)
    , m_game(0)
    , m_debug(false)
    , m_world(0)
    , m_gravity(qreal(0), qreal(-10))
    , m_debugDraw(0)
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

        if (Box2DBaseItem *box2DItem = dynamic_cast<Box2DBaseItem *>(item))
            box2DItem->synchronize();
    }

    // TODO crete properties for this arguments
    // TODO: check if scene is simulating physics
    m_world->Step(1.0f / 60.0f, 10, 10);
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

Viewport *Scene::viewport() const
{
    return m_viewport;
}

void Scene::setViewport(Viewport *viewport)
{
    if (m_viewport == viewport)
        return;

    m_viewport = viewport;

    emit viewportChanged();
}

Game *Scene::game() const
{
    return m_game;
}

void Scene::setGame(Game *game)
{
    m_game = game;
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
    foreach (item, childItems()) {
        if (Entity *entity = dynamic_cast<Entity *>(item))
            entity->setScene(this);

        if (Box2DBaseItem *box2DItem = dynamic_cast<Box2DBaseItem *>(item)) {
            box2DItem->setWorld(m_world);
            box2DItem->initialize();
        }
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

        if (Box2DBaseItem *box2DBaseItem = dynamic_cast<Box2DBaseItem *>(child)) {
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

    m_debugDraw = new Box2DDebugDrawItem(this);
    m_debugDraw->setOpacity(0.7);

    if (m_viewport) {
        m_debugDraw->setWidth(m_viewport->width());
        m_debugDraw->setHeight(m_viewport->height());
    } else {
        m_debugDraw->setWidth(width());
        m_debugDraw->setHeight(height());
    }
}

void Scene::onPostSolve(Fixture *fixtureA, Fixture *fixtureB, qreal impulse)
{
    emit postSolve(fixtureA, fixtureB, impulse);
}

void Scene::onPreSolve(Fixture *fixtureA, Fixture *fixtureB, Box2DContact *contact)
{
    emit preSolve(fixtureA, fixtureB, contact);
    delete contact;
}

void Scene::onBeginContact(Fixture *fixtureA, Fixture *fixtureB, Box2DContact *contact)
{
    emit beginContact(fixtureA, fixtureB, contact);
    delete contact;
}

void Scene::onEndContact(Fixture *fixtureA, Fixture *fixtureB, Box2DContact *contact)
{
    emit endContact(fixtureA, fixtureB, contact);
    delete contact;
}
