#ifndef _BOX2DJOINTITEM_H_
#define _BOX2DJOINTITEM_H_

#include "box2dbaseitem.h"
#include "gameitem.h"

class Box2DItem;

class Box2DJointItem : public Box2DBaseItem
{
    Q_OBJECT

    Q_PROPERTY(Box2DItem *box2ditemA READ box2ditemA WRITE setBox2ditemA NOTIFY box2ditemAChanged)
    Q_PROPERTY(Box2DItem *box2ditemB READ box2ditemB WRITE setBox2ditemB NOTIFY box2ditemBChanged)
    Q_PROPERTY(bool collideConnected READ collideConnected WRITE setCollideConnected NOTIFY collideConnectedChanged)

public:
    Box2DJointItem(GameScene *parent = 0);

    Box2DItem *box2ditemA();
    void setBox2ditemA(Box2DItem *box2ditemA);

    Box2DItem *box2ditemB();
    void setBox2ditemB(Box2DItem *box2ditemB);

    bool collideConnected();
    void setCollideConnected(bool collideConnected);

signals:
    void box2ditemAChanged();
    void box2ditemBChanged();
    void collideConnectedChanged();

protected:
    Box2DItem *m_box2ditemA;
    Box2DItem *m_box2ditemB;
    bool m_collideConnected;
};

#endif /* _BOX2DJOINTITEM_H_ */
