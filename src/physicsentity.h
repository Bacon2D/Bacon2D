#ifndef PHYSICSENTITY_H
#define PHYSICSENTITY_H

#include <QObject>
#include <entity.h>

class QPointF;
class Box2DBody;
typedef Box2DBody Body;

/**
* @brief
*/
class PhysicsEntity : public Entity
{
    Q_OBJECT
    Q_PROPERTY(Body* body READ body WRITE setBody NOTIFY bodyChanged)
public:
    PhysicsEntity(QQuickItem* parent = nullptr);
    void setBody(Body* body);
    Body* body() {  return mBody; }

public slots:
    void applyForce(QPointF force,QPointF point);
    void applyForceToCenter(QPointF force);
    void applyTorque(qreal torque);
    void applyLinearImpulse(QPointF impulse, QPointF point);
    void applyAngularImpulse(qreal torque);
    QPointF getWorldCenter();
    QPointF getLocalCenter();
    float getMass();
    void resetMassData();
    float getInertia();
    QPointF toWorldPoint(QPointF localPoint);
    QPointF toWorldVector(QPointF localVector);
    QPointF toLocalPoint(QPointF worlPoint);
    QPointF toLocalVector(QPointF worldVector);
    QPointF getLinearVelocityFromWorldPoint(QPointF point);
    QPointF getLinearVelocityFromLocalPoint(QPointF point);
signals:
    void bodyChanged(Body* body);
private:
    Body* mBody;
};

#endif // PHYSICSENTITY_H
