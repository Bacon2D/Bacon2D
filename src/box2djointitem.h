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

    Q_PROPERTY(Entity *entityA READ entityA WRITE setEntityA NOTIFY entityAChanged)
    Q_PROPERTY(Entity *entityB READ entityB WRITE setEntityB NOTIFY entityBChanged)
    Q_PROPERTY(bool collideConnected READ collideConnected WRITE setCollideConnected NOTIFY collideConnectedChanged)

public:
    Box2DJointItem(Scene *parent = 0);
    virtual ~Box2DJointItem() {}

    Entity *entityA() const;
    void setEntityA(Entity *entityA);

    Entity *entityB() const;
    void setEntityB(Entity *entityB);

    bool collideConnected() const;
    void setCollideConnected(const bool &collideConnected);

signals:
    void entityAChanged();
    void entityBChanged();
    void collideConnectedChanged();

protected:
    Entity *m_entityA;
    Entity *m_entityB;
    bool m_collideConnected;
    b2Joint *m_joint;
};

#endif /* _BOX2DJOINTITEM_H_ */
