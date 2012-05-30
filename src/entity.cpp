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

#include "entity.h"

#include "enums.h"
#include "scene.h"
#include "game.h"
#include "behavior.h"

Entity::Entity(Scene *parent)
    : QuasiDeclarativeItem(parent)
    , m_updateInterval(0)
    , m_collided(false)
    , m_scene(0)
    , m_behavior(0)
{
#if QT_VERSION >= 0x050000
    setZ(Quasi::EntityOrdering_01);
#else
    setZValue(Quasi::EntityOrdering_01);
#endif
}

void Entity::update(const int &delta)
{
    if ((m_updateInterval && m_updateTime.elapsed() >= m_updateInterval)
        || !m_updateInterval) {
        m_updateTime.restart();
        if (m_behavior) {
            m_behavior->setDelta(delta);
            m_behavior->setEntity(this);
            m_behavior->update(delta);
            m_behavior->setEntity(0);
        }
    }

#if QT_VERSION >= 0x050000
    QQuickItem *child;
#else
    QGraphicsItem *child;
#endif
    foreach (child, childItems())
        if (Entity *item = dynamic_cast<Entity *>(child)) {
            item->update(delta);
        }
}

int Entity::updateInterval() const
{
    return m_updateInterval;
}

void Entity::setUpdateInterval(const int &updateInterval)
{
    if (m_updateInterval != updateInterval) {
        m_updateInterval = updateInterval;

        emit updateIntervalChanged();

        m_updateTime.restart();
    }
}

bool Entity::collided() const
{
    return m_collided;
}

void Entity::setCollided(const bool &collided)
{
    if (m_collided != collided) {
        m_collided = collided;

        emit collidedChanged();
    }
}

Quasi::Ordering Entity::order() const
{
#if QT_VERSION >= 0x050000
    return (Quasi::Ordering)z();
#else
    return (Quasi::Ordering)zValue();
#endif
}

void Entity::setOrder(Quasi::Ordering order)
{
#if QT_VERSION >= 0x050000
    if (z() != order)
        setZ(order);
#else
    if (zValue() != order)
        setZValue(order);
#endif
}

Scene *Entity::scene() const
{
    return m_scene;
}

void Entity::setScene(Scene *scene)
{
    m_scene = scene;
}

Game *Entity::game() const
{
    if (m_scene)
        return m_scene->game();

    return 0;
}

Behavior *Entity::behavior() const
{
    return m_behavior;
}

void Entity::setBehavior(Behavior *behavior)
{
    if (m_behavior == behavior)
        return;

    m_behavior = behavior;
    emit behaviorChanged();
}
