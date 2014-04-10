#include "line.h"

Line::Line(QQuickItem *parent)
    : Shape(parent)
{
}

void Line::setP1(const QPointF &p1)
{
    if (m_p1 == p1)
        return;

    m_p1 = p1;

    emit p1Changed();

    if (m_initialized)
        emit shapeUpdated();
}

void Line::setP2(const QPointF &p2)
{
    if (m_p2 == p2)
        return;

    m_p2 = p2;

    emit p2Changed();

    if (m_initialized)
        emit shapeUpdated();
}

void Line::drawShape(QPainter *painter)
{
    painter->drawLine(m_p1, m_p2);
}
