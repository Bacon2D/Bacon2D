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

#include "box2dmousejoint.h"

#include "entity.h"
#include "game.h"

#include <QtQuick/QQuickWindow>

#include <QtGui/QCursor>

#include <Box2D/Box2D.h>

Box2DMouseJoint::Box2DMouseJoint(Scene *parent)
    : Box2DBase(parent)
    , m_joint(0)
    , m_target(0)
    , m_collideConnected(true)
    , m_maxForce(200.0f)
    , m_dummyGround(0)
{
}

Box2DMouseJoint::~Box2DMouseJoint()
{
    if (!m_world || !m_joint)
        return;

    if (m_dummyGround) {
        m_worldPtr->DestroyBody(m_dummyGround);
        m_dummyGround = 0;
    }

    m_joint = 0;
}

Entity *Box2DMouseJoint::target() const
{
    return m_target;
}

void Box2DMouseJoint::setTarget(Entity *target)
{
    if (m_target != target) {
        m_target = target;

        emit targetChanged();
    }
}

float Box2DMouseJoint::maxForce() const
{
    return m_maxForce;
}

void Box2DMouseJoint::setMaxForce(const float &maxForce)
{
    if (m_maxForce != maxForce) {
        m_maxForce = maxForce;

        if (m_joint)
            m_joint->SetMaxForce(maxForce);

        emit maxForceChanged();
    }
}

void Box2DMouseJoint::initialize()
{
    if (m_initialized || !m_world || !m_target)
        return;

    if (!m_target->initialized()) {
        m_target->setWorld(m_world);
        m_target->initialize();

    }

    b2BodyDef groundBodyDef; // dummy body

    m_dummyGround = m_worldPtr->CreateBody(&groundBodyDef);

    b2MouseJointDef jointDef;

    jointDef.collideConnected = m_collideConnected;
    jointDef.bodyA = m_dummyGround;
    jointDef.bodyB = m_target->body();
    jointDef.target = m_target->body()->GetWorldCenter();
    jointDef.maxForce = m_maxForce * m_target->body()->GetMass();

    m_joint = static_cast<b2MouseJoint *>(m_worldPtr->CreateJoint(&jointDef));

    m_initialized = true;
}

bool Box2DMouseJoint::collideConnected() const
{
    return m_collideConnected;
}

void Box2DMouseJoint::setCollideConnected(const bool &collideConnected)
{
    if (m_collideConnected != collideConnected) {
        m_collideConnected = collideConnected;

        emit collideConnectedChanged();
    }
}

b2Vec2 Box2DMouseJoint::b2TransformOrigin() const
{
    return b2Vec2(0, 0);
}

float Box2DMouseJoint::b2Angle() const
{
    return 0.0f;
}

void Box2DMouseJoint::synchronize()
{
    if (!m_joint || !m_target)
        return;

    Box2DBase::synchronize();

    QPoint mousePos;

    mousePos = window()->mapFromGlobal(QCursor::pos());

    m_joint->SetTarget(b2Vec2(mousePos.x() / m_scaleRatio, -mousePos.y() / m_scaleRatio));
}
