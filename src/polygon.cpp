#include "polygon.h"

#include "util.h"
#include "box2dbase.h"

Polygon::Polygon(QuasiDeclarativeItem *parent)
    : Shape(parent)
{
}

void Polygon::setPoints(const QVariantList &points)
{
    if (points.size() < 3 || m_points == points)
        return;
    m_points = points;

    emit pointsChanged();

    if (m_initialized)
        emit shapeUpdated();
}

void Polygon::drawShape(QPainter *painter)
{
    painter->drawPolygon(m_polygon);
}

void Polygon::initialize()
{
    Shape::initialize();

    if (m_points.size() > 2)
        updateShape(penWidth());
}

void Polygon::updateShape(qreal penWidth)
{
    //FIXME: Use penWidth to calculate the new points.
    // When using big penWidth values, the shape will overflow
    // it's own boundingRect and we have to fix it somehow.
    Q_UNUSED(penWidth);

    b2Vec2 polygon[m_points.count()];
    qreal xOffset = x() - parentItem()->width() / 2.0;
    qreal yOffset = y() - parentItem()->height() / 2.0;

    m_polygon.clear();
    for (int i = 0; i < m_points.count(); i++) {
        QPointF point = m_points.at(i).toPointF();

        m_polygon.append(point);
        polygon[i] = b2Util::b2Vec(QPointF(point.x() + xOffset,
                                           point.y() + yOffset), Box2DBase::m_scaleRatio);
    }

    if (!m_shape)
        m_shape = new b2PolygonShape;

    b2PolygonShape *polygonShape = static_cast<b2PolygonShape*>(m_shape);
    polygonShape->Set(polygon, m_points.count());
}
