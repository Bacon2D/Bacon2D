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

#include "entity.h"
#include "game.h"

#if QT_VERSION >= 0x050000
#include <QtQuick/QQuickCanvas>
#else
#include <QtGui/QApplication>
#endif

#include <QtGui/QCursor>

#include <Box2D/Box2D.h>

Box2DMouseJointItem::Box2DMouseJointItem(Scene *parent)
    : Box2DBaseItem(parent)
    , m_joint(0)
    , m_target(0)
    , m_collideConnected(true)
    , m_maxForce(200.0f)
    , m_dummyGround(0)
{
}

Box2DMouseJointItem::~Box2DMouseJointItem()
{
    if (!m_world || !m_joint)
        return;

    if (m_dummyGround) {
        m_worldPtr->DestroyBody(m_dummyGround);
        m_dummyGround = 0;
    }

    m_joint = 0;
}

Entity *Box2DMouseJointItem::target() const
{
    return m_target;
}

void Box2DMouseJointItem::setTarget(Entity *target)
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

void Box2DMouseJointItem::initialize()
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
    return b2Vec2(0, 0);
}

float Box2DMouseJointItem::b2Angle() const
{
    return 0.0f;
}

void Box2DMouseJointItem::synchronize()
{
    if (!m_joint || !m_target)
        return;

    Box2DBaseItem::synchronize();

    QPoint mousePos;

#if QT_VERSION >= 0x050000
    mousePos = canvas()->mapFromGlobal(QCursor::pos());
#else
    m_mousePos = QCursor::pos();
    QWidget *widget = QApplication::widgetAt(m_mousePos);

    if (widget)
        mousePos = widget->mapFromGlobal(m_mousePos);
    else
        mousePos = m_mousePos;
    m_mousePos = mousePos;
#endif

    m_joint->SetTarget(b2Vec2(mousePos.x() / m_scaleRatio, -mousePos.y() / m_scaleRatio));
}
