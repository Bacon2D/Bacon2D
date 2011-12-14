#ifndef _SPRITEANIMATION_H_
#define _SPRITEANIMATION_H_

#include <QPropertyAnimation>

class GameSprite;

class SpriteAnimation : public QPropertyAnimation
{
    Q_OBJECT

    Q_PROPERTY(GameSprite *sprite READ sprite WRITE setSprite NOTIFY spriteChanged)
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(int loops READ loops WRITE setLoops NOTIFY loopsChanged)

public:
    SpriteAnimation(QObject *parent = 0);

    GameSprite *sprite() const;
    void setSprite(GameSprite *sprite);

    bool running() const;
    void setRunning(bool running);

    int loops() const;
    void setLoops(int loops);

signals:
    void spriteChanged();
    void runningChanged();
    void loopsChanged();

private:
    GameSprite *m_sprite;
    bool m_running;
    int m_loops;
};

#endif /* _SPRITEANIMATION_H_ */
