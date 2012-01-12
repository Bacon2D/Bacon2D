#ifndef _BOX2DDISTANCEJOINTITEM_H_
#define _BOX2DDISTANCEJOINTITEM_H_

#include "box2djointitem.h"

class b2DistanceJointDef;

class Box2DDistanceJointItem : public Box2DJointItem
{
    Q_OBJECT

public:
    Box2DDistanceJointItem(GameScene *parent = 0);

    void initialize(b2World *world);

private:
    b2DistanceJointDef *m_joint;
};

#endif /* _BOX2DDISTANCEJOINTITEM_H_ */
