#include "box2ditem.h"

#include "box2dscene.h"

#include <Box2D/Box2D.h>

Box2DItem::Box2DItem(GameScene *parent)
    : Box2DBaseItem(parent)
    , m_body(0)
    , m_synchronizing(false)
    , m_linearDamping(0.0f)
    , m_angularDamping(0.0f)
    , m_bodyType(Dynamic)
    , m_bullet(false)
    , m_sleepingAllowed(true)
    , m_fixedRotation(false)
    , m_active(true)
    , m_fixture(0)
    , m_density(0)
    , m_friction(0)
    , m_restitution(0)
{
    setTransformOrigin(Center);
    connect(this, SIGNAL(rotationChanged()), SLOT(onRotationChanged()));
}

b2Body *Box2DItem::body()
{
    return m_body;
}

/*
 * Shamelessly stolen from qml-box2d project at gitorious
 *
 * https://gitorious.org/qml-box2d/qml-box2d
 */
void Box2DItem::synchronize()
{
    if (m_body) {
        m_synchronizing = true;

        const b2Vec2 position = m_body->GetPosition();
        const float32 angle = m_body->GetAngle();

        const qreal newX = position.x * scaleRatio - width() / 2.0;
        const qreal newY = -position.y * scaleRatio - height() / 2.0;
        const qreal newRotation = -(angle * 360.0) / (2 * b2_pi);

        if (!qFuzzyCompare(x(), newX) || !qFuzzyCompare(y(), newY))
            setPos(QPointF(newX, newY));
        if (!qFuzzyCompare(rotation(), newRotation))
            setRotation(newRotation);

        m_synchronizing = false;
    }
}

void Box2DItem::onRotationChanged()
{
    if (!m_synchronizing && m_body) {
        m_body->SetTransform(m_body->GetPosition(),
                             (rotation() * 2 * b2_pi) / -360.0);
    }
}

/*
 * Shamelessly stolen from qml-box2d project at gitorious
 *
 * https://gitorious.org/qml-box2d/qml-box2d
 */
void Box2DItem::initialize(b2World *world)
{
    if (m_initialized)
        return;

    b2BodyDef bodyDef;
    bodyDef.type = static_cast<b2BodyType>(m_bodyType);
    bodyDef.position.Set((x() + width() / 2.0) / scaleRatio,
                         (-y() - height() / 2.0) / scaleRatio);

    bodyDef.angle = -(rotation() * (2 * b2_pi)) / 360.0;
    bodyDef.linearDamping = m_linearDamping;
    bodyDef.angularDamping = m_angularDamping;
    bodyDef.bullet = m_bullet;
    bodyDef.allowSleep = m_sleepingAllowed;
    bodyDef.fixedRotation = m_fixedRotation;

    m_body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(width() / scaleRatio / 2.0, height() / scaleRatio / 2.0);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = m_density;
    fixtureDef.friction = m_friction;
    fixtureDef.restitution = m_restitution;

    m_fixture = m_body->CreateFixture(&fixtureDef);

    m_initialized = true;
}

qreal Box2DItem::linearDamping() const
{
    return m_linearDamping;
}

void Box2DItem::setLinearDamping(qreal linearDamping)
{
    if (m_linearDamping != linearDamping) {
        m_linearDamping = linearDamping;

        if (m_body)
            m_body->SetLinearDamping(linearDamping);

        emit linearDampingChanged();
    }
}

qreal Box2DItem::angularDamping() const
{
    return m_angularDamping;
}

void Box2DItem::setAngularDamping(qreal angularDamping)
{
    if (m_angularDamping != angularDamping) {
        m_angularDamping = angularDamping;

        if (m_body)
            m_body->SetAngularDamping(angularDamping);

        emit angularDampingChanged();
    }
}

Box2DItem::BodyType Box2DItem::bodyType() const
{
    return m_bodyType;
}

void Box2DItem::setBodyType(BodyType bodyType)
{
    if (m_bodyType != bodyType) {
        m_bodyType = bodyType;

        if (m_body)
            m_body->SetType((b2BodyType)bodyType);

        emit bodyTypeChanged();
    }
}

bool Box2DItem::bullet() const
{
    return m_bullet;
}

void Box2DItem::setBullet(bool bullet)
{
    if (m_bullet != bullet) {
        m_bullet = bullet;

        if (m_body)
            m_body->SetBullet(bullet);

        emit bulletChanged();
    }
}

bool Box2DItem::sleepingAllowed() const
{
    return m_sleepingAllowed;
}

void Box2DItem::setSleepingAllowed(bool sleepingAllowed)
{
    if (m_sleepingAllowed != sleepingAllowed) {
        m_sleepingAllowed = sleepingAllowed;

        if (m_body)
            m_body->SetSleepingAllowed(sleepingAllowed);

        emit sleepingAllowedChanged();
    }
}

bool Box2DItem::fixedRotation() const
{
    return m_fixedRotation;
}

void Box2DItem::setFixedRotation(bool fixedRotation)
{
    if (m_fixedRotation != fixedRotation) {
        m_fixedRotation = fixedRotation;

        if (m_body)
            m_body->SetFixedRotation(fixedRotation);

        emit fixedRotationChanged();
    }
}

bool Box2DItem::active() const
{
    return m_active;
}

void Box2DItem::setActive(bool active)
{
    if (m_active != active) {
        m_active = active;

        if (m_body)
            m_body->SetActive(active);

        emit activeChanged();
    }
}

void Box2DItem::applyTorque(float torque)
{
    if (m_body)
        m_body->ApplyTorque(torque);
}

void Box2DItem::applyLinearImpulse(QPointF impulse, QPointF point)
{
    if (m_body) {
        m_body->ApplyLinearImpulse(b2Vec2(impulse.x() / scaleRatio,
                                          -impulse.y() / scaleRatio),
                                   b2Vec2(point.x() / scaleRatio,
                                          -point.y() / scaleRatio));
    }
}

float Box2DItem::density()
{
    return m_density;
}

void Box2DItem::setDensity(float density)
{
    if (m_density != density) {
        m_density = density;

        if (m_body && m_fixture) {
            m_fixture->SetDensity(density);
            m_body->ResetMassData();
        }

        emit densityChanged();
    }
}

float Box2DItem::friction()
{
    return m_friction;
}

void Box2DItem::setFriction(float friction)
{
    if (m_friction != friction) {
        m_friction = friction;

        if (m_fixture) {
            m_fixture->SetFriction(friction);
        }

        emit frictionChanged();
    }
}

float Box2DItem::restitution()
{
    return m_restitution;
}

void Box2DItem::setRestitution(float restitution)
{
    if (m_restitution != restitution) {
        m_restitution = restitution;

        if (m_fixture) {
            m_fixture->SetRestitution(restitution);
        }
    }
}

void Box2DItem::geometryChanged(const QRectF &newGeometry,
                                const QRectF &oldGeometry)
{
    if (!m_synchronizing && m_body) {
        if (newGeometry.topLeft() != oldGeometry.topLeft()) {
            const QPointF pos = newGeometry.topLeft();

            m_body->SetTransform(b2Vec2((pos.x() + width() / 2.0) / scaleRatio,
                                        (-pos.y() - height() / 2.0) / scaleRatio),
                                 m_body->GetAngle());
        }
    }

    QQuickItem::geometryChanged(newGeometry, oldGeometry);
}
