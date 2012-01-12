#include "box2ddistancejointitem.h"

#include "box2ditem.h"

#include <Box2D/Box2D.h>

#include <QDebug>

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

    m_joint = new b2DistanceJointDef;

    m_joint->Initialize(m_box2ditemA->body(),
                        m_box2ditemB->body(),
                        m_box2ditemA->body()->GetWorldCenter(),
                        m_box2ditemB->body()->GetWorldCenter());

    world->CreateJoint(m_joint); // TODO store the joint

    m_initialized = true;
}
