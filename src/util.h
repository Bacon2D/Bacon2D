#ifndef _UTIL_H_
#define _UTIL_H_

#include <QtCore>
#include <QColor>
#include <QPolygonF>
#include <QPointF>

#include <Box2D/Box2D.h>

namespace b2Util
{
    float b2Angle(const b2Vec2 &v1, const b2Vec2 &v2);
    float b2Length(const b2Vec2 &v1, const b2Vec2 &v2);
    b2Vec2 b2Center(const b2Vec2 &v1, const b2Vec2 &v2);

    QPointF qTopLeft(const b2Vec2 &vec, const QRectF &geometry, const qreal &scaleRatio = 1.0);
    qreal qAngle(const qreal &b2Angle);
    QColor qColor(const b2Color &color);
    QPointF qPointF(const b2Vec2 &vec, const qreal &scaleRatio = 1.0);
    QPolygonF qPolygonF(const b2Vec2 *vertices, int32 vertexCount, const qreal &scaleRatio = 1.0);
}

#endif /* _UTIL_H_ */
