/**
 * The MIT License (MIT)
 *
 * Copyright (C) 2012 by INdT
 * Copyright (C) 2014 Bacon2D Project
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @author Rodrigo Goncalves de Oliveira <rodrigo.goncalves@openbossa.org>
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

#include "spriteanimation.h"
#include "spritesheet.h"
#include "spritestrip.h"
#include "animatedsprite.h"

#include <QtCore/QPropertyAnimation>

/*!
  \qmltype SpriteAnimation
  \inqmlmodule Bacon2D
  \brief An animation representing a state of a \l Sprite
 */
SpriteAnimation::SpriteAnimation(QObject *parent)
    : QObject(parent)
    , m_spriteStrip(nullptr)
    , m_defaultSpriteStrip(nullptr)
    , m_spriteSheet(nullptr)
    , m_animation(new QPropertyAnimation(this))
    , m_state(nullptr)
    , m_previousSpriteAnimation(nullptr)
    , m_inverse(false)
{
    connect(m_animation, &QPropertyAnimation::finished, this, &SpriteAnimation::finished);
    connect(m_animation, &QPropertyAnimation::stateChanged, this, &SpriteAnimation::onStateChanged);

    m_animation->setStartValue(0);
    m_animation->setEndValue(0);
}

SpriteAnimation::~SpriteAnimation()
{
    if (!m_state->parent())
        delete m_state;
}

/*!
 * \qmlproperty string SpriteAnimation::name
 * \brief Unique name for the Sprite state
 */
QString SpriteAnimation::name() const
{
    return m_name;
}

void SpriteAnimation::setName(const QString &name)
{
    m_name = name;
}

/*!
 * \qmlproperty bool SpriteAnimation::running
 * \brief Current running state of the animation
 */
bool SpriteAnimation::running() const
{
    return m_animation->state() == QAbstractAnimation::Running;
}

void SpriteAnimation::setRunning(const bool &running)
{
    const bool currentState = m_animation->state() == QAbstractAnimation::Running;
    if (currentState == running)
        return;

    if (running && !(m_animation->startValue() == m_animation->endValue()))
        m_animation->start();
    else
        m_animation->stop();

    emit runningChanged();
}

/*!
 * \qmlproperty int SpriteAnimation::loops
 * \brief Number of loops to run before stopping
 */
int SpriteAnimation::loops() const
{
    return m_animation->loopCount();
}

void SpriteAnimation::setLoops(const int &loops)
{
    const int currentState = m_animation->loopCount();
    if (currentState == loops)
        return;

    m_animation->setLoopCount(loops);
    emit loopsChanged();
}

SpriteSheetGrid *SpriteAnimation::spriteSheet() const
{
    return m_spriteSheet;
}

SpriteStrip *SpriteAnimation::spriteStrip() const
{
    return m_spriteStrip;
}

void SpriteAnimation::setSpriteStrip(SpriteStrip *spriteStrip)
{
    if (m_spriteStrip == spriteStrip)
        return;
    if (m_spriteStrip && m_spriteStrip == m_defaultSpriteStrip) {
        m_defaultSpriteStrip->deleteLater();
        m_defaultSpriteStrip = nullptr;
    }

    if (m_spriteStrip) {
        disconnect(m_spriteStrip, &SpriteStrip::framesChanged, this, &SpriteAnimation::updateEndValue);
        disconnect(m_spriteStrip, &SpriteStrip::initialFrameChanged, this, &SpriteAnimation::updateStartValue);
        disconnect(m_spriteStrip, &SpriteStrip::finalFrameChanged, this, &SpriteAnimation::updateEndValue);
        disconnect(m_spriteStrip, &SpriteStrip::frameChanged, this, &SpriteAnimation::frameChanged);
    }

    m_spriteStrip = spriteStrip;

    if (m_spriteStrip) {
        connect(m_spriteStrip, &SpriteStrip::framesChanged, this, &SpriteAnimation::updateEndValue);
        connect(m_spriteStrip, &SpriteStrip::initialFrameChanged, this, &SpriteAnimation::updateStartValue);
        connect(m_spriteStrip, &SpriteStrip::finalFrameChanged, this, &SpriteAnimation::updateEndValue);
        connect(m_spriteStrip, &SpriteStrip::frameChanged, this, &SpriteAnimation::frameChanged);

        if (!m_spriteStrip->spriteSheet())
            m_spriteStrip->setSpriteSheet(m_spriteSheet);
    }

    emit spriteStripChanged();
}

