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

/*!
  \qmltype Entity
  \inqmlmodule Bacon2D
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

/*!
  \qmlproperty enumeration Entity::bodyType
  \brief This property holds the current body type.
  \table
   \header
     \li {2, 1} \e {Entity::BodyType} is an enumeration:
   \header
     \li Type
     \li Description
   \row
     \li Entity.Static (default)
     \li A static body does not move under simulation and behaves as if it has infinite mass. Internally, Box2D
         stores zero for the mass and the inverse mass. Static bodies can be moved manually by the user. A static
         body has zero velocity. Static bodies do not collide with other static or kinematic bodies.
   \row
     \li Entity.Kinematic
     \li A kinematic body moves under simulation according to its velocity. Kinematic bodies do not respond to
         forces. They can be moved manually by the user, but normally a kinematic body is moved by setting its
         velocity. A kinematic body behaves as if it has infinite mass, however, Box2D stores zero for the mass
         and the inverse mass. Kinematic bodies do not collide with other kinematic or static bodies.
   \row
     \li Entity.Dynamic
     \li A dynamic body is fully simulated. They can be moved manually by the user, but normally they move
         according to forces. A dynamic body can collide with all body types. A dynamic body always has finite,
         non-zero mass. If you try to set the mass of a dynamic body to zero, it will automatically acquire a mass
         of one kilogram and it won’t rotate.
  \endtable
*/

/*!
  \qmlproperty float Entity::gravityScale
  \brief This property represents the scale to adjust the gravity on
   a single entity.
*/
/*!
  \qmlproperty float Entity::linearDamping
  \brief This property is used to reduce the linear velocity.  The damping
   parameter can be larger than 1.0f but the damping effect becomes sensitive
   to the time step when the damping parameter is large.
*/
/*!
  \qmlproperty float Entity::angularDamping
  \brief This property is used to reduce the angular velocity. The damping
   parameter can be larger than 1.0f but the damping effect becomes sensitive
   to the time step when the damping parameter is large.
*/
/*!
  \qmlproperty float Entity::angularVelocity
  \brief This property holds the angular velocity of the entity.
*/
/*!
  \qmlproperty QPointF Entity::linearVelocity
  \brief This property holds the linear velocity of the entity's origin
   in world co-ordinates.
*/
/*!
  \qmlproperty bool Entity::bullet
  \brief Game simulation usually generates a sequence of images that are played at some frame rate. This is
   called discrete simulation. In discrete simulation, rigid bodies can move by a large amount in one
   time step. If a physics engine doesn't account for the large motion, you may see some objects incorrectly pass
   through each other. This effect is called tunneling.

   By default, Box2D uses continuous collision detection (CCD) to prevent dynamic bodies from tunneling
   through static bodies. This is done by sweeping shapes from their old position to their new positions.
   The engine looks for new collisions during the sweep and computes the time of impact (TOI) for these
   collisions. Bodies are moved to their first TOI and then the solver performs a sub-step to complete the
   full time step. There may be additional TOI events within a sub-step.

   Normally CCD is not used between dynamic bodies. This is done to keep performance reasonable. In
   some game scenarios you need dynamic bodies to use CCD. For example, you may want to shoot a high
   speed bullet at a stack of dynamic bricks. Without CCD, the bullet might tunnel through the bricks.
   Fast moving objects in Box2D can be labeled as bullets. Bullets will perform CCD with both static and
   dynamic bodies. You should decide what bodies should be bullets based on your game design.
*/

/*!
  \qmlproperty bool Entity::sleepingAllowed
  \brief What does sleep mean? Well it is expensive to simulate bodies, so the less we have to simulate the
   better. When a body comes to rest we would like to stop simulating it.

   When Box2D determines that a body (or group of bodies) has come to rest, the body enters a sleep
   state which has very little CPU overhead. If a body is awake and collides with a sleeping body, then the
   sleeping body wakes up. Bodies will also wake up if a joint or contact attached to them is destroyed. You
   can also wake a body manually.

   The sleepingAllowed property lets you specify whether a body can sleep and whether a body is created sleeping.
*/
/*!
  \qmlproperty bool Entity::fixedRotation
  \brief You may want a rigid body, such as a character, to have a fixed rotation. Such a body should not rotate,
   even under load. You can use the fixedRotation property to achieve this.
*/

/*!
  \qmlproperty bool Entity::active
  \brief Returns true if the Entity is active, or False if it is sleeping
*/

/*!
  \qmlproperty bool Entity::awake
  \brief Returns True if the Entity is awake, or False if it is sleeping.
*/

/*!
  \qmlproperty list<Fixture> Entity::fixtures
  \brief This property holds a list of Box2D fixtures contained within the current Entity.
*/

/*!
  \qmlmethod void Entity::applyForce(const QPointF force, const QPointF point)
*/

/*!
  \qmlmethod void Entity::applyForceToCenter(const QPointF &force)
*/

/*!
  \qmlmethod void Entity::applyTorque(qreal torque)
*/

/*!
  \qmlmethod void Entity::applyLinearImpulse(const QPointF &impulse, const QPointF &point)
*/

/*!
  \qmlmethod void Entity::applyAngularImpulse(qreal impulse)
*/

/*!
  \qmlmethod QPointF Entity::getWorldCenter() const
*/

/*!
  \qmlmethod QPointF Entity::getLocalCenter() const
*/

/*!
  \qmlmethod float Entity::getMass() const
*/

/*!
  \qmlmethod float Entity::resetMassData()
*/

/*!
  \qmlmethod float Entity::getInertia() const
*/

/*!
  \qmlmethod QPointF Entity::toWorldPoint(const QPointF &localPoint) const
*/

/*!
  \qmlmethod QPointF Entity::toWorldVector(const QPointF &localVector) const
*/

/*!
  \qmlmethod QPointF Entity::toLocalPoint(const QPointF &worldPoint) const
*/

/*!
  \qmlmethod QPointF Entity::toLocalVector(const QPointF &worldVector) const
*/

/*!
  \qmlmethod QPointF Entity::getLinearVelocityFromWorldPoint(const QPointF &point) const
*/

/*!
  \qmlmethod QPointF Entity::getLinearVelocityFromLocalPoint(const QPointF &point) const
*/

/*!
  \qmlsignal void Entity::bodyCreated()
  \brief Emitted when the Box2D body has finished initialization
*/
