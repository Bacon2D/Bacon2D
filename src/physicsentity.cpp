#include "physicsentity.h"
#include "box2dbody.h"
#include "box2dworld.h"
#include "scene.h"

PhysicsEntity::PhysicsEntity(Scene *parent)
    : m_body(new Box2DBody(this))
    , Entity(parent)
{
    m_body->setTarget(this);
    setTransformOrigin(QQuickItem::TopLeft);

    connect(m_body, SIGNAL(targetChanged()), this, SIGNAL(targetChanged()));
    connect(m_body, SIGNAL(linearDampingChanged()), this, SIGNAL(linearDampingChanged()));
    connect(m_body, SIGNAL(angularDampingChanged()), this, SIGNAL(angularDampingChanged()));
    connect(m_body, SIGNAL(angularVelocityChanged()), this, SIGNAL(angularVelocityChanged()));
    connect(m_body, SIGNAL(gravityScaleChanged()), this, SIGNAL(gravityScaleChanged()));
    connect(m_body, SIGNAL(bulletChanged()), this, SIGNAL(bulletChanged()));
    connect(m_body, SIGNAL(sleepingAllowedChanged()), this, SIGNAL(sleepingAllowedChanged()));
    connect(m_body, SIGNAL(fixedRotationChanged()), this, SIGNAL(fixedRotationChanged()));
}

Box2DWorld *PhysicsEntity::world() const
{
    return m_body->world();
}

void PhysicsEntity::setWorld(Box2DWorld *world)
{
    if (m_body->world() == world)
        return;

    m_body->setWorld(world);
    emit worldChanged();
}

QQuickItem *PhysicsEntity::target() const
{
    return m_body->target();
}

void PhysicsEntity::setTarget(QQuickItem *target)
{
    m_body->setTarget(target);
}

float PhysicsEntity::linearDamping() const
{
    return m_body->linearDamping();
}

void PhysicsEntity::setLinearDamping(float linearDamping)
{
    if (m_body)
        m_body->setLinearDamping(linearDamping);
}

float PhysicsEntity::angularDamping() const
{
    return m_body->angularDamping();
}

void PhysicsEntity::setAngularDamping(float angularDamping)
{
    m_body->setAngularDamping(angularDamping);
}

float PhysicsEntity::angularVelocity() const
{
    return m_body->angularVelocity();
}

void PhysicsEntity::setAngularVelocity(float angularVelocity)
{
    m_body->setAngularVelocity(angularVelocity);
}

QPointF PhysicsEntity::linearVelocity() const
{
    return m_body->linearVelocity();
}

void PhysicsEntity::setLinearVelocity(const QPointF &linearVelocity)
{
    m_body->setLinearVelocity(linearVelocity);
}

Box2DBody::BodyType PhysicsEntity::bodyType() const
{
    return m_body->bodyType();
}

void PhysicsEntity::setBodyType(Box2DBody::BodyType bodyType)
{
    m_body->setBodyType(bodyType);
}

bool PhysicsEntity::isActive() const
{
    return m_body->isActive();
}

void PhysicsEntity::setActive(bool active)
{
    if (m_body->isActive() == active)
        return;

    m_body->setActive(active);
    emit activeChanged();
}

float PhysicsEntity::gravityScale() const
{
    return m_body->gravityScale();
}

void PhysicsEntity::setGravityScale(float gravityScale)
{
    m_body->setGravityScale(gravityScale);
}

bool PhysicsEntity::isBullet() const
{
    return m_body->isBullet();
}

void PhysicsEntity::setBullet(bool bullet)
{
    m_body->setBullet(bullet);
}

bool PhysicsEntity::isSleepingAllowed() const
{
    return m_body->sleepingAllowed();
}

void PhysicsEntity::setSleepingAllowed(bool sleepingAllowed)
{
    m_body->setSleepingAllowed(sleepingAllowed);
}

bool PhysicsEntity::hasFixedRotation() const
{
    return m_body->fixedRotation();
}

void PhysicsEntity::setFixedRotation(bool fixedRotation)
{
    m_body->setFixedRotation(fixedRotation);
}

bool PhysicsEntity::isAwake() const
{
    m_body->isAwake();
}

void PhysicsEntity::setAwake(bool awake)
{
    if (m_body->isAwake() == awake)
        return;

    m_body->setAwake(awake);
    emit awakeChanged();
}

QQmlListProperty<Box2DFixture> PhysicsEntity::fixtures()
{
    return QQmlListProperty<Box2DFixture>(this, 0,
                                          &PhysicsEntity::append_fixture,
                                          &PhysicsEntity::count_fixture,
                                          &PhysicsEntity::at_fixture,
                                          0);
}

void PhysicsEntity::append_fixture(QQmlListProperty<Box2DFixture> *list,
                               Box2DFixture *fixture)
{
    PhysicsEntity *entity = static_cast<PhysicsEntity *>(list->object);
    entity->body()->addFixture(fixture);
    entity->m_fixtures.append(fixture);
}

int PhysicsEntity::count_fixture(QQmlListProperty<Box2DFixture> *list)
{
    PhysicsEntity *entity = static_cast<PhysicsEntity *>(list->object);
    return entity->m_fixtures.count();
}

Box2DFixture *PhysicsEntity::at_fixture(QQmlListProperty<Box2DFixture> *list, int index)
{
    PhysicsEntity *entity = static_cast<PhysicsEntity *>(list->object);
    return entity->m_fixtures.at(index);
}

void PhysicsEntity::applyForce(QPointF force, QPointF point)
{
    m_body->applyForce(force,point);
}

void PhysicsEntity::applyForceToCenter(QPointF force)
{
    m_body->applyForceToCenter(force);
}

void PhysicsEntity::applyTorque(qreal torque)
{
    m_body->applyTorque(torque);
}

void PhysicsEntity::applyLinearImpulse(QPointF impulse, QPointF point)
{
    m_body->applyLinearImpulse(impulse, point);
}

void PhysicsEntity::applyAngularImpulse(qreal torque)
{
    m_body->applyAngularImpulse(torque);
}

QPointF PhysicsEntity::getWorldCenter()
{
    return m_body->getWorldCenter();
}

QPointF PhysicsEntity::getLocalCenter()
{
    return m_body->getLocalCenter();
}

float PhysicsEntity::getMass()
{
    return m_body->getMass();
}

void PhysicsEntity::resetMassData()
{
    m_body->resetMassData();
}

float PhysicsEntity::getInertia()
{
    return m_body->getInertia();
}

QPointF PhysicsEntity::toWorldPoint(QPointF localPoint)
{
    return m_body->toWorldPoint(localPoint);
}

QPointF PhysicsEntity::toWorldVector(QPointF localVector)
{
    return m_body->toWorldVector(localVector);
}

QPointF PhysicsEntity::toLocalPoint(QPointF worlPoint)
{
    return m_body->toLocalPoint(worlPoint);
}

QPointF PhysicsEntity::toLocalVector(QPointF worldVector)
{
    return m_body->toLocalVector(worldVector);
}

QPointF PhysicsEntity::getLinearVelocityFromWorldPoint(QPointF point)
{
    return m_body->getLinearVelocityFromWorldPoint(point);
}

QPointF PhysicsEntity::getLinearVelocityFromLocalPoint(QPointF point)
{
    return m_body->getLinearVelocityFromLocalPoint(point);
}

void PhysicsEntity::componentComplete()
{
    Entity::componentComplete();

    m_body->setWorld(scene()->world());
    m_body->componentComplete();
}
