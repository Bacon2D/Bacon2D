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

#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "shape.h"

class Polygon : public Shape
{
    Q_OBJECT

    Q_PROPERTY(QVariantList points READ points WRITE setPoints NOTIFY pointsChanged)

public:
    Polygon(QuasiDeclarativeItem *parent = 0)
        : Shape(parent)
        {}

    QVariantList points() const { return m_points; }
    void setPoints(const QVariantList &points) {
        if (points.size() < 3 || m_points == points)
            return;
        m_points = points;

        if (m_fill && m_fill->initialized())
            updatePolygon(m_fill->pen()->widthF());

        emit pointsChanged();
    }

    void drawShape(QPainter *painter) {
        painter->drawPolygon(m_polygon);
    }

    void initialize() {
        if (!m_fill)
            return;
        m_fill->initialize();
        if (m_points.size() > 2)
            updatePolygon(m_fill->pen()->widthF());
    }

signals:
    void pointsChanged();

private:
    void updatePolygon(qreal penWidth) {
        qreal offset = penWidth / 2.0;
        qreal xScale = (width() - penWidth)  / width();
        qreal yScale = (height() - penWidth)  / height();

        m_polygon.clear();
        for (int i = 0; i < m_points.count(); i++) {
            QPointF point = m_points.at(i).toPointF();

            const float x = offset + point.x() * xScale;
            const float y = offset + point.y() * yScale;
            m_polygon.append(QPointF(x, y));
        }
    }

private:
    QVariantList m_points;
    QPolygonF m_polygon;
};

#endif /* _POLYGON_H_ */
