#include "box2ddistancejointitem.h"

#include "box2ditem.h"
#include "util.h"

#include <Box2D/Box2D.h>

Box2DDistanceJointItem::Box2DDistanceJointItem(GameScene *parent)
    : Box2DJointItem(parent)
    , m_joint(0)
{
}

void Box2DDistanceJointItem::initialize(b2World *world)
{
    if (m_initialized || !m_box2ditemA || !m_box2ditemB)
        return;

    if (!m_box2ditemA->initialized())
        m_box2ditemA->initialize(world);
    if (!m_box2ditemB->initialized())
        m_box2ditemB->initialize(world);

    b2DistanceJointDef jointDef;

    jointDef.collideConnected = m_collideConnected;

    jointDef.Initialize(m_box2ditemA->body(),
                        m_box2ditemB->body(),
                        m_box2ditemA->body()->GetWorldCenter(),
                        m_box2ditemB->body()->GetWorldCenter());

    m_joint = static_cast<b2DistanceJoint *>(world->CreateJoint(&jointDef));

    setHeight(length());
    emit lengthChanged();

    m_initialized = true;
}

b2Vec2 Box2DDistanceJointItem::b2TransformOrigin()
{
    b2Vec2 vec;
    if (m_joint)
        vec = b2Util::b2Center(m_joint->GetAnchorA(), m_joint->GetAnchorB());
    return vec;
}

float Box2DDistanceJointItem::b2Angle()
{
    float32 angle = 0.0f;
    if (m_joint)
        angle = b2Util::b2Angle(m_joint->GetAnchorB(), m_joint->GetAnchorA());
    return angle;
}

float Box2DDistanceJointItem::length()
{
    if (m_joint)
        return b2Util::b2Length(m_joint->GetAnchorA(), m_joint->GetAnchorB()) * m_scaleRatio;
    return 0;
}

void Box2DDistanceJointItem::itemChange(ItemChange change, const ItemChangeData &data)
{
    if (change == ItemChildAddedChange) {
        QQuickItem *child = data.item;
        if (width() < child->width())
            setWidth(child->width());
    }

    QQuickItem::itemChange(change, data);
}
