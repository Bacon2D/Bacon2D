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

#include "box2djointitem.h"

Box2DJointItem::Box2DJointItem(Scene *parent)
    : Box2DBaseItem(parent)
    , m_entityA(0)
    , m_entityB(0)
    , m_collideConnected(true)
    , m_joint(0)
{
}

Entity *Box2DJointItem::entityA() const
{
    return m_entityA;
}

void Box2DJointItem::setEntityA(Entity *entityA)
{
    if (m_entityA != entityA) {
        m_entityA = entityA;

        emit entityAChanged();
    }
}

Entity *Box2DJointItem::entityB() const
{
    return m_entityB;
}

void Box2DJointItem::setEntityB(Entity *entityB)
{
    if (m_entityB != entityB) {
        m_entityB = entityB;

        emit entityBChanged();
    }
}

bool Box2DJointItem::collideConnected() const
{
    return m_collideConnected;
}

void Box2DJointItem::setCollideConnected(const bool &collideConnected)
{
    if (m_collideConnected != collideConnected) {
        m_collideConnected = collideConnected;

        emit collideConnectedChanged();
    }
}
