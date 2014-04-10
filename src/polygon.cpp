#include "polygon.h"

Polygon::Polygon(QQuickItem *parent)
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
