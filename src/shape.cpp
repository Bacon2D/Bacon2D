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

#include "shape.h"

Shape::Shape(QuasiDeclarativeItem *parent)
    : QuasiPaintedItem(parent)
    , m_shape(0)
    , m_fill(0)
    , m_initialized(false)
{
}

Shape::~Shape()
{
    delete m_shape;
}

void Shape::initialize()
{
    if (!m_fill || m_initialized)
        return;

    if (!m_fill->initialized())
        m_fill->initialize();

    m_initialized = true;
}

void Shape::setFill(Fill *fill)
{
    if (m_fill == fill)
        return;

    m_fill = fill;

    if (!m_fill->initialized())
        m_fill->initialize();

    emit fillChanged();
}

void Shape::paint(QPainter *painter)
{
    if (!m_fill)
        return;

    QBrush *brush = m_fill->brush();
    if (brush)
        painter->setBrush(*brush);

    QPen *pen = m_fill->pen();
    if (pen)
        painter->setPen(*pen);

    drawShape(painter);
}

void Shape::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    Q_UNUSED(newGeometry);
    Q_UNUSED(oldGeometry);

    if (m_initialized)
        emit shapeUpdated();
}

qreal Shape::penWidth() const
{
    qreal penWidth = 0;
    if (m_fill && m_fill->initialized())
        penWidth = m_fill->pen()->widthF();

    return penWidth;
}
