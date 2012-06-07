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

#include "polyline.h"

#include "util.h"
#include "box2dbaseitem.h"

Polyline::Polyline(QuasiDeclarativeItem *parent)
    : Polygon(parent)
    , m_loop(false)
{
}

void Polyline::drawShape(QPainter *painter)
{
    painter->drawPolyline(m_polygon);
}

void Polyline::updateShape(qreal penWidth) {
    b2Vec2 polyline[m_points.count() + m_loop ? 1 : 0];
    qreal xOffset = x() - parentItem()->width() / 2.0;
    qreal yOffset = y() - parentItem()->height() / 2.0;

    m_polygon.clear();
    for (int i = 0; i < m_points.count(); i++) {
        QPointF point = m_points.at(i).toPointF();

        m_polygon.append(point);
        polyline[i] = b2Util::b2Vec(QPointF(point.x() + xOffset,
                                           point.y() + yOffset), Box2DBaseItem::m_scaleRatio);
    }

    int pointCount = m_points.count();
    if (m_loop) {
        pointCount += 1;
        polyline[m_points.count()] = polyline[0];
        m_polygon.append(m_polygon.at(0));
    }

    if (m_shape)
        delete m_shape;

    m_shape = new b2ChainShape;
    b2ChainShape *chainShape = static_cast<b2ChainShape*>(m_shape);

    if (m_loop)
        chainShape->CreateLoop(polyline, pointCount);
    else
        chainShape->CreateChain(polyline, pointCount);

    if (m_initialized)
        emit box2DShapeUpdated();
}

void Polyline::setLoop(const bool &loop)
{
    if (m_loop == loop)
        return;

    m_loop = loop;

    emit loopChanged();
}
