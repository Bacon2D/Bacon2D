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

#include "box2ditem.h"

Box2DJointItem::Box2DJointItem(GameScene *parent)
    : Box2DBaseItem(parent)
    , m_box2ditemA(0)
    , m_box2ditemB(0)
    , m_collideConnected(true)
{

}

Box2DItem *Box2DJointItem::box2ditemA() const
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

Box2DItem *Box2DJointItem::box2ditemB() const
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
