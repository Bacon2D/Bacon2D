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

#ifndef _BOX2DBASE_H_
#define _BOX2DBASE_H_

#include "quasideclarativeitem.h"

#include <Box2D/Box2D.h>

class Scene;

class Box2DBase : public QuasiDeclarativeItem
{
    Q_OBJECT

public:
    Box2DBase(Scene *parent = 0);
    virtual ~Box2DBase() {}

    static float m_scaleRatio;

    void setWorld(QSharedPointer<b2World> world);

    bool initialized() const;
    virtual void initialize() = 0;

    virtual void synchronize();

protected:
    virtual b2Vec2 b2TransformOrigin() const = 0;
    virtual float b2Angle() const = 0;

protected:
    bool m_initialized;
    bool m_synchronizing;
    QWeakPointer<b2World> m_world;
    b2World *m_worldPtr;
};

#endif /* _BOX2DBASE_H_ */
