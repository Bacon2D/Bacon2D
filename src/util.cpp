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

#include "util.h"

float b2Util::b2Angle(const b2Vec2 &v1, const b2Vec2 &v2)
{
    b2Vec2 toV2Vec = v1 - v2;
    return qAtan2(-toV2Vec.x, toV2Vec.y);
}

float b2Util::b2Length(const b2Vec2 &v1, const b2Vec2 &v2)
{
    return qSqrt(qPow(v2.x - v1.x, 2) + qPow(v2.y - v1.y, 2));
}

b2Vec2 b2Util::b2Center(const b2Vec2 &v1, const b2Vec2 &v2)
{
    return b2Vec2((v1.x + v2.x) / 2.0f,
                  (v1.y + v2.y) / 2.0f);
}

b2Vec2 *b2Util::b2Vertices(const QVariantList &vertices, const QRectF &geometry, const qreal &scaleRatio)
{
    b2Vec2 *vec= new b2Vec2[vertices.length()];

    for (int i = 0; i < vertices.length(); i++){
        QVariantList temp = vertices.at(i).toList();

        const float x = temp.at(0).toFloat() - geometry.width() / 2.0;
        const float y = temp.at(1).toFloat() - geometry.height() / 2.0;
        vec[i].Set(x / scaleRatio, y / scaleRatio);
    }
    return vec;
}

QPointF b2Util::qTopLeft(const b2Vec2 &vec, const QRectF &geometry, const qreal &scaleRatio)
{
    const qreal newX = vec.x * scaleRatio - geometry.width() / 2.0;
    const qreal newY = -vec.y * scaleRatio - geometry.height() / 2.0;

    return QPointF(newX, newY);
}

qreal b2Util::qAngle(const qreal &angle)
{
    return -(angle * 360.0) / (2 * b2_pi);
}

QColor b2Util::qColor(const b2Color &color)
{
    return QColor(color.r * 255, color.g * 255, color.b * 255);
}

QPointF b2Util::qPointF(const b2Vec2 &vec, const qreal &scaleRatio)
{
    return QPointF(vec.x * scaleRatio, -vec.y * scaleRatio);
}

QPolygonF b2Util::qPolygonF(const b2Vec2 *vertices, int32 vertexCount, const qreal &scaleRatio)
{
    QPolygonF polygon;
    polygon.reserve(vertexCount);

    for (int i = 0; i < vertexCount; ++i)
        polygon.append(qPointF(vertices[i], scaleRatio));

    return polygon;
}
