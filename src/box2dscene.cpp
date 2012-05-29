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

#include "box2dscene.h"

#include "box2dbaseitem.h"
#include "box2ddebugdrawitem.h"
#include "game.h"
#include "viewport.h"

#include <QDebug>

static void deleteWorld(b2World *world)
{
    delete world;
}

Box2DScene::Box2DScene(Game *parent)
    : Scene(parent)
    , m_world(0)
    , m_gravity(qreal(0), qreal(-10))
    , m_debugDraw(0)
{
    const b2Vec2 gravity(m_gravity.x(), m_gravity.y());

    m_world = QSharedPointer<b2World>(new b2World(gravity), deleteWorld);

    ContactListener *contactListener = new ContactListener(this);
    m_world->SetContactListener(contactListener);

    connect(this, SIGNAL(debugChanged()), SLOT(onDebugChanged()));
}

Box2DScene::~Box2DScene()
{
    m_world.clear();
}

b2World *Box2DScene::world() const
{
    return m_world.data();
}

void Box2DScene::setGravity(const QPointF &gravity)
{
    m_gravity = gravity;

    m_world->SetGravity(b2Vec2(gravity.x(), gravity.y()));
}

QPointF Box2DScene::gravity() const
{
    return m_gravity;
}

void Box2DScene::update(const int &delta)
{
    if (!m_running)
        return;

    Scene::update(delta);

    // TODO crete properties for this arguments
    m_world->Step(1.0f / 60.0f, 10, 10);

#if QT_VERSION >= 0x050000
    QQuickItem *item;
#else
    QGraphicsItem *item;
#endif
    foreach (item, childItems()) {
        if (Box2DBaseItem *box2DItem = dynamic_cast<Box2DBaseItem *>(item))
            box2DItem->synchronize();
    }

    if (m_debugDraw)
        m_debugDraw->step();
}

void Box2DScene::componentComplete()
{
    Scene::componentComplete();

#if QT_VERSION >= 0x050000
    QQuickItem *item;
#else
    QGraphicsItem *item;
#endif
    foreach (item, childItems()) {
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

void Box2DScene::onDebugChanged()
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

#if QT_VERSION >= 0x050000
void Box2DScene::itemChange(ItemChange change, const ItemChangeData &data)
#else
QVariant Box2DScene::itemChange(GraphicsItemChange change, const QVariant &value)
#endif
{
    if (isComponentComplete() && change == ItemChildAddedChange) {
#if QT_VERSION >= 0x050000
        QQuickItem *child = data.item;
#else
        QGraphicsItem *child = value.value<QGraphicsItem *>();
#endif
        if (Box2DItem *box2DItem = dynamic_cast<Box2DItem *>(child)) {
            box2DItem->setWorld(m_world);
        }
    }

#if QT_VERSION >= 0x050000
    Scene::itemChange(change, data);
#else
    return Scene::itemChange(change, value);
#endif
}

void Box2DScene::onContact(Box2DItem *bodyA, Box2DItem *bodyB, qreal impulse)
{
    emit contact(bodyA, bodyB, impulse);
}

void Box2DScene::onPreContact(Box2DItem *bodyA, Box2DItem *bodyB, Box2DContact *contact)
{
    emit preContact(bodyA, bodyB, contact);
    delete contact;
}
