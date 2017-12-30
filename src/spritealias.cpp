#include "spritealias.h"

SpriteAlias::SpriteAlias(QObject *parent)
    : m_frameX(0.0)
    , m_frameY(0.0)
    , m_frameWidth(0.0)
    , m_frameHeight(0.0)
    , QObject(parent)
{

}

QString SpriteAlias::name() const
{
    return m_name;
}

void SpriteAlias::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged();
}

qreal SpriteAlias::frameX() const
{
    return m_frameX;
}

void SpriteAlias::setFrameX(qreal frameX)
{
    if (m_frameX == frameX)
        return;

    m_frameX = frameX;
    emit frameXChanged();
}

qreal SpriteAlias::frameY() const
{
    return m_frameY;
}

void SpriteAlias::setFrameY(qreal frameY)
{
    if (m_frameY == frameY)
        return;

    m_frameY = frameY;
    emit frameYChanged();
}

qreal SpriteAlias::frameWidth() const
{
    return m_frameWidth;
}

void SpriteAlias::setFrameWidth(qreal frameWidth)
{
    if (m_frameWidth == frameWidth)
        return;

    m_frameWidth = frameWidth;
    emit frameWidthChanged();
}

qreal SpriteAlias::frameHeight() const
{
    return m_frameHeight;
}

void SpriteAlias::setFrameHeight(qreal frameHeight)
{
    if (m_frameHeight == frameHeight)
        return;

    m_frameHeight = frameHeight;
    emit frameHeightChanged();
}
