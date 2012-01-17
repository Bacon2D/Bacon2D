#include "box2dbaseitem.h"

#include <Box2D/Box2D.h>

Box2DBaseItem::Box2DBaseItem(GameScene *parent )
    : GameItem(parent)
    , m_initialized(false)
    , m_synchronizing(false)
    , m_synchronize(true)
{
}

bool Box2DBaseItem::initialized()
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

        const b2Vec2 position = b2TransformOrigin();
        const float32 angle = b2Angle();

        const qreal newX = position.x * scaleRatio - width() / 2.0;
        const qreal newY = -position.y * scaleRatio - height() / 2.0;
        const qreal newRotation = -(angle * 360.0) / (2 * b2_pi);

        if (!qFuzzyCompare(x(), newX) || !qFuzzyCompare(y(), newY))
            setPos(QPointF(newX, newY));
        if (!qFuzzyCompare(rotation(), newRotation))
            setRotation(newRotation);

        m_synchronizing = false;
    }
}
