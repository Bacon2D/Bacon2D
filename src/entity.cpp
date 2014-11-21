/**
 * Copyright (C) 2012 by INdT
 * Copyright (C) 2014 Bacon2D Project
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
#include "sprite.h"
#include "../../3rdparty/qml-box2d/box2dbody.h"


/*!
  \qmltype Entity
  \inqmlmodule Bacon2D
  \inherits Item
  \brief Entity is the base for any component used in your game.

   Each Entity gets updated from the \l Scene on each step of the
   game loop.  The Entity can include a Behavior, which gets run on each
   update.  You can also change the updateInterval so your Behavior
   doesn't get run on each update of the Entity, reducing
   processing time.

   If physics are enabled in the \l Scene, Entities will become part of the
   scene's \l Box2D physics world.  Box2D uses the term "body" for all items
   participating in the physics world.  Your entities are bodies to Box2D, so
   whenever you see the term body used in the documentation, remember in
   Bacon2D it's an Entity.

   You can apply forces, torques, and impulses to entities. An Entity can
   be static, kinematic, or dynamic.

   Bodies (Entities) are the backbone for fixtures (shapes).  Bodies carry
   fixtures and move them around in the world.  Entites are always rigid bodies
   in Box2D.  That means that two fixtures attached to the same rigid body
   never move relative to each other and fixtures attached to the same
   entity don’t collide.

   Fixtures have collision geometry and density. Normally, entities acquire
   their mass properties from the fixtures. However, you can override the
   mass properties after an entity is constructed.
*/
Entity::Entity(Scene *parent)
    : QQuickItem(parent)
    , m_updateInterval(0)
    , m_scene(0)
    , m_behavior(0)
{
}

Entity::~Entity()
{
}

void Entity::initializeEntities(QQuickItem *parent)
{
    if (!m_scene)
        return;

    QQuickItem *item;
    foreach (item, parent->childItems()) {
        if (Entity *entity = dynamic_cast<Entity *>(item))
            entity->setScene(m_scene);
        if (Sprite *sprite = dynamic_cast<Sprite *>(item))
            sprite->setEntity(this);
        initializeEntities(item);
    }
}

void Entity::componentComplete()
{
    QQuickItem::componentComplete();
    if (m_scene && m_scene->physics() && m_scene->world()) {
        foreach (Box2DBody *body, this->findChildren<Box2DBody *>(QString(), Qt::FindDirectChildrenOnly)) {
            body->setTarget(this);
            body->setWorld(m_scene->world());
        }
    }
    initializeEntities(this);
}

void Entity::itemChange(ItemChange change, const ItemChangeData &data)
{
    if (!m_scene)
        return;

    if (isComponentComplete() && change == ItemChildAddedChange) {
        QQuickItem *child = data.item;
        if (Entity *entity = dynamic_cast<Entity *>(child))
            entity->setScene(m_scene);
        if (Sprite *sprite = dynamic_cast<Sprite *>(child))
            sprite->setEntity(this);

        initializeEntities(child);
    }

    QQuickItem::itemChange(change, data);
}

void Entity::update(const int &delta)
{
    if ((m_updateInterval && m_updateTime.elapsed() >= m_updateInterval)
        || !m_updateInterval) {
        m_updateTime.restart();
        if (m_behavior) {
            m_behavior->setDelta(delta);
            m_behavior->setTarget(this);
            m_behavior->update(delta);
            m_behavior->setTarget(0);
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
    if (m_scene == scene)
        return;
    m_scene = scene;
    initializeEntities(this);
    emit sceneChanged();
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
