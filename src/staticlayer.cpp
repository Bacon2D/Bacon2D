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
    painter->drawPixmap(0 * m_factor, 0, *m_currentPixmap);
}
