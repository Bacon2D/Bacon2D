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

Polyline::Polyline(QQuickItem *parent)
    : Shape(parent)
    , m_loop(false)
{
}

void Polyline::setPoints(const QVariantList &points)
{
    if (points.size() < 3 || m_points == points)
        return;
    m_points = points;

    emit pointsChanged();

    if (m_initialized)
        emit shapeUpdated();
}

void Polyline::drawShape(QPainter *painter)
{
    painter->drawPolyline(m_polygon);
}

void Polyline::setLoop(const bool &loop)
{
    if (m_loop == loop)
        return;

    m_loop = loop;

    emit loopChanged();

    if (m_initialized && (m_points.count() > 2))
        emit shapeUpdated();
}
