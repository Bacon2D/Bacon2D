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

#include "rectangle.h"

#include "box2dbase.h"
#include "util.h"

Rectangle::Rectangle(QuasiDeclarativeItem *parent)
    : Shape(parent)
{
}

void Rectangle::drawShape(QPainter *painter)
{
    painter->drawRect(m_rect);
}

void Rectangle::initialize()
{
    Shape::initialize();

    m_rect = boundingRect();

    updateShape(penWidth());
}

void Rectangle::updateShape(qreal penWidth)
{
    //FIXME: Use penWidth to calculate the new points.
    // When using big penWidth values, the shape will overflow
    // it's own boundingRect and we have to fix it somehow.
    Q_UNUSED(penWidth);

    if (!m_shape)
        m_shape = new b2PolygonShape;

    QPointF basePos(x() - parentItem()->width() / 2.0,
                    y() - parentItem()->height() / 2.0);

    b2Vec2 rect[4];
    rect[0] = b2Util::b2Vec(QPointF(basePos.x(), basePos.y() + height()), Box2DBase::m_scaleRatio);
    rect[1] = b2Util::b2Vec(QPointF(basePos.x() + width(), basePos.y() + height()), Box2DBase::m_scaleRatio);
    rect[2] = b2Util::b2Vec(QPointF(basePos.x() + width(), basePos.y()), Box2DBase::m_scaleRatio);
    rect[3] = b2Util::b2Vec(basePos, Box2DBase::m_scaleRatio);

    b2PolygonShape *polygonShape = static_cast<b2PolygonShape*>(m_shape);
    polygonShape->Set(rect, 4);
}
