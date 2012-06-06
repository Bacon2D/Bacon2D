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

#include "box2dbaseitem.h"
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
    m_shape = new b2PolygonShape;

    QPointF newPos(x() - parentItem()->width() / 2.0,
                   y() - parentItem()->height() / 2.0);

    b2Vec2 rect[4];
    rect[0] = b2Util::b2Vec(QPointF(newPos.x(), newPos.y() + height()), Box2DBaseItem::m_scaleRatio);
    rect[1] = b2Util::b2Vec(QPointF(newPos.x() + width(), newPos.y() + height()), Box2DBaseItem::m_scaleRatio);
    rect[2] = b2Util::b2Vec(QPointF(newPos.x() + width(), newPos.y()), Box2DBaseItem::m_scaleRatio);
    rect[3] = b2Util::b2Vec(newPos, Box2DBaseItem::m_scaleRatio);

    b2PolygonShape *polygonShape = static_cast<b2PolygonShape*>(m_shape);
    polygonShape->Set(rect, 4);
}

