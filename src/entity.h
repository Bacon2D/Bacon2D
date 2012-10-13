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

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "enums.h"
#include "box2dbase.h"

#include <QtCore/QtGlobal>
#include <QtCore/QTime>

class Game;
class Scene;
class Behavior;
class Fixture;

class Entity : public Box2DBase
{
    Q_OBJECT

    Q_PROPERTY(int updateInterval READ updateInterval WRITE setUpdateInterval NOTIFY updateIntervalChanged)
    Q_PROPERTY(Game *game READ game)
    Q_PROPERTY(Behavior *behavior READ behavior WRITE setBehavior NOTIFY behaviorChanged)
    Q_PROPERTY(qreal linearDamping READ linearDamping WRITE setLinearDamping NOTIFY linearDampingChanged)
    Q_PROPERTY(qreal angularDamping READ angularDamping WRITE setAngularDamping NOTIFY angularDampingChanged)
    Q_PROPERTY(Quasi::EntityType entityType READ entityType WRITE setEntityType NOTIFY entityTypeChanged)
    Q_PROPERTY(bool bullet READ bullet WRITE setBullet NOTIFY bulletChanged)
    Q_PROPERTY(bool sleepingAllowed READ sleepingAllowed WRITE setSleepingAllowed NOTIFY sleepingAllowedChanged)
    Q_PROPERTY(bool fixedRotation READ fixedRotation WRITE setFixedRotation NOTIFY fixedRotationChanged)
    Q_PROPERTY(bool active READ active WRITE setActive)

public:
    Entity(Scene *parent = 0);
    ~Entity();

    int updateInterval() const;
    void setUpdateInterval(const int &updateInterval);

    Scene *scene() const;
    void setScene(Scene *scene);

    Game *game() const;

    Behavior *behavior() const;
    void setBehavior(Behavior *behavior);

    virtual void update(const int &delta);

    b2Body *body() const;

    qreal linearDamping() const;
    void setLinearDamping(const qreal &linearDamping);

    qreal angularDamping() const;
    void setAngularDamping(const qreal &angularDamping);

    Quasi::EntityType entityType() const;
    void setEntityType(const Quasi::EntityType &entityType);

    bool bullet() const;
    void setBullet(const bool &bullet);

    bool sleepingAllowed() const;
    void setSleepingAllowed(const bool &allowed);

    bool fixedRotation() const;
    void setFixedRotation(const bool &fixedRotation);

    bool active() const;
    void setActive(const bool &active);

    void initialize();

    b2Vec2 b2TransformOrigin() const;
    float b2Angle() const;

    Q_INVOKABLE void applyTorque(const float &torque);
    Q_INVOKABLE void applyLinearImpulse(const QPointF &impulse, const QPointF &point);
    Q_INVOKABLE void setLinearVelocity(const QPointF &velocity);
    Q_INVOKABLE void setAngularVelocity(const float &velocity);

protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);
#if QT_VERSION >= 0x050000
    virtual void itemChange(ItemChange change, const ItemChangeData &data);
#else
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);
#endif
    void componentComplete();

signals:
    void updateIntervalChanged();
    void behaviorChanged();
    void activeChanged();
    void linearDampingChanged();
    void angularDampingChanged();
    void entityTypeChanged();
    void bulletChanged();
    void sleepingAllowedChanged();
    void fixedRotationChanged();
    void linearVelocityChanged();

private slots:
    void onRotationChanged();

private:
    void initializeFixtures();
    void createSensorFixture();
    void destroySensorFixture();

private:
    int m_updateInterval;
    QTime m_updateTime;
    Scene *m_scene;
    Behavior *m_behavior;
    b2Body *m_body;
    qreal m_linearDamping;
    qreal m_angularDamping;
    Quasi::EntityType m_entityType;
    bool m_bullet;
    bool m_sleepingAllowed;
    bool m_fixedRotation;
    bool m_active;
    Fixture *m_sensorFixture;
};

#endif /* _ENTITY_H_ */
