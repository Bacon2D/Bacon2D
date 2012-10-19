#include "line.h"

#include "util.h"
#include "box2dbase.h"

Line::Line(QuasiDeclarativeItem *parent)
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

void Line::initialize()
{
    Shape::initialize();

    updateShape(penWidth());
}

void Line::updateShape(qreal penWidth)
{
    //FIXME: Use penWidth to calculate the new points.
    // When using big penWidth values, the shape will overflow
    // it's own boundingRect and we have to fix it somehow.
    Q_UNUSED(penWidth);

    qreal xOffset = x() - parentItem()->width() / 2.0;
    qreal yOffset = y() - parentItem()->height() / 2.0;

    if (!m_shape)
        m_shape = new b2EdgeShape;

    b2EdgeShape *edgeShape = static_cast<b2EdgeShape *>(m_shape);
    edgeShape->Set(b2Util::b2Vec(QPointF(m_p1.x() + xOffset,
                                         m_p1.y() + yOffset), Box2DBase::m_scaleRatio),
                   b2Util::b2Vec(QPointF(m_p2.x() + xOffset,
                                         m_p2.y() + yOffset), Box2DBase::m_scaleRatio));
}
