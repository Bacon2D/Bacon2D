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

#ifndef _BOX2DJOINTITEM_H_
#define _BOX2DJOINTITEM_H_

#include "box2dbaseitem.h"
#include "entity.h"

class Entity;
class b2Joint;

class Box2DJointItem : public Box2DBaseItem
{
    Q_OBJECT

    Q_PROPERTY(Entity *bodyA READ bodyA WRITE setBodyA NOTIFY bodyAChanged)
    Q_PROPERTY(Entity *bodyB READ bodyB WRITE setBodyB NOTIFY bodyBChanged)
    Q_PROPERTY(bool collideConnected READ collideConnected WRITE setCollideConnected NOTIFY collideConnectedChanged)

public:
    Box2DJointItem(Scene *parent = 0);
    virtual ~Box2DJointItem() {}

    Entity *bodyA() const;
    void setBodyA(Entity *bodyA);

    Entity *bodyB() const;
    void setBodyB(Entity *bodyB);

    bool collideConnected() const;
    void setCollideConnected(const bool &collideConnected);

signals:
    void bodyAChanged();
    void bodyBChanged();
    void collideConnectedChanged();

protected:
    Entity *m_bodyA;
    Entity *m_bodyB;
    bool m_collideConnected;
    b2Joint *m_joint;
};

#endif /* _BOX2DJOINTITEM_H_ */
