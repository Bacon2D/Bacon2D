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

#ifndef _BOX2DJOINT_H_
#define _BOX2DJOINT_H_

#include "box2dbase.h"
#include "entity.h"

class Entity;
class b2Joint;

class Box2DJoint : public Box2DBase
{
    Q_OBJECT

    Q_PROPERTY(Entity *entityA READ entityA WRITE setEntityA NOTIFY entityAChanged)
    Q_PROPERTY(Entity *entityB READ entityB WRITE setEntityB NOTIFY entityBChanged)
    Q_PROPERTY(bool collideConnected READ collideConnected WRITE setCollideConnected NOTIFY collideConnectedChanged)
    Q_PROPERTY(QPointF anchorA READ anchorA WRITE setAnchorA NOTIFY anchorAChanged)
    Q_PROPERTY(QPointF anchorB READ anchorB WRITE setAnchorB NOTIFY anchorBChanged)

public:
    Box2DJoint(Scene *parent = 0);
    virtual ~Box2DJoint() {}

    Entity *entityA() const;
    void setEntityA(Entity *entityA);

    Entity *entityB() const;
    void setEntityB(Entity *entityB);

    bool collideConnected() const;
    void setCollideConnected(const bool &collideConnected);

    QPointF anchorA() const { return m_anchorA; }
    void setAnchorA(const QPointF &anchorA);

    QPointF anchorB() const { return m_anchorB; }
    void setAnchorB(const QPointF &anchorB);

signals:
    void entityAChanged();
    void entityBChanged();
    void collideConnectedChanged();
    void anchorAChanged();
    void anchorBChanged();

protected:
    Entity *m_entityA;
    Entity *m_entityB;
    bool m_collideConnected;
    b2Joint *m_joint;
    QPointF m_anchorA;
    QPointF m_anchorB;
};

#endif /* _BOX2DJOINT_H_ */
