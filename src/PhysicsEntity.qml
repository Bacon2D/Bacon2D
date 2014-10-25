import QtQuick 2.0
import Bacon2D 1.0

/*!
  \qmltype PhysicsEntity
  \inqmlmodule Bacon2D
  \inherits Entity
  \ingroup physics
  \brief An \l Entity that participates in the \l Box2D physics world
*/
Entity {
    id: item

    transformOrigin: Item.TopLeft

    /*!
      \qmlproperty Body PhysicsEntity::body
      \brief \l Box2D Bodyin the physics world
    */
    property alias body: itemBody

    // Body properties
    /*!
      \qmlproperty World PhysicsEntity::world
      \brief The world defines the physics world of the game, and all bodies found in the world
       can interact/react with other bodies in the world.
    */
    property alias world: itemBody.world

    /*! \internal */
    property alias target: itemBody.target

    /*!
      \qmlproperty float PhysicsEntity::linearDamping
      \brief This property is used to reduce the linear velocity.  The damping
       parameter can be larger than 1.0f but the damping effect becomes sensitive
       to the time step when the damping parameter is large.
    */
    property alias linearDamping: itemBody.linearDamping

    /*!
      \qmlproperty float PhysicsEntity::angularDamping
      \brief This property is used to reduce the angular velocity. The damping
       parameter can be larger than 1.0f but the damping effect becomes sensitive
       to the time step when the damping parameter is large.
    */
    property alias angularDamping: itemBody.angularDamping

    /*!
      \qmlproperty float PhysicsEntity::angularVelocity
      \brief This property holds the angular velocity of the entity.
    */
    property alias angularVelocity: itemBody.angularVelocity

    /*!
      \qmlproperty QPointF PhysicsEntity::linearVelocity
      \brief This property holds the linear velocity of the entity's origin
       in world co-ordinates.
    */
    property alias linearVelocity: itemBody.linearVelocity

    /*!
      \qmlproperty enumeration PhysicsEntity::bodyType
      \brief This property holds the current body type.
      \table
       \header
         \li {2, 1} \e {PhysicsEntity::BodyType} is an enumeration:
       \header
         \li Type
         \li Description
       \row
         \li Body.Static (default)
         \li A static body does not move under simulation and behaves as if it has infinite mass. Internally, Box2D
             stores zero for the mass and the inverse mass. Static bodies can be moved manually by the user. A static
             body has zero velocity. Static bodies do not collide with other static or kinematic bodies.
       \row
         \li Body.Kinematic
         \li A kinematic body moves under simulation according to its velocity. Kinematic bodies do not respond to
             forces. They can be moved manually by the user, but normally a kinematic body is moved by setting its
             velocity. A kinematic body behaves as if it has infinite mass, however, Box2D stores zero for the mass
             and the inverse mass. Kinematic bodies do not collide with other kinematic or static bodies.
       \row
         \li Body.Dynamic
         \li A dynamic body is fully simulated. They can be moved manually by the user, but normally they move
             according to forces. A dynamic body can collide with all body types. A dynamic body always has finite,
             non-zero mass. If you try to set the mass of a dynamic body to zero, it will automatically acquire a mass
             of one kilogram and it won’t rotate.
      \endtable
    */
    property alias bodyType: itemBody.bodyType

    /*!
      \qmlproperty bool PhysicsEntity::active
      \brief Returns true if the Body is active, or False if it is sleeping
    */
    property alias active: itemBody.active

    /*!
      \qmlproperty float PhysicsEntity::gravityScale
      \brief This property represents the scale to adjust the gravity on
       a single entity.
    */
    property alias gravityScale: itemBody.gravityScale

    /*!
      \qmlproperty bool PhysicsEntity::bullet
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
    property alias bullet: itemBody.bullet

    /*!
      \qmlproperty bool PhysicsEntity::sleepingAllowed
      \brief What does sleep mean? Well it is expensive to simulate bodies, so the less we have to simulate the
       better. When a body comes to rest we would like to stop simulating it.

       When Box2D determines that a body (or group of bodies) has come to rest, the body enters a sleep
       state which has very little CPU overhead. If a body is awake and collides with a sleeping body, then the
       sleeping body wakes up. Bodies will also wake up if a joint or contact attached to them is destroyed. You
       can also wake a body manually.

       The sleepingAllowed property lets you specify whether a body can sleep and whether a body is created sleeping.
    */
    property alias sleepingAllowed: itemBody.sleepingAllowed

    /*!
      \qmlproperty bool PhysicsEntity::fixedRotation
       property alias fixedRotation: itemBody.fixedRotation
      \brief You may want a rigid body, such as a character, to have a fixed rotation. Such a body should not rotate,
       even under load. You can use the fixedRotation property to achieve this.
    */
    property alias fixedRotation: itemBody.fixedRotation

    /*!
      \qmlproperty bool PhysicsEntity::awake
      \brief Returns True if the Body is awake, or False if it is sleeping.
    */
    property alias awake: itemBody.awake

    /*!
      \qmlproperty list<Fixture> PhysicsEntity::fixtures
      \brief This property holds a list of Box2D fixtures contained within the current Body.
    */
    property alias fixtures: itemBody.fixtures

    /*!
      \qmlmethod void PhysicsEntity::applyForce(const QPointF force, const QPointF point)
    */
    function applyForce(force, point) {
        itemBody.applyForce(force, point);
    }

    /*!
      \qmlmethod void PhysicsEntity::applyForceToCenter(const QPointF &force)
    */
    function applyForceToCenter(force) {
        itemBody.applyForceToCenter(force);
    }

    /*!
      \qmlmethod void PhysicsEntity::applyTorque(qreal torque)
    */
    function applyTorque(torque) {
        itemBody.applyTorque(torque);
    }

    /*!
      \qmlmethod void PhysicsEntity::applyLinearImpulse(const QPointF &impulse, const QPointF &point)
    */
    function applyLinearImpulse(impulse, point) {
        itemBody.applyLinearImpulse(impulse, point);
    }

    /*!
      \qmlmethod void PhysicsEntity::applyAngularImpulse(qreal impulse)
    */
    function applyAngularImpulse(impulse) {
        itemBody.applyAngularImpulse(impulse);
    }

    /*!
      \qmlmethod QPointF PhysicsEntity::getWorldCenter() const
    */
    function getWorldCenter() {
        return itemBody.getWorldCenter();
    }

    /*!
      \qmlmethod QPointF PhysicsEntity::getLocalCenter() const
    */
    function getLocalCenter() {
        return itemBody.getLocalCenter();
    }

    /*!
      \qmlmethod float PhysicsEntity::getMass() const
    */
    function getMass() {
        return itemBody.getMass();
    }

    /*!
      \qmlmethod float PhysicsEntity::resetMassData()
    */
    function resetMassData() {
        return itemBody.resetMassData();
    }

    /*!
      \qmlmethod float PhysicsEntity::getInertia() const
    */
    function getInertia() {
        return itemBody.getInertia();
    }

    /*!
      \qmlmethod QPointF PhysicsEntity::toWorldPoint(const QPointF &localPoint) const
    */
    function toWorldPoint(localPoint) {
        return itemBody.toWorldPoint(localPoint);
    }

    /*!
      \qmlmethod QPointF PhysicsEntity::toWorldVector(const QPointF &localVector) const
    */
    function toWorldVector(localVector) {
        return itemBody.toWorldVector(localVector);
    }

    /*!
      \qmlmethod QPointF PhysicsEntity::toLocalPoint(const QPointF &worldPoint) const
    */
    function toLocalPoint(worldPoint) {
        return itemBody.toLocalPoint(worldPoint);
    }

    /*!
      \qmlmethod QPointF PhysicsEntity::toLocalVector(const QPointF &worldVector) const
    */
    function toLocalVector(worldVector) {
        return itemBody.toLocalVector(worldVector);
    }

    /*!
      \qmlmethod QPointF PhysicsEntity::getLinearVelocityFromWorldPoint(const QPointF &point) const
    */
    function getLinearVelocityFromWorldPoint(point) {
        return itemBody.getLinearVelocityFromWorldPoint(point);
    }

    /*!
      \qmlmethod QPointF PhysicsEntity::getLinearVelocityFromLocalPoint(const QPointF &point) const
    */
    function getLinearVelocityFromLocalPoint(point) {
        return itemBody.getLinearVelocityFromLocalPoint(point);
    }

    /*!
      \qmlsignal void PhysicsEntity::bodyCreated()
      \brief Emitted when the Box2D body has finished initialization
    */
    signal bodyCreated()

    Body {
        id: itemBody
        world: scene.world
        target: item
        signal beginContact(Fixture other)
        signal endContact(Fixture other)
    }
}