/*!
 * \qmlproperty int SpriteAnimation::frames
 * \brief Number of frames included in the source image
 */
int SpriteAnimation::frames() const
{
    return m_spriteStrip->frames();
}

/*!
 * \qmlproperty int SpriteAnimation::frame
 * \brief Current frame shown in the SpriteAnimation
 */
int SpriteAnimation::frame() const
{
    return m_spriteStrip->frame();
}

/*!
 * \qmlproperty int SpriteAnimation::initialFrame
 * \brief Starting frame to be shown in the SpriteAnimation
 */

SpriteAnimation *SpriteAnimation::previousAnimation() const
{
    return m_previousSpriteAnimation;
}

void SpriteAnimation::setPreviousAnimation(SpriteAnimation *previousAnimation)
{
    m_previousSpriteAnimation = previousAnimation;
}

QState *SpriteAnimation::state() const
{
    return m_state;
}

QAbstractAnimation *SpriteAnimation::animation() const
{
    return m_animation;
}

void SpriteAnimation::classBegin()
{

}

void SpriteAnimation::componentComplete()
{
    if (!m_spriteStrip) {
        SpriteStrip *spriteStrip = new SpriteStrip;
        m_defaultSpriteStrip = spriteStrip;
        setSpriteStrip(spriteStrip);
    }

    m_animation->setTargetObject(m_spriteStrip);
    m_animation->setPropertyName("frame");
    m_animation->setStartValue(m_spriteStrip->initialFrame());
    m_animation->setEndValue(m_spriteStrip->finalFrame());
    connect(m_spriteStrip, &SpriteStrip::framesChanged, this, &SpriteAnimation::updateEndValue);
    connect(m_spriteStrip, &SpriteStrip::finalFrameChanged, this, &SpriteAnimation::updateEndValue);
}

void SpriteAnimation::setParentState(QState *state)
{
    if (m_state)
        delete m_state;

    m_state = new QState(state);
}

void SpriteAnimation::onStateChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState)
{
    Q_UNUSED(oldState)
    setRunning(newState == QAbstractAnimation::Running);
}

void SpriteAnimation::updateStartValue()
{
    m_animation->setStartValue(m_spriteStrip->initialFrame());
}

void SpriteAnimation::updateEndValue()
{
    m_animation->setEndValue(m_spriteStrip->finalFrame() <= 0 ? m_spriteStrip->frames() - 1 : m_spriteStrip->finalFrame() + 1);
}

/*!
 * \qmlproperty int SpriteAnimation::duration
 * \brief Duration in milliseconds of all frames in the animation per loop.
 */
int SpriteAnimation::duration() const
{
    return m_animation->duration();
}

void SpriteAnimation::setDuration(const int &duration)
{
    int currentState = m_animation->duration();
    if (currentState == duration)
        return;

    m_animation->setDuration(duration);

    emit durationChanged();
}

/*!
 * \qmlproperty bool SpriteAnimation::inverse
 * \brief Reverse the animation, showing frames from right to left
 */
bool SpriteAnimation::inverse() const
{
    return m_inverse;
}

void SpriteAnimation::setInverse(const bool &inverse)
{
    if (m_inverse == inverse)
        return;

    m_inverse = inverse;

    //m_animation->setDirection(m_inverse ? QAbstractAnimation::Backward : QAbstractAnimation::Forward);

    if (m_inverse) {
        m_animation->setStartValue(m_spriteStrip->finalFrame() + 1);
        m_animation->setEndValue(m_spriteStrip->initialFrame());
    } else {
        m_animation->setStartValue(m_spriteStrip->initialFrame());
        m_animation->setEndValue(m_spriteStrip->finalFrame() + 1);
    }

    emit inverseChanged();
}
