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

#include "box2ddebugdrawitem.h"

#include "box2dbaseitem.h"
#include "enums.h"
#include "util.h"
#include "scene.h"

#include <Box2D/Box2D.h>

#include <QtGui/QPainter>

Box2DDebugDrawItem::Box2DDebugDrawItem(Scene *parent)
    : QuasiPaintedItem((QuasiDeclarativeItem*)parent)
    , b2Draw()
    , m_painter(0)
    , m_scene(parent)

{
    SetFlags(e_shapeBit
             | e_jointBit
             | e_aabbBit
             | e_pairBit
             | e_centerOfMassBit);

#if QT_VERSION >= 0x050000
    setZ(Quasi::MaxOrdering);
#else
    setZValue(Quasi::MaxOrdering);
#endif
}

void Box2DDebugDrawItem::draw()
{
    if (m_scene) {
        b2World *world = m_scene->world();
        world->SetDebugDraw(this);
        world->DrawDebugData();
        world->SetDebugDraw(0);
    }
}

void Box2DDebugDrawItem::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount,
                            const b2Color &color)
{
    if (!m_painter)
        return;

    m_painter->setPen(b2Util::qColor(color));
    m_painter->setBrush(Qt::NoBrush);
    m_painter->drawPolygon(b2Util::qPolygonF(vertices, vertexCount, Box2DBaseItem::m_scaleRatio));
}

void Box2DDebugDrawItem::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount,
                                 const b2Color &color)
{
    if (!m_painter)
        return;

    m_painter->setPen(Qt::NoPen);
    m_painter->setBrush(b2Util::qColor(color));
    m_painter->drawPolygon(b2Util::qPolygonF(vertices, vertexCount, Box2DBaseItem::m_scaleRatio));
}

void Box2DDebugDrawItem::DrawCircle(const b2Vec2 &center, float32 radius,
                           const b2Color &color)
{
    if (!m_painter)
        return;

    m_painter->setPen(b2Util::qColor(color));
    m_painter->setBrush(Qt::NoBrush);
    m_painter->drawEllipse(b2Util::qPointF(center),
                           radius * Box2DBaseItem::m_scaleRatio,
                           radius * Box2DBaseItem::m_scaleRatio);
}

void Box2DDebugDrawItem::DrawSolidCircle(const b2Vec2 &center, float32 radius,
                                const b2Vec2 &axis, const b2Color &color)
{
    Q_UNUSED(axis)

    if (!m_painter)
        return;

    m_painter->setPen(Qt::NoPen);
    m_painter->setBrush(b2Util::qColor(color));
    m_painter->drawEllipse(b2Util::qPointF(center, Box2DBaseItem::m_scaleRatio),
                           radius * Box2DBaseItem::m_scaleRatio,
                           radius * Box2DBaseItem::m_scaleRatio);
}




void Box2DDebugDrawItem::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2,
                            const b2Color &color)
{
    if (!m_painter)
        return;

    m_painter->setPen(b2Util::qColor(color));
    m_painter->drawLine(b2Util::qPointF(p1, Box2DBaseItem::m_scaleRatio), b2Util::qPointF(p2, Box2DBaseItem::m_scaleRatio));
}

void Box2DDebugDrawItem::DrawTransform(const b2Transform &xf)
{
    Q_UNUSED(xf)
}

#if QT_VERSION >= 0x050000
void Box2DDebugDrawItem::paint(QPainter *painter)
{
#else
void Box2DDebugDrawItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
#endif
    m_painter = painter;

    draw();
}

void Box2DDebugDrawItem::step()
{
    update();
}
