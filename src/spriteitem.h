#ifndef _SPRITEITEM_H_
#define _SPRITEITEM_H_

#include <QHash>
#include <QStateMachine>

#include "gameitem.h"

class GameScene;
class SpriteAnimationItem;

class SpriteItem : public GameItem
{
    Q_OBJECT

    Q_PROPERTY(QDeclarativeListProperty<SpriteAnimationItem> animations READ animations)
    Q_PROPERTY(QString animation READ animation WRITE setAnimation NOTIFY animationChanged)

public:
    SpriteItem(GameScene *parent = 0);

    QDeclarativeListProperty<SpriteAnimationItem> animations() const;

    QString animation() const;
    void setAnimation(const QString &animation, const bool &force = false);

public slots:
    void initializeAnimation();

signals:
    void animationChanged();

private:
    void initializeMachine();

private:
    static void append_animation(QDeclarativeListProperty<SpriteAnimationItem> *list, SpriteAnimationItem *animation);

    QStateMachine *m_stateMachine;
    QState *m_stateGroup;
    QHash<QString, SpriteAnimationItem *> m_states;
    QString m_animation;
};

#endif /* _SPRITEITEM_H_ */
