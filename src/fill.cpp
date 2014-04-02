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

#include "fill.h"

/*!
  \qmltype QuasiFill
  \instantiates Fill
  \inqmlmodule QuasiGame 1.0
  \brief FIXME
 */
Fill::Fill(QObject *parent)
    : QObject(parent)
    , m_brush(0)
    , m_pen(0)
    , m_initialized(false)
    , m_brushStyle(Qt::SolidPattern)
    , m_penStyle(Qt::SolidLine)
    , m_penCapStyle(Qt::SquareCap)
    , m_penJoinStyle(Qt::BevelJoin)
    , m_penWidth(0)
{
}

/*!
 * \qmlproperty Qt::BrushStyle brushStyle
 * \brief FIXME
 */
void Fill::setBrushStyle(const Qt::BrushStyle &brushStyle)
{
    if (m_brushStyle == brushStyle)
        return;

    m_brushStyle = brushStyle;

    emit brushStyleChanged();
}

/*!
 * \qmlproperty Qt::PenStyle penStyle
 * \brief FIXME
 */
void Fill::setPenStyle(const Qt::PenStyle &penStyle)
{
    if (m_penStyle == penStyle)
        return;

    m_penStyle = penStyle;

    emit penStyleChanged();
}

/*!
 * \qmlproperty Qt::PenCapStyle penCapStyle
 * \brief FIXME
 */
void Fill::setPenCapStyle(const Qt::PenCapStyle &penCapStyle)
{
    if (m_penCapStyle == penCapStyle)
        return;

    m_penCapStyle = penCapStyle;

    emit penCapStyleChanged();
}

/*!
 * \qmlproperty Qt::PenJoinStyle penJoinStyle
 * \brief FIXME
 */
void Fill::setPenJoinStyle(const Qt::PenJoinStyle &penJoinStyle)
{
    if (m_penJoinStyle == penJoinStyle)
        return;

    m_penJoinStyle = penJoinStyle;

    emit penJoinStyleChanged();
}

/*!
 * \qmlproperty qreal penWidth
 * \brief FIXME
 */
void Fill::setPenWidth(const qreal &penWidth)
{
    if (m_penWidth == penWidth)
        return;

    m_penWidth = penWidth;

    emit penWidthChanged();
}
