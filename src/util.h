#ifndef _UTIL_H_
#define _UTIL_H_

#include <QtCore>

struct b2Vec2;

namespace b2Util
{
    float b2Angle(const b2Vec2 &v1, const b2Vec2 &v2);
    float b2Length(const b2Vec2 &v1, const b2Vec2 &v2);
    b2Vec2 b2Center(const b2Vec2 &v1, const b2Vec2 &v2);

    QPointF qTopLeft(const b2Vec2 &vec, const QRectF &geometry, const qreal &scaleRatio = 1.0);
    qreal qAngle(qreal b2Angle);
}

#endif /* _UTIL_H_ */
