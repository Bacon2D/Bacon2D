#include "staticlayer.h"

StaticLayer::StaticLayer(Layer *parent)
    : Layer(parent)
      , m_globalXPos(0.0)
      , m_localXPos(0.0)
{
}

StaticLayer::~StaticLayer()
{
}
void StaticLayer::moveX(qreal value)
{
    m_globalXPos += value; // XXX should multiply by -1??
    m_localXPos += value;

    if (m_localXPos > 0) {
        drawPixmap();
        m_localXPos =  -width() + value;
    } else if (m_localXPos * m_factor <= -width()) {
        drawPixmap();
        m_localXPos = 0;
    }
}

void StaticLayer::paint(QPainter *painter)
{
    if (m_currentPixmap)
        painter->drawPixmap(m_localXPos * m_factor, 0, *m_currentPixmap);
}
