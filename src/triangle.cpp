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

#include "triangle.h"

#include "util.h"
#include "box2dbaseitem.h"

Triangle::Triangle(QuasiDeclarativeItem *parent)
    : Shape(parent)
{
}

void Triangle::setPoints(QVariantList &points)
{
    if (points.size() != 3 || m_points == points)
        return;
    m_points = points;

    if (m_fill && m_fill->initialized())
        updateShape(m_fill->pen()->widthF());

    emit pointsChanged();
}

void Triangle::drawShape(QPainter *painter)
{
    painter->drawPolygon(m_triangle);
}

void Triangle::initialize()
{
    Shape::initialize();
    if (!m_fill)
        return;

    if (m_points.size() == 3)
        updateShape(m_fill->pen()->widthF());
}

void Triangle::updateShape(qreal penWidth)
{
    b2Vec2 triangle[3];
    qreal xOffset = x() - parentItem()->width() / 2.0;
    qreal yOffset = y() - parentItem()->height() / 2.0;

    m_triangle.clear();
    for (int i = 0; i < 3; i++) {
        QPointF point = m_points.at(i).toPointF();

        m_triangle.append(point);
        triangle[i] = b2Util::b2Vec(QPointF(point.x() + xOffset,
                                            point.y() + yOffset), Box2DBaseItem::m_scaleRatio);
    }

    if (m_shape)
        delete m_shape;

    m_shape = new b2PolygonShape;
    b2PolygonShape *polygonShape = static_cast<b2PolygonShape*>(m_shape);
    polygonShape->Set(triangle, 3);

    if (m_initialized)
        emit box2DShapeUpdated();
}
