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

#ifndef _FILL_H_
#define _FILL_H_

#include <QtCore/QObject>
#include <QtGui/QBrush>
#include <QtGui/QPen>

class Fill : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Qt::BrushStyle brushStyle READ brushStyle WRITE setBrushStyle NOTIFY brushStyleChanged)
    Q_PROPERTY(Qt::PenStyle penStyle READ penStyle WRITE setPenStyle NOTIFY penStyleChanged)
    Q_PROPERTY(Qt::PenCapStyle penCapStyle READ penCapStyle WRITE setPenCapStyle NOTIFY penCapStyleChanged)
    Q_PROPERTY(Qt::PenJoinStyle penJoinStyle READ penJoinStyle WRITE setPenJoinStyle NOTIFY penJoinStyleChanged)
    Q_PROPERTY(qreal penWidth READ penWidth WRITE setPenWidth NOTIFY penWidthChanged)

public:
    Fill(QObject *parent = 0);

    QBrush *brush() const { return m_brush; }
    QPen *pen() const { return m_pen; }

    virtual void initialize() = 0;
    bool initialized() const { return m_initialized; }

    Qt::BrushStyle brushStyle() const { return m_brushStyle; }
    void setBrushStyle(const Qt::BrushStyle &brushStyle);

    Qt::PenStyle penStyle() const { return m_penStyle; };
    void setPenStyle(const Qt::PenStyle &penStyle);

    Qt::PenCapStyle penCapStyle() const { return m_penCapStyle; }
    void setPenCapStyle(const Qt::PenCapStyle &penCapStyle);

    Qt::PenJoinStyle penJoinStyle() const { return m_penJoinStyle; }
    void setPenJoinStyle(const Qt::PenJoinStyle &penJoinStyle);

    qreal penWidth() const { return m_penWidth; }
    void setPenWidth(const qreal &penWidth);

signals:
    void brushStyleChanged();
    void penStyleChanged();
    void penCapStyleChanged();
    void penJoinStyleChanged();
    void penWidthChanged();

protected:
    QBrush *m_brush;
    QPen *m_pen;
    bool m_initialized;
    Qt::BrushStyle m_brushStyle;
    Qt::PenStyle m_penStyle;
    Qt::PenCapStyle m_penCapStyle;
    Qt::PenJoinStyle m_penJoinStyle;
    qreal m_penWidth;
};

#endif /* _FILL_H_ */
