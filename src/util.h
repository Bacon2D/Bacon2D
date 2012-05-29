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

#ifndef _UTIL_H_
#define _UTIL_H_

#include <Box2D/Box2D.h>

#include <QtCore/QtCore>
#include <QtGui/QColor>
#include <QtGui/QPolygonF>

namespace b2Util
{
    float b2Angle(const b2Vec2 &v1, const b2Vec2 &v2);
    float b2Length(const b2Vec2 &v1, const b2Vec2 &v2);
    b2Vec2 b2Center(const b2Vec2 &v1, const b2Vec2 &v2);
    b2Vec2 *b2Vertices(const QVariantList &vertices, const QRectF &geometry, const qreal &scaleRatio = 1.0);
    b2Vec2 b2Vec(const QPointF &point, const qreal &scaleRatio = 1.0);

    QPointF qTopLeft(const b2Vec2 &vec, const QRectF &geometry, const qreal &scaleRatio = 1.0);
    qreal qAngle(const qreal &b2Angle);
    QColor qColor(const b2Color &color);
    QPointF qPointF(const b2Vec2 &vec, const qreal &scaleRatio = 1.0);
    QPolygonF qPolygonF(const b2Vec2 *vertices, int32 vertexCount, const qreal &scaleRatio = 1.0);
}

#endif /* _UTIL_H_ */
