#ifndef PHYSICSENTITY_H
#define PHYSICSENTITY_H

#include <QObject>
#include "entity.h"
#include "box2dbody.h"

class QPointF;
class Box2DBody;
class Box2DWorld;
class Box2DFixture;

class PhysicsEntity : public Entity
{
    Q_OBJECT

    Q_PROPERTY(Box2DBody* body READ body)
    Q_PROPERTY(Box2DWorld* world READ world WRITE setWorld NOTIFY worldChanged)
    Q_PROPERTY(QQuickItem* target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(float linearDamping READ linearDamping WRITE setLinearDamping NOTIFY linearDampingChanged)
    Q_PROPERTY(float angularDamping READ angularDamping WRITE setAngularDamping NOTIFY angularDampingChanged)
    Q_PROPERTY(float angularVelocity READ angularVelocity WRITE setAngularVelocity NOTIFY angularVelocityChanged)
    Q_PROPERTY(QPointF linearVelocity READ linearVelocity WRITE setLinearVelocity NOTIFY linearVelocityChanged)
    Q_PROPERTY(Box2DBody::BodyType bodyType READ bodyType WRITE setBodyType NOTIFY bodyTypeChanged)
    Q_PROPERTY(bool active READ isActive WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(float gravityScale READ gravityScale WRITE setGravityScale NOTIFY gravityScaleChanged)
    Q_PROPERTY(bool bullet READ isBullet WRITE setBullet NOTIFY bulletChanged)
    Q_PROPERTY(bool sleepingAllowed READ isSleepingAllowed WRITE setSleepingAllowed NOTIFY sleepingAllowedChanged)
    Q_PROPERTY(bool fixedRotation READ hasFixedRotation WRITE setFixedRotation NOTIFY fixedRotationChanged)
    Q_PROPERTY(bool awake READ isAwake WRITE setAwake NOTIFY awakeChanged)
    Q_PROPERTY(QQmlListProperty<Box2DFixture> fixtures READ fixtures)
public:
    explicit PhysicsEntity(Scene *parent = nullptr);

    /*!
      \qmlproperty Body PhysicsEntity::body
      \brief \l Box2D Bodyin the physics world
    */
    Box2DBody* body() {  return m_body; }

    // Body properties
    /*!
      \qmlproperty World PhysicsEntity::world
      \brief The world defines the physics world of the game, and all bodies found in the world
       can interact/react with other bodies in the world.
    */
    Box2DWorld *world() const;
    void setWorld(Box2DWorld *world);

    /*! \internal */
    QQuickItem *target() const;
    void setTarget(QQuickItem *target);

    /*!
      \qmlproperty float PhysicsEntity::linearDamping
      \brief This property is used to reduce the linear velocity.  The damping
       parameter can be larger than 1.0f but the damping effect becomes sensitive
       to the time step when the damping parameter is large.
    */
    float linearDamping() const;
    void setLinearDamping(float linearDamping);

    /*!
      \qmlproperty float PhysicsEntity::angularDamping
      \brief This property is used to reduce the angular velocity. The damping
       parameter can be larger than 1.0f but the damping effect becomes sensitive
       to the time step when the damping parameter is large.
    */
    float angularDamping() const;
    void setAngularDamping(float angularDamping);

    /*!
      \qmlproperty float PhysicsEntity::angularVelocity
      \brief This property holds the angular velocity of the entity.
    */
    float angularVelocity() const;
    void setAngularVelocity(float angularVelocity);

    /*!
      \qmlproperty QPointF PhysicsEntity::linearVelocity
      \brief This property holds the linear velocity of the entity's origin
       in world co-ordinates.
    */
    QPointF linearVelocity() const;
    void setLinearVelocity(const QPointF &);

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
    Box2DBody::BodyType bodyType() const;
    void setBodyType(Box2DBody::BodyType bodyType);

    /*!
      \qmlproperty bool PhysicsEntity::active
      \brief Returns true if the Body is active, or False if it is sleeping
    */
    bool isActive() const;
    void setActive(bool active);

    /*!
      \qmlproperty float PhysicsEntity::gravityScale
      \brief This property represents the scale to adjust the gravity on
       a single entity.
    */
    float gravityScale() const;
    void setGravityScale(float gravityScale);

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
    bool isBullet() const;
    void setBullet(bool bullet);
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
    bool isSleepingAllowed() const;
    void setSleepingAllowed(bool sleepingAllowed);

    /*!
      \qmlproperty bool PhysicsEntity::fixedRotation
       property alias fixedRotation: itemBody.fixedRotation
      \brief You may want a rigid body, such as a character, to have a fixed rotation. Such a body should not rotate,
       even under load. You can use the fixedRotation property to achieve this.
    */
    bool hasFixedRotation() const;
    void setFixedRotation(bool fixedRotation);

    /*!
      \qmlproperty bool PhysicsEntity::awake
      \brief Returns True if the Body is awake, or False if it is sleeping.
    */
    bool isAwake() const;
    void setAwake(bool awake);

    /*!
      \qmlproperty list<Fixture> PhysicsEntity::fixtures
      \brief This property holds a list of Box2D fixtures contained within the current Body.
    */
    QQmlListProperty<Box2DFixture> fixtures();

    Q_INVOKABLE void applyForce(QPointF force,QPointF point);
    Q_INVOKABLE void applyForceToCenter(QPointF force);
    Q_INVOKABLE void applyTorque(qreal torque);
    Q_INVOKABLE void applyLinearImpulse(QPointF impulse, QPointF point);
    Q_INVOKABLE void applyAngularImpulse(qreal torque);
    Q_INVOKABLE QPointF getWorldCenter();
    Q_INVOKABLE QPointF getLocalCenter();
    Q_INVOKABLE float getMass();
    Q_INVOKABLE void resetMassData();
    Q_INVOKABLE float getInertia();
    Q_INVOKABLE QPointF toWorldPoint(QPointF localPoint);
    Q_INVOKABLE QPointF toWorldVector(QPointF localVector);
    Q_INVOKABLE QPointF toLocalPoint(QPointF worlPoint);
    Q_INVOKABLE QPointF toLocalVector(QPointF worldVector);
    Q_INVOKABLE QPointF getLinearVelocityFromWorldPoint(QPointF point);
    Q_INVOKABLE QPointF getLinearVelocityFromLocalPoint(QPointF point);
protected:
    virtual void componentComplete();
signals:
    void worldChanged();
    void bodyTypeChanged();
    void targetChanged();
    void linearDampingChanged();
    void linearVelocityChanged();
    void angularDampingChanged();
    void angularVelocityChanged();
    void activeChanged();
    void gravityScaleChanged();
    void bulletChanged();
    void sleepingAllowedChanged();
    void fixedRotationChanged();
    void awakeChanged();
private:
    Box2DBody* m_body;
    QList<Box2DFixture *> m_fixtures;

    static void append_fixture(QQmlListProperty<Box2DFixture> *, Box2DFixture *fixture);
    static int count_fixture(QQmlListProperty<Box2DFixture> *list);
    static Box2DFixture *at_fixture(QQmlListProperty<Box2DFixture> *list, int index);
};

#endif // PHYSICSENTITY_H
