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

#ifndef _BOX2DMOUSEJOINTITEM_H_
#define _BOX2DMOUSEJOINTITEM_H_

#include "box2dbaseitem.h"

class b2MouseJoint;
class Box2DItem;

class Box2DMouseJointItem : public Box2DBaseItem
{
    Q_OBJECT

    Q_PROPERTY(Box2DItem *target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(bool collideConnected READ collideConnected WRITE setCollideConnected NOTIFY collideConnectedChanged)
    Q_PROPERTY(float maxForce READ maxForce WRITE setMaxForce NOTIFY maxForceChanged)

public:
    Box2DMouseJointItem(Scene *parent = 0);

    Box2DItem *target() const;
    void setTarget(Box2DItem *target);

    bool collideConnected() const;
    void setCollideConnected(const bool &collideConnected);

    float maxForce() const;
    void setMaxForce(const float &maxForce);

    void initialize(b2World *world);

    void update(const long &delta);

    b2Vec2 b2TransformOrigin() const;

    float b2Angle() const;

signals:
    void targetChanged();
    void collideConnectedChanged();
    void maxForceChanged();

private:
    b2MouseJoint *m_joint;
    Box2DItem *m_target;
    bool m_collideConnected;
    float m_maxForce;
};

#endif /* _BOX2DMOUSEJOINTITEM_H_ */
