#include "box2djointitem.h"

#include "box2ditem.h"

Box2DJointItem::Box2DJointItem(GameScene *parent)
    : Box2DBaseItem(parent)
    , m_box2ditemA(0)
    , m_box2ditemB(0)
    , m_collideConnected(true)
{

}

Box2DItem *Box2DJointItem::box2ditemA()
{
    return m_box2ditemA;
}

void Box2DJointItem::setBox2ditemA(Box2DItem *box2ditemA)
{
    if (m_box2ditemA != box2ditemA) {
        m_box2ditemA = box2ditemA;

        emit box2ditemAChanged();
    }
}

Box2DItem *Box2DJointItem::box2ditemB()
{
    return m_box2ditemB;
}

void Box2DJointItem::setBox2ditemB(Box2DItem *box2ditemB)
{
    if (m_box2ditemB != box2ditemB) {
        m_box2ditemB = box2ditemB;

        emit box2ditemBChanged();
    }
}

bool Box2DJointItem::collideConnected()
{
    return m_collideConnected;
}

void Box2DJointItem::setCollideConnected(bool collideConnected)
{
    if (m_collideConnected != collideConnected) {
        m_collideConnected = collideConnected;

        emit collideConnectedChanged();
    }
}
