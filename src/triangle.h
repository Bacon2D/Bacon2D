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

#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "shape.h"

class Triangle : public Shape
{
    Q_OBJECT

    Q_PROPERTY(QVariantList points READ points WRITE setPoints NOTIFY pointsChanged)

public:
    Triangle(QuasiDeclarativeItem *parent = 0)
        : Shape(parent)
        {}

    QVariantList points() const { return m_points; }
    void setPoints(QVariantList &points) {
        if (points.size() != 3 || m_points == points)
            return;
        m_points = points;

        if (m_fill && m_fill->initialized())
            updateShape(m_fill->pen()->widthF());

        emit pointsChanged();
    }

    void drawShape(QPainter *painter) {
        painter->drawPolygon(m_triangle);
    }

    void initialize() {
        if (!m_fill)
            return;
        m_fill->initialize();
        if (m_points.size() == 3)
            updateShape(m_fill->pen()->widthF());
    }

signals:
    void pointsChanged();

private:
    void updateShape(qreal penWidth) {
        m_triangle.clear();
        for (int i = 0; i < 3; i++) {
            QPointF point = m_points.at(i).toPointF();

            m_triangle.append(point);
        }
    }

private:
    QVariantList m_points;
    QPolygonF m_triangle;
};

#endif /* _TRIANGLE_H_ */
