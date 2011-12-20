#ifndef _SPRITEITEM_H_
#define _SPRITEITEM_H_

#include <QHash>
#include <QStateMachine>

#include "gameitem.h"
#include "gamesprite.h"
#include "spriteanimation.h"
#include "spriteanimationitem.h"

class GameScene;

class SpriteItem : public GameItem
{
    Q_OBJECT

    Q_PROPERTY(QDeclarativeListProperty<SpriteAnimationItem> animations READ animations)
    Q_PROPERTY(QString animation READ animation WRITE setAnimation NOTIFY animationChanged)
    Q_PROPERTY(GameSprite *currentSprite READ currentSprite WRITE setCurrentSprite NOTIFY currentSpriteChanged)
    Q_PROPERTY(SpriteAnimation *currentSpriteAnimation READ currentSpriteAnimation WRITE setCurrentSpriteAnimation NOTIFY currentSpriteAnimationChanged)

public:
    SpriteItem(GameScene *parent = 0);

    QDeclarativeListProperty<SpriteAnimationItem> animations();

    QString animation() const;
    void setAnimation(QString animation, bool force = false);

    GameSprite *currentSprite() const;
    void setCurrentSprite(GameSprite *currentSprite);

    SpriteAnimation *currentSpriteAnimation() const;
    void setCurrentSpriteAnimation(SpriteAnimation *currentSpriteAnimation);

public slots:
    void initializeAnimation();

signals:
    void animationChanged();
    void currentSpriteChanged();
    void currentSpriteAnimationChanged();

private:
    void initializeMachine();

private:
    static void append_animation(QDeclarativeListProperty<SpriteAnimationItem> *list, SpriteAnimationItem *animation);

    QStateMachine *m_stateMachine;
    QState *m_stateGroup;
    QHash<QString, SpriteAnimationItem*> m_states;
    QString m_animation;
    GameSprite *m_currentSprite;
    SpriteAnimation *m_currentSpriteAnimation;
};

#endif /* _SPRITEITEM_H_ */
