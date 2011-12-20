#ifndef _SPRITEANIMATIONITEM_H_
#define _SPRITEANIMATIONITEM_H_

#include <QState>

#include "gamesprite.h"
#include "spriteanimation.h"

class SpriteAnimationItem : public QState
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName CONSTANT)
    Q_PROPERTY(GameSprite *sprite READ sprite WRITE setSprite CONSTANT)
    Q_PROPERTY(SpriteAnimation *spriteAnimation READ spriteAnimation WRITE setSpriteAnimation CONSTANT)

public:
    SpriteAnimationItem(QState *parent = 0);

    QString name() const;
    void setName(QString name);

    GameSprite *sprite() const;
    void setSprite(GameSprite *sprite);

    SpriteAnimation *spriteAnimation() const;
    void setSpriteAnimation(SpriteAnimation *spriteAnimation);

private:
    QString m_name;
    GameSprite *m_sprite;
    SpriteAnimation *m_spriteAnimation;
};

#endif /* _SPRITEANIMATIONITEM_H_ */
