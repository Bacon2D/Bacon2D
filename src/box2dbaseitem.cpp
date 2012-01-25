#include "box2dbaseitem.h"

#include "util.h"

#include <Box2D/Box2D.h>

float Box2DBaseItem::m_scaleRatio = 32.0f;

Box2DBaseItem::Box2DBaseItem(GameScene *parent )
    : GameItem(parent)
    , m_initialized(false)
    , m_synchronizing(false)
    , m_synchronize(true)
{
}

bool Box2DBaseItem::initialized() const
{
    return m_initialized;
}

/*
 * Shamelessly stolen from qml-box2d project at gitorious
 *
 * https://gitorious.org/qml-box2d/qml-box2d
 */
void Box2DBaseItem::synchronize()
{
    if (m_synchronize && m_initialized) {
        m_synchronizing = true;

        const QPointF newPoint = b2Util::qTopLeft(b2TransformOrigin(), boundingRect(), m_scaleRatio);
        const float32 angle = b2Angle();
        const qreal newRotation = -(angle * 360.0) / (2 * b2_pi);

        if (!qFuzzyCompare(x(), newPoint.x()) || !qFuzzyCompare(y(), newPoint.y()))
            setPos(newPoint);
        if (!qFuzzyCompare(rotation(), newRotation))
            setRotation(newRotation);

        m_synchronizing = false;
    }
}
