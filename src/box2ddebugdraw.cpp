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

#include "box2ddebugdraw.h"

#include "box2dbase.h"
#include "enums.h"
#include "util.h"
#include "scene.h"

#include <Box2D/Box2D.h>

#include <QtGui/QPainter>

Box2DDebugDraw::Box2DDebugDraw(Scene *parent)
    : QQuickPaintedItem((QQuickItem*)parent)
    , b2Draw()
    , m_painter(0)
    , m_scene(parent)

{
    SetFlags(e_shapeBit
             | e_jointBit
             | e_aabbBit
             | e_pairBit
             | e_centerOfMassBit);

    setZ(Bacon2D::MaxOrdering);
}

void Box2DDebugDraw::draw()
{
    if (m_scene) {
        b2World *world = m_scene->world();
        world->SetDebugDraw(this);
        world->DrawDebugData();
        world->SetDebugDraw(0);
    }
}

void Box2DDebugDraw::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount,
                            const b2Color &color)
{
    if (!m_painter)
        return;

    m_painter->setPen(b2Util::qColor(color));
    m_painter->setBrush(Qt::NoBrush);
    m_painter->drawPolygon(b2Util::qPolygonF(vertices, vertexCount, Box2DBase::m_scaleRatio));
}

void Box2DDebugDraw::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount,
                                 const b2Color &color)
{
    if (!m_painter)
        return;

    m_painter->setPen(Qt::NoPen);
    m_painter->setBrush(b2Util::qColor(color));
    m_painter->drawPolygon(b2Util::qPolygonF(vertices, vertexCount, Box2DBase::m_scaleRatio));
}

void Box2DDebugDraw::DrawCircle(const b2Vec2 &center, float32 radius,
                           const b2Color &color)
{
    if (!m_painter)
        return;

    m_painter->setPen(b2Util::qColor(color));
    m_painter->setBrush(Qt::NoBrush);
    m_painter->drawEllipse(b2Util::qPointF(center),
                           radius * Box2DBase::m_scaleRatio,
                           radius * Box2DBase::m_scaleRatio);
}

void Box2DDebugDraw::DrawSolidCircle(const b2Vec2 &center, float32 radius,
                                const b2Vec2 &axis, const b2Color &color)
{
    Q_UNUSED(axis)

    if (!m_painter)
        return;

    m_painter->setPen(Qt::NoPen);
    m_painter->setBrush(b2Util::qColor(color));
    m_painter->drawEllipse(b2Util::qPointF(center, Box2DBase::m_scaleRatio),
                           radius * Box2DBase::m_scaleRatio,
                           radius * Box2DBase::m_scaleRatio);
}




void Box2DDebugDraw::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2,
                            const b2Color &color)
{
    if (!m_painter)
        return;

    m_painter->setPen(b2Util::qColor(color));
    m_painter->drawLine(b2Util::qPointF(p1, Box2DBase::m_scaleRatio), b2Util::qPointF(p2, Box2DBase::m_scaleRatio));
}

void Box2DDebugDraw::DrawTransform(const b2Transform &xf)
{
    Q_UNUSED(xf)
}

void Box2DDebugDraw::paint(QPainter *painter)
{
    m_painter = painter;

    draw();
}

void Box2DDebugDraw::step()
{
    update();
}
