#ifndef _BOX2DMOUSEJOINTITEM_H_
#define _BOX2DMOUSEJOINTITEM_H_

#include "box2dbaseitem.h"

class b2MouseJoint;
class Box2DItem;

class Box2DMouseJointItem : public Box2DBaseItem
{
    Q_OBJECT

    Q_PROPERTY(Box2DItem *target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(bool collideConnected READ collideConnected WRITE setCollideConnected NOTIFY collideConnectedChanged)
    Q_PROPERTY(float maxForce READ maxForce WRITE setMaxForce NOTIFY maxForceChanged)

public:
    Box2DMouseJointItem(GameScene *parent = 0);

    Box2DItem *target() const;
    void setTarget(Box2DItem *target);

    bool collideConnected() const;
    void setCollideConnected(const bool &collideConnected);

    float maxForce() const;
    void setMaxForce(const float &maxForce);

    void initialize(b2World *world);

    void update(const long &delta);

    b2Vec2 b2TransformOrigin() const;

    float b2Angle() const;

signals:
    void targetChanged();
    void collideConnectedChanged();
    void maxForceChanged();

private:
    b2MouseJoint *m_joint;
    Box2DItem *m_target;
    bool m_collideConnected;
    float m_maxForce;
};

#endif /* _BOX2DMOUSEJOINTITEM_H_ */
