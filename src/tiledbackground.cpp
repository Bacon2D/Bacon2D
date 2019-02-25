#include "tiledbackground.h"

TiledBackground::TiledBackground(QObject *parent)
    : QObject(parent)
{

}

QColor TiledBackground::color() const
{
    return m_color;
}

void TiledBackground::setColor(const QColor &color)
{
    if (m_color == color)
        return;

    m_color = color;
    emit colorChanged();
}
