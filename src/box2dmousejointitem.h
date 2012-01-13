#ifndef _BOX2DMOUSEJOINTITEM_H_
#define _BOX2DMOUSEJOINTITEM_H_

#include "box2dbaseitem.h"

class b2MouseJointDef;
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

    Box2DItem *target();
    void setTarget(Box2DItem *target);

    bool collideConnected();
    void setCollideConnected(bool collideConnected);

    float maxForce();
    void setMaxForce(float maxForce);

    void initialize(b2World *world);
    void update(long delta);

signals:
    void targetChanged();
    void collideConnectedChanged();
    void maxForceChanged();

private:
    b2MouseJointDef *m_jointDef;
    b2MouseJoint *m_joint;
    Box2DItem *m_target;
    bool m_collideConnected;
    float m_maxForce;
};

#endif /* _BOX2DMOUSEJOINTITEM_H_ */
