#include "spriteanimationitem.h"

SpriteAnimationItem::SpriteAnimationItem(QState *parent)
    : QState(parent)
    , m_sprite(0)
    , m_spriteAnimation(0)
{
}

QString SpriteAnimationItem::name() const
{
    return m_name;
}

void SpriteAnimationItem::setName(const QString &name)
{
    m_name = name;
}

GameSprite *SpriteAnimationItem::sprite() const
{
    return m_sprite;
}

void SpriteAnimationItem::setSprite(GameSprite *sprite)
{
    m_sprite = sprite;
}

SpriteAnimation *SpriteAnimationItem::spriteAnimation() const
{
    return m_spriteAnimation;
}

void SpriteAnimationItem::setSpriteAnimation(SpriteAnimation *spriteAnimation)
{
    m_spriteAnimation = spriteAnimation;
}
