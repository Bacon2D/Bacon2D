#include "animationtransition.h"

#include "animationchangeevent.h"
#include "spriteanimationitem.h"
#include "spriteitem.h"
#include "spritesheet.h"

AnimationTransition::AnimationTransition(SpriteAnimationItem *spriteAnimationItem)
    : QAbstractTransition()
    , m_spriteAnimationItem(spriteAnimationItem)
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
    m_spriteAnimationItem->spriteSheet()->setVisible(true);
    m_spriteAnimationItem->setRunning(true);
}
