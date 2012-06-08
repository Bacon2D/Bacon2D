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

#ifndef _LINE_H_
#define _LINE_H_

#include "shape.h"

class Line : public Shape
{
    Q_OBJECT

    Q_PROPERTY(QPointF p1 READ p1 WRITE setP1 NOTIFY p1Changed)
    Q_PROPERTY(QPointF p2 READ p2 WRITE setP2 NOTIFY p2Changed)

public:
    Line(QuasiDeclarativeItem *parent = 0);

    QPointF p1() const { return m_p1; }
    void setP1(const QPointF &p1);

    QPointF p2() const { return m_p2; }
    void setP2(const QPointF &p2);

    void drawShape(QPainter *painter);

    void initialize();

    void updateShape(qreal penWidth);

signals:
    void p1Changed();
    void p2Changed();

private:
    QPointF m_p1;
    QPointF m_p2;
};

#endif /* _LINE_H_ */
