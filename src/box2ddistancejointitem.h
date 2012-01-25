#ifndef _BOX2DDISTANCEJOINTITEM_H_
#define _BOX2DDISTANCEJOINTITEM_H_

#include "box2djointitem.h"

class b2DistanceJoint;

class Box2DDistanceJointItem : public Box2DJointItem
{
    Q_OBJECT

    Q_PROPERTY(float length READ length NOTIFY lengthChanged)

public:
    Box2DDistanceJointItem(GameScene *parent = 0);

    void initialize(b2World *world);

    b2Vec2 b2TransformOrigin() const;

    float b2Angle() const;

    float length() const;

protected:
    void itemChange(ItemChange change, const ItemChangeData &data);

signals:
    void lengthChanged();

private:
    b2DistanceJoint *m_joint;
};

#endif /* _BOX2DDISTANCEJOINTITEM_H_ */
