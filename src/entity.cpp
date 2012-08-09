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
#include "fixture.h"
#include "material.h"

Entity::Entity(Scene *parent)
    : Box2DBaseItem(parent)
    , m_updateInterval(0)
    , m_scene(0)
    , m_behavior(0)
    , m_body(0)
    , m_linearDamping(0.0f)
    , m_angularDamping(0.0f)
    , m_bodyType(Quasi::StaticBodyType)
    , m_bullet(false)
    , m_sleepingAllowed(true)
    , m_fixedRotation(false)
    , m_active(true)
    , m_sensorFixture(0)
{
    setTransformOrigin(Center);
    connect(this, SIGNAL(rotationChanged()), SLOT(onRotationChanged()));
}

Entity::~Entity()
{
    if (!m_world || !m_body)
        return;

#if QT_VERSION >= 0x050000
    QQuickItem *child;
#else
    QGraphicsItem *child;
#endif

    foreach (child, childItems())
        if (Fixture *fixture = dynamic_cast<Fixture *>(child))
            delete fixture;

    m_worldPtr->DestroyBody(m_body);
    m_body = 0;
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
        if (Entity *item = dynamic_cast<Entity *>(child))
            item->update(delta);
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

void Entity::componentComplete()
{
    if (!m_initialized)
        initialize();
}

b2Body *Entity::body() const
{
    return m_body;
}

void Entity::onRotationChanged()
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
void Entity::initialize()
{
    if (m_initialized || !m_world)
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

    m_body = m_worldPtr->CreateBody(&bodyDef);

    initializeFixtures();

    m_initialized = true;
}

qreal Entity::linearDamping() const
{
    return m_linearDamping;
}

void Entity::setLinearDamping(const qreal &linearDamping)
{
    if (m_linearDamping != linearDamping) {
        m_linearDamping = linearDamping;

        if (m_body)
            m_body->SetLinearDamping(linearDamping);

        emit linearDampingChanged();
    }
}

qreal Entity::angularDamping() const
{
    return m_angularDamping;
}

void Entity::setAngularDamping(const qreal &angularDamping)
{
    if (m_angularDamping != angularDamping) {
        m_angularDamping = angularDamping;

        if (m_body)
            m_body->SetAngularDamping(angularDamping);

        emit angularDampingChanged();
    }
}

Quasi::BodyType Entity::bodyType() const
{
    return m_bodyType;
}

void Entity::setBodyType(const Quasi::BodyType &bodyType)
{
    if (m_bodyType != bodyType) {
        m_bodyType = bodyType;

        if (m_body)
            m_body->SetType((b2BodyType)bodyType);

        emit bodyTypeChanged();
    }
}

bool Entity::bullet() const
{
    return m_bullet;
}

void Entity::setBullet(const bool &bullet)
{
    if (m_bullet != bullet) {
        m_bullet = bullet;

        if (m_body)
            m_body->SetBullet(bullet);

        emit bulletChanged();
    }
}

bool Entity::sleepingAllowed() const
{
    return m_sleepingAllowed;
}

void Entity::setSleepingAllowed(const bool &sleepingAllowed)
{
    if (m_sleepingAllowed != sleepingAllowed) {
        m_sleepingAllowed = sleepingAllowed;

        if (m_body)
            m_body->SetSleepingAllowed(sleepingAllowed);

        emit sleepingAllowedChanged();
    }
}

bool Entity::fixedRotation() const
{
    return m_fixedRotation;
}

void Entity::setFixedRotation(const bool &fixedRotation)
{
    if (m_fixedRotation != fixedRotation) {
        m_fixedRotation = fixedRotation;

        if (m_body)
            m_body->SetFixedRotation(fixedRotation);

        emit fixedRotationChanged();
    }
}

bool Entity::active() const
{
    return m_active;
}

void Entity::setActive(const bool &active)
{
    if (m_active != active) {
        m_active = active;

        if (m_body)
            m_body->SetActive(active);

        emit activeChanged();
    }
}

void Entity::applyTorque(const float &torque)
{
    if (m_body)
        m_body->ApplyTorque(torque);
}

void Entity::applyLinearImpulse(const QPointF &impulse, const QPointF &point)
{
    if (m_body) {
        m_body->ApplyLinearImpulse(b2Vec2(impulse.x() / m_scaleRatio,
                                          -impulse.y() / m_scaleRatio),
                                   b2Vec2(point.x() / m_scaleRatio,
                                          -point.y() / m_scaleRatio));
    }
}

void Entity::setLinearVelocity(const QPointF &velocity)
{
    if (m_body) {
        m_body->SetLinearVelocity(b2Vec2(velocity.x() / m_scaleRatio,
                                         -velocity.y() / m_scaleRatio));
    }
}

void Entity::setAngularVelocity(const float &velocity)
{
    if (m_body) {
        m_body->SetAngularVelocity(velocity);
    }
}

void Entity::geometryChanged(const QRectF &newGeometry,
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

#if QT_VERSION >= 0x050000
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
#else
    QDeclarativeItem::geometryChanged(newGeometry, oldGeometry);
#endif
}

b2Vec2 Entity::b2TransformOrigin() const
{
    b2Vec2 vec;
    if (m_body)
        vec = m_body->GetPosition();

    return vec;
}

float Entity::b2Angle() const
{
    float32 angle = 0.0f;
    if (m_body)
        angle = m_body->GetAngle();
    return angle;
}

void Entity::initializeFixtures()
{
#if QT_VERSION >= 0x050000
    QQuickItem *item;
#else
    QGraphicsItem *item;
#endif

    bool createSensor = true;
    foreach (item, childItems()) {
        if (Fixture *fixture = dynamic_cast<Fixture *>(item)) {
            createSensor = false;
            fixture->setWorld(m_world);
            fixture->setBody(this);
            fixture->initialize();
        }
    }

    if (createSensor)
        createSensorFixture();
}

#if QT_VERSION >= 0x050000
void Entity::itemChange(ItemChange change, const ItemChangeData &data)
#else
QVariant Entity::itemChange(GraphicsItemChange change, const QVariant &value)
#endif
{
    if (isComponentComplete() && change == ItemChildAddedChange) {
#if QT_VERSION >= 0x050000
        QQuickItem *child = data.item;
#else
        QGraphicsItem *child = value.value<QGraphicsItem *>();
#endif
        if (Fixture *fixture = dynamic_cast<Fixture *>(child)) {
            destroySensorFixture();
            fixture->setWorld(m_world);
            fixture->setBody(this);
            fixture->initialize();
        }
    }

#if QT_VERSION >= 0x050000
    Box2DBaseItem::itemChange(change, data);
#else
    return Box2DBaseItem::itemChange(change, value);
#endif
}

void Entity::createSensorFixture()
{
    setBodyType(Quasi::DynamicBodyType);
    m_body->SetGravityScale(0);

    m_sensorFixture = new Fixture(this);
    m_sensorFixture->setMaterial(new Material(this));
    m_sensorFixture->setWidth(width());
    m_sensorFixture->setHeight(height());
    m_sensorFixture->setShapeItem(this);
    m_sensorFixture->setWorld(m_world);
    m_sensorFixture->setBody(this);
    m_sensorFixture->setSensor(true);
    m_sensorFixture->updateFixture();
}

void Entity::destroySensorFixture()
{
    if (!m_sensorFixture)
        return;

    m_sensorFixture->deleteLater();
    m_sensorFixture = 0;
}
