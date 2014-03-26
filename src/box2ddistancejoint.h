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

#ifndef _BOX2DDISTANCEJOINT_H_
#define _BOX2DDISTANCEJOINT_H_

#include "box2djoint.h"

#include <QtCore/QtGlobal>

class b2DistanceJoint;

class Box2DDistanceJoint : public Box2DJoint
{
    Q_OBJECT

    Q_PROPERTY(float length READ length NOTIFY lengthChanged)

public:
    Box2DDistanceJoint(Scene *parent = 0);
    ~Box2DDistanceJoint();

    void initialize();

    b2Vec2 b2TransformOrigin() const;

    float b2Angle() const;

    float length() const;

protected:
    void itemChange(ItemChange change, const ItemChangeData &data);

signals:
    void lengthChanged();
};

#endif /* _BOX2DDISTANCEJOINT_H_ */
