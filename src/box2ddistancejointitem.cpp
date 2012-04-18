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

#include "box2ddistancejointitem.h"

#include "box2ditem.h"
#include "util.h"

#include <Box2D/Box2D.h>

Box2DDistanceJointItem::Box2DDistanceJointItem(Scene *parent)
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

b2Vec2 Box2DDistanceJointItem::b2TransformOrigin() const
{
    b2Vec2 vec;
    if (m_joint)
        vec = b2Util::b2Center(m_joint->GetAnchorA(), m_joint->GetAnchorB());
    return vec;
}

float Box2DDistanceJointItem::b2Angle() const
{
    float32 angle = 0.0f;
    if (m_joint)
        angle = b2Util::b2Angle(m_joint->GetAnchorB(), m_joint->GetAnchorA());
    return angle;
}

float Box2DDistanceJointItem::length() const
{
    if (m_joint)
        return b2Util::b2Length(m_joint->GetAnchorA(), m_joint->GetAnchorB()) * m_scaleRatio;
    return 0;
}

#if QT_VERSION >= 0x050000
void Box2DDistanceJointItem::itemChange(ItemChange change, const ItemChangeData &data)
#else
QVariant Box2DDistanceJointItem::itemChange(GraphicsItemChange change, const QVariant &value)
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
