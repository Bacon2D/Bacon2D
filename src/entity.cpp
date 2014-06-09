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

#include "scene.h"
#include "game.h"
#include "behavior.h"

/*!
  \qmltype Entity
  \inqmlmodule Bacon2D
  \inherits Body
  \brief Entity is the base for any component used in your game.

   Entity inherits from the Box2D \l Body giving it physics properties,
   fixtures, collision detection, etc.

   Each Entity gets updated from the \l Scene on each step of the
   game loop.  The Entity can include a Behavior, which gets run on each
   update.  You can also change the updateInterval so your Behavior
   doesn't get run on each update of the Entity, reducing
   processing time.
*/
Entity::Entity(Scene *parent)
    : Box2DBody(parent)
    , m_updateInterval(0)
    , m_scene(0)
    , m_behavior(0)
{
}

Entity::~Entity()
{
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

    QQuickItem *child;
    foreach (child, childItems())
        if (Entity *item = dynamic_cast<Entity *>(child))
            item->update(delta);
}

/*!
  \qmlproperty int Entity::updateInterval
  \brief This property holds the interval in milliseconds between 
   execution of the Behavior.
*/
int Entity::updateInterval() const
{
    return m_updateInterval;
}

void Entity::setUpdateInterval(const int &updateInterval)
{
    if (m_updateInterval == updateInterval)
        return;

    m_updateInterval = updateInterval;

    emit updateIntervalChanged();

    m_updateTime.restart();
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

/*!
  \qmlproperty Behavior Entity::behavior
  \brief This property holds the \l Behavior to be run on on
   each \l updateInterval
*/
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
