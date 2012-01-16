#include "box2dmousejointitem.h"

#include "box2dscene.h"
#include "box2ditem.h"

#include <QCursor>
#include <QQuickCanvas>
#include <Box2D/Box2D.h>

Box2DMouseJointItem::Box2DMouseJointItem(GameScene *parent)
    : Box2DBaseItem(parent)
    , m_target(0)
    , m_collideConnected(true)
    , m_maxForce(200.0f)
{
}

Box2DItem *Box2DMouseJointItem::target()
{
    return m_target;
}

void Box2DMouseJointItem::setTarget(Box2DItem *target)
{
    if (m_target != target) {
        m_target = target;

        emit targetChanged();
    }
}

void Box2DMouseJointItem::initialize(b2World *world)
{
    if (m_initialized || !m_target)
        return;

    if (!m_target->initialized())
        m_target->initialize(world);

    b2BodyDef groundBodyDef; // dummy body
    b2Body *groundBody = world->CreateBody(&groundBodyDef);

    b2MouseJointDef jointDef;

    jointDef.collideConnected = m_collideConnected;
    jointDef.bodyA = groundBody;
    jointDef.bodyB = m_target->body();
    jointDef.target = m_target->body()->GetWorldCenter();
    jointDef.maxForce = m_maxForce * m_target->body()->GetMass();

    m_joint = static_cast<b2MouseJoint *>(world->CreateJoint(&jointDef));

    m_initialized = true;
}

void Box2DMouseJointItem::update(long delta)
{
    if (!m_joint)
        return;

    GameItem::update(delta);

    QPointF mousePos = mapToScene(scene()->canvas()->mapFromGlobal(QCursor::pos()));
    m_joint->SetTarget(b2Vec2(mousePos.x() / scaleRatio, -mousePos.y() / scaleRatio));
}

bool Box2DMouseJointItem::collideConnected()
{
    return m_collideConnected;
}

void Box2DMouseJointItem::setCollideConnected(bool collideConnected)
{
    if (m_collideConnected != collideConnected) {
        m_collideConnected = collideConnected;

        emit collideConnectedChanged();
    }
}
