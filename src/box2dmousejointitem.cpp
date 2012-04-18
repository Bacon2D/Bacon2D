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

#include "box2dmousejointitem.h"

#include "box2ditem.h"
#include "box2dscene.h"
#include "game.h"

#include <Box2D/Box2D.h>

#include <QtGui/QCursor>

Box2DMouseJointItem::Box2DMouseJointItem(Scene *parent)
    : Box2DBaseItem(parent)
    , m_target(0)
    , m_collideConnected(true)
    , m_maxForce(200.0f)
{
    m_synchronize = false;
}

Box2DItem *Box2DMouseJointItem::target() const
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

float Box2DMouseJointItem::maxForce() const
{
    return m_maxForce;
}

void Box2DMouseJointItem::setMaxForce(const float &maxForce)
{
    if (m_maxForce != maxForce) {
        m_maxForce = maxForce;

        if (m_joint)
            m_joint->SetMaxForce(maxForce);

        emit maxForceChanged();
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

void Box2DMouseJointItem::update(const long &delta)
{
    if (!m_joint)
        return;

    Entity::update(delta);

    QPointF mousePos = game()->mouse();
    m_joint->SetTarget(b2Vec2(mousePos.x() / m_scaleRatio, -mousePos.y() / m_scaleRatio));
}

bool Box2DMouseJointItem::collideConnected() const
{
    return m_collideConnected;
}

void Box2DMouseJointItem::setCollideConnected(const bool &collideConnected)
{
    if (m_collideConnected != collideConnected) {
        m_collideConnected = collideConnected;

        emit collideConnectedChanged();
    }
}

b2Vec2 Box2DMouseJointItem::b2TransformOrigin() const
{
    return b2Vec2(0, 0); // FIXME: remove "m_syncronize" member and return correct position
}

float Box2DMouseJointItem::b2Angle() const
{
    return 0.0f;
}
