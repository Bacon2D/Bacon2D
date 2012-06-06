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

#if QT_VERSION >= 0x050000
void Shape::paint(QPainter *painter)
{
#else
void Shape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
#endif

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
