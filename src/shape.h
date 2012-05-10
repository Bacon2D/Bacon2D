/**
 * Copyright (C) 2012 by INdT
nn *
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

#include <QtGui/QPainter>

class Shape : public QuasiPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(Fill *fill READ fill WRITE setFill NOTIFY fillChanged)

public:
    Shape(QuasiDeclarativeItem *parent = 0)
        : QuasiPaintedItem(parent)
        , m_fill(0)
        {}

    virtual void initialize() = 0;
    virtual void drawShape(QPainter *painter) = 0;

    Fill *fill() const { return m_fill; }

    void setFill(Fill *fill) {
        if (m_fill == fill)
            return;

        m_fill = fill;
        if (!m_fill->initialized())
            m_fill->initialize();
        emit fillChanged();
    }

#if QT_VERSION >= 0x050000
    void paint(QPainter *painter) {
#else
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) {
        Q_UNUSED(option);
        Q_UNUSED(widget);
#endif
        if (m_fill) {
            QBrush *brush = m_fill->brush();
            if (brush)
                painter->setBrush(*brush);
            QPen *pen = m_fill->pen();
            if (pen) {
                painter->setPen(*pen);
            }
            drawShape(painter);
        }
    }

    virtual void componentComplete() {
        initialize();

        QuasiPaintedItem::componentComplete();
    }

signals:
    void fillChanged();

protected:
    Fill *m_fill;
};

#endif /* _SHAPE_H_ */
