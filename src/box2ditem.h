#ifndef _BOX2DITEN_H_
#define _BOX2DITEN_H_

#include "gameitem.h"

class GameScene;
class b2World;
class b2Body;
class b2FixtureDef;

class Box2DItem : public GameItem
{
    Q_OBJECT

    Q_ENUMS(BodyType)
    Q_PROPERTY(qreal linearDamping READ linearDamping WRITE setLinearDamping NOTIFY linearDampingChanged)
    Q_PROPERTY(qreal angularDamping READ angularDamping WRITE setAngularDamping NOTIFY angularDampingChanged)
    Q_PROPERTY(BodyType bodyType READ bodyType WRITE setBodyType NOTIFY bodyTypeChanged)
    Q_PROPERTY(bool bullet READ bullet WRITE setBullet NOTIFY bulletChanged)
    Q_PROPERTY(bool sleepingAllowed READ sleepingAllowed WRITE setSleepingAllowed NOTIFY sleepingAllowedChanged)
    Q_PROPERTY(bool fixedRotation READ fixedRotation WRITE setFixedRotation NOTIFY fixedRotationChanged)
    Q_PROPERTY(bool active READ active WRITE setActive)

public:
    enum BodyType {
        Static,
        Kinematic,
        Dynamic
    };

    Box2DItem(GameScene *parent = 0);

    b2Body *body();

    qreal linearDamping() const;
    void setLinearDamping(qreal linearDamping);

    qreal angularDamping() const;
    void setAngularDamping(qreal angularDamping);

    BodyType bodyType() const;
    void setBodyType(BodyType bodyType);

    bool bullet() const;
    void setBullet(bool bullet);

    bool sleepingAllowed() const;
    void setSleepingAllowed(bool allowed);

    bool fixedRotation() const;
    void setFixedRotation(bool fixedRotation);

    bool active() const;
    void setActive(bool active);

    void synchronize();

    void initialize(b2World *world);

    Q_INVOKABLE void applyTorque(float torque);
    Q_INVOKABLE void applyLinearImpulse(QPointF impulse, QPointF point);

private slots:
    void onRotationChanged();

signals:
    void activeChanged();
    void linearDampingChanged();
    void angularDampingChanged();
    void bodyTypeChanged();
    void bulletChanged();
    void sleepingAllowedChanged();
    void fixedRotationChanged();
    void linearVelocityChanged();

private:
    b2Body *m_body;
    bool m_synchronizing;
    qreal m_linearDamping;
    qreal m_angularDamping;
    BodyType m_bodyType;
    bool m_bullet;
    bool m_sleepingAllowed;
    bool m_fixedRotation;
    bool m_active;
    b2FixtureDef *m_fixtureDef;
};

#endif /* _BOX2DITEN_H_ */
