#include "triangle.h"

#include "util.h"
#include "box2dbaseitem.h"

Triangle::Triangle(QuasiDeclarativeItem *parent)
        : Shape(parent)
{
}

void Triangle::setPoints(QVariantList &points)
{
    if (points.size() != 3 || m_points == points)
        return;
    m_points = points;

    if (m_fill && m_fill->initialized())
        updateShape(m_fill->pen()->widthF());

    emit pointsChanged();
}

void Triangle::drawShape(QPainter *painter)
{
    painter->drawPolygon(m_triangle);
}

void Triangle::initialize()
{
    Shape::initialize();

    if (m_points.size() == 3)
        updateShape(m_fill->pen()->widthF());
}

void Triangle::updateShape(qreal penWidth)
{
    b2Vec2 triangle[3];
    qreal xOffset = x() - parentItem()->width() / 2.0;
    qreal yOffset = y() - parentItem()->height() / 2.0;

    m_triangle.clear();
    for (int i = 0; i < 3; i++) {
        QPointF point = m_points.at(i).toPointF();

        m_triangle.append(point);
        triangle[i] = b2Util::b2Vec(QPointF(point.x() + xOffset,
                                            point.y() + yOffset), Box2DBaseItem::m_scaleRatio);
    }

    m_shape = new b2PolygonShape;
    b2PolygonShape *polygonShape = static_cast<b2PolygonShape*>(m_shape);
    polygonShape->Set(triangle, 3);
}
