#ifndef _BOX2DITEN_H_
#define _BOX2DITEN_H_

#include "box2dbaseitem.h"
#include "gameitem.h"

class GameScene;
class b2World;
class b2Body;
class b2Fixture;

class Box2DItem : public Box2DBaseItem
{
    Q_OBJECT

    Q_ENUMS(BodyType Shape)
    Q_PROPERTY(qreal linearDamping READ linearDamping WRITE setLinearDamping NOTIFY linearDampingChanged)
    Q_PROPERTY(qreal angularDamping READ angularDamping WRITE setAngularDamping NOTIFY angularDampingChanged)
    Q_PROPERTY(BodyType bodyType READ bodyType WRITE setBodyType NOTIFY bodyTypeChanged)
    Q_PROPERTY(Shape shape READ shape WRITE setShape NOTIFY shapeChanged)
    Q_PROPERTY(bool bullet READ bullet WRITE setBullet NOTIFY bulletChanged)
    Q_PROPERTY(bool sleepingAllowed READ sleepingAllowed WRITE setSleepingAllowed NOTIFY sleepingAllowedChanged)
    Q_PROPERTY(bool fixedRotation READ fixedRotation WRITE setFixedRotation NOTIFY fixedRotationChanged)
    Q_PROPERTY(bool active READ active WRITE setActive)
    Q_PROPERTY(qreal density READ density WRITE setDensity NOTIFY densityChanged)
    Q_PROPERTY(qreal friction READ friction WRITE setFriction NOTIFY frictionChanged)
    Q_PROPERTY(qreal restitution READ restitution WRITE setRestitution NOTIFY restitutionChanged)
    Q_PROPERTY(QVariantList vertices READ vertices WRITE setVertices NOTIFY verticesChanged)

public:
    enum BodyType {
        Static,
        Kinematic,
        Dynamic
    };
    enum Shape {
        Rectangle,
        Polygon,
        Circle
    };

    Box2DItem(GameScene *parent = 0);

    b2Body *body() const;

    qreal linearDamping() const;
    void setLinearDamping(const qreal &linearDamping);

    qreal angularDamping() const;
    void setAngularDamping(const qreal &angularDamping);

    BodyType bodyType() const;
    void setBodyType(const BodyType &bodyType);

    Shape shape() const;
    void setShape(const Shape &shape);

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

    void initialize(b2World *world);

    b2Vec2 b2TransformOrigin() const;

    float b2Angle() const;

    Q_INVOKABLE void applyTorque(const float &torque);
    Q_INVOKABLE void applyLinearImpulse(const QPointF &impulse, const QPointF &point);

protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

private slots:
    void onRotationChanged();

signals:
    void activeChanged();
    void linearDampingChanged();
    void angularDampingChanged();
    void bodyTypeChanged();
    void shapeChanged();
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
    BodyType m_bodyType;
    Shape m_shape;
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

#endif /* _BOX2DITEN_H_ */
