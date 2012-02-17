#include "staticlayer.h"

StaticLayer::StaticLayer(Layer *parent)
    : Layer(parent)
{
}

StaticLayer::~StaticLayer()
{
}

void StaticLayer::paint(QPainter *painter)
{
    drawPixmap();

    if (m_currentPixmap)
        painter->drawPixmap(0 * m_factor, 0, *m_currentPixmap);
}
