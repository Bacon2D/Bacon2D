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

#ifndef _POLYLINE_H_
#define _POLYLINE_H_

#include "polygon.h"

class Polyline : public Polygon
{
    Q_OBJECT

    Q_PROPERTY(bool loop READ loop WRITE setLoop NOTIFY loopChanged)

public:
    Polyline(QuasiDeclarativeItem *parent = 0);

    void drawShape(QPainter *painter);

    bool loop() const { return m_loop; }
    void setLoop(const bool &loop);

protected:
    void updateShape(qreal penWidth);

signals:
    void loopChanged();

private:
    bool m_loop;
};

#endif /* _POLYLINE_H_ */
