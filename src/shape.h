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

#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "quasipainteditem.h"
#include "fill.h"

#include <Box2D/Box2D.h>
#include <QtGui/QPainter>

class Shape : public QuasiPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(Fill *fill READ fill WRITE setFill NOTIFY fillChanged)

public:
    Shape(QuasiDeclarativeItem *parent = 0);
    virtual ~Shape();

    virtual void initialize();
    virtual void drawShape(QPainter *painter) = 0;

    Fill *fill() const { return m_fill; }
    void setFill(Fill *fill);

    b2Shape *box2DShape() { return m_shape; }

    void paint(QPainter *painter);

    virtual void updateShape(qreal penWidth) = 0;

    qreal penWidth() const;

protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

signals:
    void fillChanged();
    void shapeUpdated();

protected:
    b2Shape *m_shape;
    Fill *m_fill;
    bool m_initialized;
};

#endif /* _SHAPE_H_ */
