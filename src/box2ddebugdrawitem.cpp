#include "box2ddebugdrawitem.h"

#include <QQuickItem>
#include <QPainter>

#include <Box2D/Box2D.h>

#include "enums.h"
#include "box2dscene.h"
#include "box2dbaseitem.h"
#include "util.h"

Box2DDebugDrawItem::Box2DDebugDrawItem(Box2DScene *parent)
    : QQuickPaintedItem((QQuickItem *)parent)
    , b2Draw()
    , m_painter(0)
    , m_scene(parent)

{
    SetFlags(e_shapeBit
             | e_jointBit
             | e_aabbBit
             | e_pairBit
             | e_centerOfMassBit);

    setZ(Quasi::MaxOrdering);
}

void Box2DDebugDrawItem::draw()
{
    if (m_scene) {
        b2World *world = m_scene->world();
        world->SetDebugDraw(this);
        world->DrawDebugData();
        world->SetDebugDraw(0);
    }
}

void Box2DDebugDrawItem::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount,
                            const b2Color &color)
{
    if (!m_painter)
        return;

    m_painter->setPen(b2Util::qColor(color));
    m_painter->setBrush(Qt::NoBrush);
    m_painter->drawPolygon(b2Util::qPolygonF(vertices, vertexCount, Box2DBaseItem::m_scaleRatio));
}

void Box2DDebugDrawItem::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount,
                                 const b2Color &color)
{
    if (!m_painter)
        return;

    m_painter->setPen(Qt::NoPen);
    m_painter->setBrush(b2Util::qColor(color));
    m_painter->drawPolygon(b2Util::qPolygonF(vertices, vertexCount, Box2DBaseItem::m_scaleRatio));
}

void Box2DDebugDrawItem::DrawCircle(const b2Vec2 &center, float32 radius,
                           const b2Color &color)
{
    if (!m_painter)
        return;

    m_painter->setPen(b2Util::qColor(color));
    m_painter->setBrush(Qt::NoBrush);
    m_painter->drawEllipse(b2Util::qPointF(center),
                           radius * Box2DBaseItem::m_scaleRatio,
                           radius * Box2DBaseItem::m_scaleRatio);
}

void Box2DDebugDrawItem::DrawSolidCircle(const b2Vec2 &center, float32 radius,
                                const b2Vec2 &axis, const b2Color &color)
{
    Q_UNUSED(axis)

    if (!m_painter)
        return;

    m_painter->setPen(Qt::NoPen);
    m_painter->setBrush(b2Util::qColor(color));
    m_painter->drawEllipse(b2Util::qPointF(center, Box2DBaseItem::m_scaleRatio),
                           radius * Box2DBaseItem::m_scaleRatio,
                           radius * Box2DBaseItem::m_scaleRatio);
}




void Box2DDebugDrawItem::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2,
                            const b2Color &color)
{
    if (!m_painter)
        return;

    m_painter->setPen(b2Util::qColor(color));
    m_painter->drawLine(b2Util::qPointF(p1, Box2DBaseItem::m_scaleRatio), b2Util::qPointF(p2, Box2DBaseItem::m_scaleRatio));
}

void Box2DDebugDrawItem::DrawTransform(const b2Transform &xf)
{
    Q_UNUSED(xf)
}

void Box2DDebugDrawItem::paint(QPainter *painter)
{
    m_painter = painter;

    draw();
}

void Box2DDebugDrawItem::step()
{
    update();
}
