#ifndef _ANIMATIONTRANSITION_H_
#define _ANIMATIONTRANSITION_H_

#include <QAbstractTransition>

class SpriteAnimationItem;

class AnimationTransition : public QAbstractTransition
{
public:
    AnimationTransition(SpriteAnimationItem *spriteAnimationItem);

    virtual bool eventTest(QEvent *e);
    virtual void onTransition(QEvent *e);

private:
    SpriteAnimationItem *m_spriteAnimationItem;
};

#endif /* _ANIMATIONTRANSITION_H_ */
