/**
 * Copyright (C) 2012 by INdT
 * Copyright (C) 2014 Bacon2D Project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * @author Rodrigo Goncalves de Oliveira <rodrigo.goncalves@openbossa.org>
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

#include "spriteanimation.h"
#include "spritesheet.h"

#include <QtCore/QPropertyAnimation>

/*!
  \qmltype SpriteAnimation
  \inqmlmodule Bacon2D
  \brief An animation representing a state of a \l Sprite
 */
SpriteAnimation::SpriteAnimation(QState *parent)
    : QState(parent)
    , m_spriteSheet(new SpriteSheet)
    , m_spriteAnimation(new QPropertyAnimation(this))
    , m_inverse(false)
{
    connect(m_spriteSheet, SIGNAL(sourceChanged()), this, SIGNAL(sourceChanged()));
    connect(m_spriteSheet, SIGNAL(frameChanged()), this, SIGNAL(frameChanged()));
    connect(m_spriteSheet, SIGNAL(framesChanged()), this, SIGNAL(framesChanged()));
    connect(m_spriteSheet, SIGNAL(initialFrameChanged()), this, SIGNAL(initialFrameChanged()));

    connect(m_spriteAnimation, SIGNAL(finished()), this, SIGNAL(finished()));

    m_spriteAnimation->setTargetObject(m_spriteSheet);
    m_spriteAnimation->setPropertyName("frame");
    m_spriteAnimation->setStartValue(0);
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
    return m_spriteAnimation->state() == QAbstractAnimation::Running;
}

void SpriteAnimation::setRunning(const bool &running)
{
    if (!m_spriteAnimation) {
        qWarning() << "SpriteAnimation" << "invalid";
        return;
    }

    bool currentState = m_spriteAnimation->state() == QAbstractAnimation::Running;

    if (currentState != running) {
        if (running)
            m_spriteAnimation->start();
        else
            m_spriteAnimation->stop();

        emit runningChanged();
    }
}

/*!
 * \qmlproperty int SpriteAnimation::loops
 * \brief Number of loops to run before stopping
 */
int SpriteAnimation::loops() const
{
    return m_spriteAnimation->loopCount();
}

void SpriteAnimation::setLoops(const int &loops)
{
    int currentState = m_spriteAnimation->loopCount();

    if (currentState != loops) {
        m_spriteAnimation->setLoopCount(loops);

        emit loopsChanged();
    }
}

/*!
 * \qmlproperty string SpriteAnimation::source
 * \brief QUrl for the source image
 */
QUrl SpriteAnimation::source() const
{
    return m_spriteSheet->source();
}

void SpriteAnimation::setSource(const QUrl &source)
{
    m_spriteSheet->setSource(source);
}

/*!
 * \qmlproperty int SpriteAnimation::frames
 * \brief Number of frames included in the source image
 */
int SpriteAnimation::frames() const
{
    return m_spriteSheet->frames();
}

void SpriteAnimation::setFrames(const int &frames)
{
    m_spriteSheet->setFrames(frames);
    m_spriteAnimation->setEndValue(frames);
}

/*!
 * \qmlproperty int SpriteAnimation::frame
 * \brief Current frame shown in the SpriteAnimation
 */
int SpriteAnimation::frame() const
{
    return m_spriteSheet->frame();
}

void SpriteAnimation::setFrame(const int &frame)
{
    m_spriteSheet->setFrame(frame);
}

/*!
 * \qmlproperty int SpriteAnimation::initialFrame
 * \brief Starting frame to be shown in the SpriteAnimation
 */
int SpriteAnimation::initialFrame() const
{
    return m_spriteSheet->initialFrame();
}

void SpriteAnimation::setInitialFrame(const int &initialFrame)
{
    m_spriteSheet->setInitialFrame(initialFrame);
    m_spriteAnimation->setStartValue(initialFrame);
}

/*!
 * \qmlproperty bool SpriteAnimation::visible
 * \brief FIXME
 * \internal
 */
bool SpriteAnimation::visible() const
{
    return m_spriteSheet->isVisible();
}

void SpriteAnimation::setVisible(const bool &visible)
{
    bool currentState = m_spriteSheet->isVisible();
    if (currentState != visible) {
        m_spriteSheet->setVisible(visible);

        emit visibleChanged();
    }
}

/*!
 * \qmlproperty SpriteSheet SpriteAnimation::spriteSheet
 * \brief FIXME
 * \internal
 */
SpriteSheet *SpriteAnimation::spriteSheet()
{
    return m_spriteSheet;
}

/*!
 * \qmlproperty int SpriteAnimation::duration
 * \brief Duration in milliseconds of all frames in the animation per loop.  
 */
int SpriteAnimation::duration() const
{
    return m_spriteAnimation->duration();
}

void SpriteAnimation::setDuration(const int &duration)
{
    int currentState = m_spriteAnimation->duration();
    if (currentState != duration) {
        m_spriteAnimation->setDuration(duration);

        emit durationChanged();
    }
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
    if (m_inverse != inverse) {
        m_inverse = inverse;

        if (m_inverse) {
            m_spriteAnimation->setStartValue(frames());
            m_spriteAnimation->setEndValue(0);
        } else {
            m_spriteAnimation->setStartValue(0);
            m_spriteAnimation->setEndValue(frames());
        }

        emit inverseChanged();
    }
}

/*!
 * \qmlproperty bool SpriteAnimation::verticalMirror
 * \brief Shows the Sprite mirrored (flipped) vertically
 */
bool SpriteAnimation::verticalMirror() const
{
    return m_spriteSheet->verticalMirror();
}

void SpriteAnimation::setVerticalMirror(const bool &verticalMirror)
{
    m_spriteSheet->setVerticalMirror(verticalMirror);
}

/*!
 * \qmlproperty bool SpriteAnimation::horizontalMirror
 * \brief Shows the Sprite mirrored (flipped) horizontally
 */
bool SpriteAnimation::horizontalMirror() const
{
    return m_spriteSheet->horizontalMirror();
}

void SpriteAnimation::setHorizontalMirror(const bool &horizontalMirror)
{
    m_spriteSheet->setHorizontalMirror(horizontalMirror);
}
