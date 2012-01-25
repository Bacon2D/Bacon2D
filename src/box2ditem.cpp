#include "box2ditem.h"

#include "box2dscene.h"

#include <Box2D/Box2D.h>

Box2DItem::Box2DItem(GameScene *parent)
    : Box2DBaseItem(parent)
    , m_body(0)
    , m_linearDamping(0.0f)
    , m_angularDamping(0.0f)
    , m_bodyType(Dynamic)
    , m_shape(Rectangle)
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

b2Body *Box2DItem::body() const
{
    return m_body;
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
    bodyDef.position.Set((x() + width() / 2.0) / m_scaleRatio,
                         (-y() - height() / 2.0) / m_scaleRatio);

    bodyDef.angle = -(rotation() * (2 * b2_pi)) / 360.0;
    bodyDef.linearDamping = m_linearDamping;
    bodyDef.angularDamping = m_angularDamping;
    bodyDef.bullet = m_bullet;
    bodyDef.allowSleep = m_sleepingAllowed;
    bodyDef.fixedRotation = m_fixedRotation;

    m_body = world->CreateBody(&bodyDef);

    b2Shape *shape;

    switch (m_shape){
        case Rectangle:
            shape = new b2PolygonShape;
            ((b2PolygonShape*)shape)->SetAsBox(width() / m_scaleRatio / 2.0, height() / m_scaleRatio / 2.0);
            break;
        case Polygon:
            {
                // TODO: check for b2_maxPolygonVertices
                int i;
                b2Vec2 *vertices = new b2Vec2[m_vertices.length()];

                for (i = 0; i < m_vertices.length(); i++){
                    QVariantList temp = m_vertices.at(i).toList();

                    const float x = temp.at(0).toFloat() - (width() / 2);
                    const float y = temp.at(1).toFloat() - (height() / 2);
                    vertices[i].Set(x / m_scaleRatio, y / m_scaleRatio);

                }

                shape = new b2PolygonShape;
                ((b2PolygonShape*)shape)->Set(vertices, m_vertices.length());
            }
            break;
        case Circle:
            shape = new b2CircleShape;
            ((b2CircleShape*)shape)->m_radius = width() / m_scaleRatio / 2.0f;
            break;
        default:
            // TODO error handling
            break;
    }

    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = m_density;
    fixtureDef.friction = m_friction;
    fixtureDef.restitution = m_restitution;

    m_fixture = m_body->CreateFixture(&fixtureDef);

    foreach (QQuickItem *item, childItems()) {
        if (Box2DBaseItem *box2DItem = dynamic_cast<Box2DBaseItem *>(item))
            box2DItem->initialize(world);
    }

    m_initialized = true;
}

qreal Box2DItem::linearDamping() const
{
    return m_linearDamping;
}

void Box2DItem::setLinearDamping(const qreal &linearDamping)
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

void Box2DItem::setAngularDamping(const qreal &angularDamping)
{
    if (m_angularDamping != angularDamping) {
        m_angularDamping = angularDamping;

        if (m_body)
            m_body->SetAngularDamping(angularDamping);

        emit angularDampingChanged();
    }
}

Box2DItem::Shape Box2DItem::shape() const
{
    return m_shape;
}

void Box2DItem::setShape(const Shape &shape)
{
    if (m_shape != shape) {
        m_shape = shape;

        emit shapeChanged();
        // XXX needs additional treatment?
    }
}

Box2DItem::BodyType Box2DItem::bodyType() const
{
    return m_bodyType;
}

void Box2DItem::setBodyType(const BodyType &bodyType)
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

void Box2DItem::setBullet(const bool &bullet)
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

void Box2DItem::setSleepingAllowed(const bool &sleepingAllowed)
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

void Box2DItem::setFixedRotation(const bool &fixedRotation)
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

void Box2DItem::setActive(const bool &active)
{
    if (m_active != active) {
        m_active = active;

        if (m_body)
            m_body->SetActive(active);

        emit activeChanged();
    }
}

void Box2DItem::applyTorque(const float &torque)
{
    if (m_body)
        m_body->ApplyTorque(torque);
}

void Box2DItem::applyLinearImpulse(const QPointF &impulse, const QPointF &point)
{
    if (m_body) {
        m_body->ApplyLinearImpulse(b2Vec2(impulse.x() / m_scaleRatio,
                                          -impulse.y() / m_scaleRatio),
                                   b2Vec2(point.x() / m_scaleRatio,
                                          -point.y() / m_scaleRatio));
    }
}

float Box2DItem::density() const
{
    return m_density;
}

void Box2DItem::setDensity(const float &density)
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

float Box2DItem::friction() const
{
    return m_friction;
}

void Box2DItem::setFriction(const float &friction)
{
    if (m_friction != friction) {
        m_friction = friction;

        if (m_fixture) {
            m_fixture->SetFriction(friction);
        }

        emit frictionChanged();
    }
}

float Box2DItem::restitution() const
{
    return m_restitution;
}

void Box2DItem::setRestitution(const float &restitution)
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

            m_body->SetTransform(b2Vec2((pos.x() + width() / 2.0) / m_scaleRatio,
                                        (-pos.y() - height() / 2.0) / m_scaleRatio),
                                 m_body->GetAngle());
        }
    }

    QQuickItem::geometryChanged(newGeometry, oldGeometry);
}

QVariantList Box2DItem::vertices() const
{
    return m_vertices;
}

void Box2DItem::setVertices(const QVariantList &vertices)
{
    if (m_vertices != vertices) {
        m_vertices.clear(); // XXX it's really needed?
        m_vertices = vertices;

        emit verticesChanged();
    }
}

b2Vec2 Box2DItem::b2TransformOrigin() const
{
    b2Vec2 vec;
    if (m_body)
        vec = m_body->GetPosition();
    return vec;
}

float Box2DItem::b2Angle() const
{
    float32 angle = 0.0f;
    if (m_body)
        angle = m_body->GetAngle();
    return angle;
}
