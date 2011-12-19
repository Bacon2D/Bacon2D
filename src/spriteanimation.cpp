#include "spriteanimation.h"

#include "gamesprite.h"

SpriteAnimation::SpriteAnimation(QObject *parent)
    : QPropertyAnimation(parent)
    , m_sprite(0)
    , m_running(false)
    , m_loops(1)
{
    setLoops(m_loops);
}

GameSprite *SpriteAnimation::sprite() const
{
    return m_sprite;
}

void SpriteAnimation::setSprite(GameSprite *sprite)
{
    if (m_sprite != sprite) {
        m_sprite = sprite;

        if (m_sprite) {
            stop();

            setTargetObject(m_sprite);
            setPropertyName("frame");
            setStartValue(m_sprite->initialFrame());
            setEndValue(m_sprite->frames());

            if (m_running)
                start();
        }
    }

    emit spriteChanged();
}

bool SpriteAnimation::running() const
{
    return m_running;
}

void SpriteAnimation::setRunning(bool running)
{
    if (m_running != running) {
        m_running = running;

        if (m_sprite) {
            if (m_running)
                start();
            else
                stop();
        }

        emit runningChanged();
    }
}

int SpriteAnimation::loops() const
{
    return m_loops;
}

void SpriteAnimation::setLoops(int loops)
{
    if (m_loops != loops) {
        m_loops = loops;

        setLoopCount(loops);

        emit loopsChanged();
    }
}
