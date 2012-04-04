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

#include "quasigame.h"
#include "box2ditem.h"
#include "box2dbaseitem.h"
#include "box2ddebugdrawitem.h"
#include "viewport.h"

#include <Box2D/Box2D.h>

Box2DScene::Box2DScene(QuasiGame *parent)
    : GameScene(parent)
    , m_world(0)
    , m_gravity(qreal(0), qreal(-10))
    , m_debugDraw(0)
{
    const b2Vec2 gravity(m_gravity.x(), m_gravity.y());

    m_world = new b2World(gravity);

    connect(this, SIGNAL(debugChanged()), SLOT(onDebugChanged()));
}

b2World *Box2DScene::world() const
{
    return m_world;
}

void Box2DScene::setGravity(const QPointF &gravity)
{
    m_gravity = gravity;
    if (m_world)
        m_world->SetGravity(b2Vec2(gravity.x(), gravity.y()));
}

QPointF Box2DScene::gravity() const
{
    return m_gravity;
}

void Box2DScene::update(const long &delta)
{
    if (!m_running)
        return;

    GameScene::update(delta);

    // TODO crete properties for this arguments
    m_world->Step(1.0f / 60.0f, 10, 10);

    GameItem *item;

    foreach (item, m_entities) {
        item->update(delta);
        if (Box2DBaseItem *box2DItem = dynamic_cast<Box2DBaseItem *>(item))
            box2DItem->synchronize();
    }

    if (m_debugDraw)
        m_debugDraw->step();
}

void Box2DScene::componentComplete()
{
    QQuickItem::componentComplete();

    foreach (GameItem *item, m_entities) {
        if (Box2DBaseItem *box2DItem = dynamic_cast<Box2DBaseItem *>(item))
            box2DItem->initialize(m_world);
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
