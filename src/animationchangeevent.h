#ifndef _ANIMATIONCHANGEEVENT_H_
#define _ANIMATIONCHANGEEVENT_H_

#include <QEvent>

class AnimationChangeEvent : public QEvent
{
public:
    AnimationChangeEvent(const QString &val)
        : QEvent(QEvent::Type(QEvent::User+1))
        , animation(val) {}

    QString animation;
};

#endif /* _ANIMATIONCHANGEEVENT_H_ */
