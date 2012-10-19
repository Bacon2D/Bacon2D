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

#include "box2dbase.h"

#include "util.h"

#include <Box2D/Box2D.h>

float Box2DBase::m_scaleRatio = 32.0f;

Box2DBase::Box2DBase(Scene *parent )
    : QuasiDeclarativeItem((QuasiDeclarativeItem*)parent)
    , m_initialized(false)
    , m_synchronizing(false)
    , m_worldPtr(0)
{
}

bool Box2DBase::initialized() const
{
    return m_initialized;
}

/*
 * Shamelessly stolen from qml-box2d project at gitorious
 *
 * https://gitorious.org/qml-box2d/qml-box2d
 */
void Box2DBase::synchronize()
{
    if (!m_initialized)
        return;

    m_synchronizing = true;

    const QPointF newPoint = b2Util::qTopLeft(b2TransformOrigin(), boundingRect(), m_scaleRatio);
    const qreal newRotation = b2Util::qAngle(b2Angle());

    if (!qFuzzyCompare(x(), newPoint.x()) || !qFuzzyCompare(y(), newPoint.y()))
        setPos(newPoint);

    if (!qFuzzyCompare(rotation(), newRotation))
        setRotation(newRotation);

    m_synchronizing = false;
}

void Box2DBase::setWorld(QSharedPointer<b2World> world)
{
    m_world = world;

    if (!m_world.isNull())
        m_worldPtr = m_world.data();
}
