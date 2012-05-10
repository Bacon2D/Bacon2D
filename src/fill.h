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
    Fill(QObject *parent = 0)
        : QObject(parent)
        , m_brush(0)
        , m_pen(0)
        , m_initialized(false)
        , m_brushStyle(Qt::SolidPattern)
        , m_penStyle(Qt::SolidLine)
        , m_penCapStyle(Qt::SquareCap)
        , m_penJoinStyle(Qt::BevelJoin)
        , m_penWidth(0)
        {}

    QBrush *brush() const { return m_brush; }
    QPen *pen() const { return m_pen; }

    virtual void initialize() = 0;
    bool initialized() const { return m_initialized; }

    Qt::BrushStyle brushStyle() const { return m_brushStyle; }
    void setBrushStyle(const Qt::BrushStyle &brushStyle) {
        if (m_brushStyle == brushStyle)
            return;

        m_brushStyle = brushStyle;
        emit brushStyleChanged();
    }

    Qt::PenStyle penStyle() const { return m_penStyle; };
    void setPenStyle(const Qt::PenStyle &penStyle) {
        if (m_penStyle == penStyle)
            return;

        m_penStyle = penStyle;
        emit penStyleChanged();
    }

    Qt::PenCapStyle penCapStyle() const { return m_penCapStyle; }
    void setPenCapStyle(const Qt::PenCapStyle &penCapStyle) {
        if (m_penCapStyle == penCapStyle)
            return;

        m_penCapStyle = penCapStyle;
        emit penCapStyleChanged();
    }

    Qt::PenJoinStyle penJoinStyle() const { return m_penJoinStyle; }
    void setPenJoinStyle(const Qt::PenJoinStyle &penJoinStyle) {
        if (m_penJoinStyle == penJoinStyle)
            return;

        m_penJoinStyle = penJoinStyle;
        emit penJoinStyleChanged();
    }

    qreal penWidth() const { return m_penWidth; }
    void setPenWidth(const qreal &penWidth) {
        if (m_penWidth == penWidth)
            return;

        m_penWidth = penWidth;
        emit penWidthChanged();
    }

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
