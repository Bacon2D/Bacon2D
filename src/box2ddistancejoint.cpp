/**
 * Copyright (C) 2012 by INdT
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * @author Rodrigo Goncalves de Oliveira <rodrigo.goncalves@openbossa.org>
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

#include "box2ddistancejoint.h"

#include "util.h"

#include <Box2D/Box2D.h>

Box2DDistanceJoint::Box2DDistanceJoint(Scene *parent)
    : Box2DJoint(parent)
{
}

Box2DDistanceJoint::~Box2DDistanceJoint()
{
    if (!m_world || !m_joint)
        return;

    m_joint = 0;
}

void Box2DDistanceJoint::initialize()
{
    if (m_initialized || !m_entityA || !m_entityB || !m_world)
        return;
    if (!m_entityA->initialized())
        return;
    if (!m_entityB->initialized())
        return;

    b2DistanceJointDef jointDef;

    jointDef.collideConnected = m_collideConnected;

    jointDef.Initialize(m_entityA->body(),
                        m_entityB->body(),
                        m_entityA->body()->GetWorldCenter() + b2Util::b2Vec(m_anchorA, m_scaleRatio),
                        m_entityB->body()->GetWorldCenter() + b2Util::b2Vec(m_anchorB, m_scaleRatio));

    m_joint = static_cast<b2DistanceJoint *>(m_worldPtr->CreateJoint(&jointDef));

    setHeight(length());
    emit lengthChanged();

    m_initialized = true;
}

b2Vec2 Box2DDistanceJoint::b2TransformOrigin() const
{
    b2Vec2 vec;
    if (m_joint)
        vec = b2Util::b2Center(m_joint->GetAnchorA(), m_joint->GetAnchorB());
    return vec;
}

float Box2DDistanceJoint::b2Angle() const
{
    float32 angle = 0.0f;
    if (m_joint)
        angle = b2Util::b2Angle(m_joint->GetAnchorB(), m_joint->GetAnchorA());
    return angle;
}

float Box2DDistanceJoint::length() const
{
    if (m_joint)
        return b2Util::b2Length(m_joint->GetAnchorA(), m_joint->GetAnchorB()) * m_scaleRatio;
    return 0;
}

#if QT_VERSION >= 0x050000
void Box2DDistanceJoint::itemChange(ItemChange change, const ItemChangeData &data)
#else
QVariant Box2DDistanceJoint::itemChange(GraphicsItemChange change, const QVariant &value)
#endif
{
    if (change == ItemChildAddedChange) {
#if QT_VERSION >= 0x050000
        QQuickItem *child = data.item;
#else
        QDeclarativeItem *child = value.value<QDeclarativeItem *>();
#endif
        if (width() < child->width())
            setWidth(child->width());
    }

#if QT_VERSION >= 0x050000
    QQuickItem::itemChange(change, data);
#else
    return QDeclarativeItem::itemChange(change, value);
#endif
}
