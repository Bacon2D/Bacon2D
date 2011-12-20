#ifndef _ANIMATIONTRANSITION_H_
#define _ANIMATIONTRANSITION_H_

#include <QAbstractTransition>

class SpriteItem;
class SpriteAnimationItem;

class AnimationTransition : public QAbstractTransition
{
public:
    AnimationTransition(SpriteItem *spriteItem, SpriteAnimationItem *spriteAnimationItem);

    virtual bool eventTest(QEvent *e);
    virtual void onTransition(QEvent *e);

private:
    SpriteAnimationItem *m_spriteAnimationItem;
    SpriteItem *m_spriteItem;
};

#endif /* _ANIMATIONTRANSITION_H_ */
