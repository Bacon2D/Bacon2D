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

#include "circle.h"

#include "box2dbase.h"
#include "util.h"

Circle::Circle(QuasiDeclarativeItem *parent)
    : Shape(parent)
    , m_radius(0)
{
}

void Circle::setRadius(qreal radius)
{
    if (m_radius == radius)
        return;

    m_radius = radius;

    emit radiusChanged();

    if (m_initialized)
        emit shapeUpdated();
}

void Circle::drawShape(QPainter *painter)
{
    qreal diameter = getDiameter();

    // XXX: Why do we need to have x and y set
    // to 0 in order to make it work correctly?
    QRectF rect(0, 0, diameter, diameter);
    painter->drawEllipse(rect);
}

void Circle::initialize()
{
    Shape::initialize();

    updateShape(penWidth());
}

qreal Circle::getDiameter() const
{
    qreal diameter = 0.0;

    if (m_radius > 0)
        diameter = m_radius * 2.0;
    else
        diameter = width() > height() ? height() : width();

    return diameter;
}

void Circle::updateShape(qreal penWidth)
{
    //FIXME: Use penWidth to calculate the new points.
    // When using big penWidth values, the shape will overflow
    // it's own boundingRect and we have to fix it somehow.
    Q_UNUSED(penWidth);

    if (!m_shape)
        m_shape = new b2CircleShape;

    b2CircleShape *circleShape = static_cast<b2CircleShape*>(m_shape);

    qreal diameter = getDiameter();
    QPointF shapePos(x() - parentItem()->width() / 2.0 + diameter / 2.0,
                     y() - parentItem()->height() / 2.0 + diameter / 2.0);

    circleShape->m_radius = diameter / 2.0 / Box2DBase::m_scaleRatio;
    circleShape->m_p = b2Util::b2Vec(shapePos, Box2DBase::m_scaleRatio);
}
