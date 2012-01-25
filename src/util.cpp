#include "util.h"

#include <QtCore/qmath.h>
#include <Box2D/Box2D.h>

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

QPointF b2Util::qTopLeft(const b2Vec2 &vec, const QRectF &geometry, const qreal &scaleRatio)
{
    const qreal newX = vec.x * scaleRatio - geometry.width() / 2.0;
    const qreal newY = -vec.y * scaleRatio - geometry.height() / 2.0;

    return QPointF(newX, newY);
}

qreal b2Util::qAngle(qreal angle)
{
    return -(angle * 360.0) / (2 * b2_pi);
}
