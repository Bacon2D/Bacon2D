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

#include "colorfill.h"

ColorFill::ColorFill(Fill *parent)
    : Fill(parent)
    , m_brushColor("#FFFFFF")
    , m_penColor("")
{
}

void ColorFill::initialize()
{
    m_brush = new QBrush(QColor(m_brushColor), m_brushStyle);
    m_pen = new QPen(*m_brush, m_penWidth, m_penStyle, m_penCapStyle, m_penJoinStyle);

    if (m_penColor.isValid())
        m_pen->setColor(QColor(m_penColor));
    else
        m_pen->setColor(QColor(m_brushColor));

    m_initialized = true;
}

QColor ColorFill::brushColor() const
{
    return m_brushColor;
}

void ColorFill::setBrushColor(const QColor &brushColor)
{
    if (m_brushColor == brushColor)
        return;

    m_brushColor = brushColor;

    if (m_brush)
        delete m_brush;

    m_brush = new QBrush(QColor(m_brushColor));

    emit brushColorChanged();
}

QColor ColorFill::penColor() const
{
    return m_penColor;
}

void ColorFill::setPenColor(const QColor &penColor)
{
    if (m_penColor == penColor)
        return;

    m_penColor = penColor;

    if (m_pen)
        delete m_pen;

    if (m_brush)
        m_pen = new QPen(*m_brush, m_penWidth, m_penStyle, m_penCapStyle, m_penJoinStyle);
    else {
        m_pen = new QPen(QColor(m_penColor));
        m_pen->setWidthF(m_penWidth);
        m_pen->setStyle(m_penStyle);
        m_pen->setCapStyle(m_penCapStyle);
        m_pen->setJoinStyle(m_penJoinStyle);
    }

    emit penColorChanged();
}
