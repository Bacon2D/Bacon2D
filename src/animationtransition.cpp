#include "animationtransition.h"

#include "animationchangeevent.h"
#include "spriteanimationitem.h"
#include "spriteitem.h"

AnimationTransition::AnimationTransition(SpriteItem *spriteItem, SpriteAnimationItem *spriteAnimationItem)
    : QAbstractTransition()
    , m_spriteAnimationItem(spriteAnimationItem)
    , m_spriteItem(spriteItem)
{
}


bool AnimationTransition::eventTest(QEvent *e)
{
    if (e->type() != QEvent::Type(QEvent::User+1))
        return false;

    AnimationChangeEvent *ae = static_cast<AnimationChangeEvent*>(e);
    return (m_spriteAnimationItem->name() == ae->animation);
}

void AnimationTransition::onTransition(QEvent *e)
{
    m_spriteItem->setCurrentSprite(m_spriteAnimationItem->sprite());
    m_spriteItem->setCurrentSpriteAnimation(m_spriteAnimationItem->spriteAnimation());
}
