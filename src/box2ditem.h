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

#ifndef _BOX2DITEM_H_
#define _BOX2DITEM_H_

#include "box2dbaseitem.h"
#include "enums.h"
#include "entity.h"

#include <QtCore/QtGlobal>

class Scene;
class b2World;
class b2Body;
class b2Fixture;

class Box2DItem : public Box2DBaseItem
{
    Q_OBJECT

    Q_PROPERTY(qreal linearDamping READ linearDamping WRITE setLinearDamping NOTIFY linearDampingChanged)
    Q_PROPERTY(qreal angularDamping READ angularDamping WRITE setAngularDamping NOTIFY angularDampingChanged)
    Q_PROPERTY(Quasi::BodyType bodyType READ bodyType WRITE setBodyType NOTIFY bodyTypeChanged)
    Q_PROPERTY(Quasi::BodyShape shapeGeometry READ shapeGeometry WRITE setShapeGeometry NOTIFY shapeGeometryChanged)
    Q_PROPERTY(bool bullet READ bullet WRITE setBullet NOTIFY bulletChanged)
    Q_PROPERTY(bool sleepingAllowed READ sleepingAllowed WRITE setSleepingAllowed NOTIFY sleepingAllowedChanged)
    Q_PROPERTY(bool fixedRotation READ fixedRotation WRITE setFixedRotation NOTIFY fixedRotationChanged)
    Q_PROPERTY(bool active READ active WRITE setActive)
    Q_PROPERTY(qreal density READ density WRITE setDensity NOTIFY densityChanged)
    Q_PROPERTY(qreal friction READ friction WRITE setFriction NOTIFY frictionChanged)
    Q_PROPERTY(qreal restitution READ restitution WRITE setRestitution NOTIFY restitutionChanged)
    Q_PROPERTY(QVariantList vertices READ vertices WRITE setVertices NOTIFY verticesChanged)

public:
    Box2DItem(Scene *parent = 0);
    ~Box2DItem();

    b2Body *body() const;

    qreal linearDamping() const;
    void setLinearDamping(const qreal &linearDamping);

    qreal angularDamping() const;
    void setAngularDamping(const qreal &angularDamping);

    Quasi::BodyType bodyType() const;
    void setBodyType(const Quasi::BodyType &bodyType);

    Quasi::BodyShape shapeGeometry() const;
    void setShapeGeometry(const Quasi::BodyShape &shape);

    bool bullet() const;
    void setBullet(const bool &bullet);

    bool sleepingAllowed() const;
    void setSleepingAllowed(const bool &allowed);

    bool fixedRotation() const;
    void setFixedRotation(const bool &fixedRotation);

    bool active() const;
    void setActive(const bool &active);

    float density() const;
    void setDensity(const float &density);

    float friction() const;
    void setFriction(const float &friction);

    float restitution() const;
    void setRestitution(const float &restitution);

    QVariantList vertices() const;
    void setVertices(const QVariantList &vertices);

    void initialize();

    b2Vec2 b2TransformOrigin() const;

    float b2Angle() const;

    void componentComplete();

    Q_INVOKABLE void applyTorque(const float &torque);
    Q_INVOKABLE void applyLinearImpulse(const QPointF &impulse, const QPointF &point);
    Q_INVOKABLE void setLinearVelocity(const QPointF &velocity);

protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

private slots:
    void onRotationChanged();

signals:
    void activeChanged();
    void linearDampingChanged();
    void angularDampingChanged();
    void bodyTypeChanged();
    void shapeGeometryChanged();
    void bulletChanged();
    void sleepingAllowedChanged();
    void fixedRotationChanged();
    void linearVelocityChanged();
    void densityChanged();
    void frictionChanged();
    void restitutionChanged();
    void verticesChanged();

private:
    b2Body *m_body;
    qreal m_linearDamping;
    qreal m_angularDamping;
    Quasi::BodyType m_bodyType;
    Quasi::BodyShape m_shape;
    bool m_bullet;
    bool m_sleepingAllowed;
    bool m_fixedRotation;
    bool m_active;
    b2Fixture *m_fixture;
    float m_density;
    float m_friction;
    float m_restitution;
    QVariantList m_vertices;
};

#endif /* _BOX2DITEM_H_ */
