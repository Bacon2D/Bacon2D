/**
 * Copyright (C) 2012 by INdT
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

QString SpriteAnimation::name() const
{
    return m_name;
}

void SpriteAnimation::setName(const QString &name)
{
    m_name = name;
}

bool SpriteAnimation::running() const
{
    return m_spriteAnimation->state() == QAbstractAnimation::Running;
}

void SpriteAnimation::setRunning(const bool &running)
{
    bool currentState = m_spriteAnimation->state() == QAbstractAnimation::Running;

    if (currentState != running) {
        if (running)
            m_spriteAnimation->start();
        else
            m_spriteAnimation->stop();

        emit runningChanged();
    }
}

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

QString SpriteAnimation::source() const
{
    return m_spriteSheet->source();
}

void SpriteAnimation::setSource(const QString &source)
{
    m_spriteSheet->setSource(source);
}

int SpriteAnimation::frames() const
{
    return m_spriteSheet->frames();
}

void SpriteAnimation::setFrames(const int &frames)
{
    m_spriteSheet->setFrames(frames);
    m_spriteAnimation->setEndValue(frames);
}

int SpriteAnimation::frame() const
{
    return m_spriteSheet->frame();
}

void SpriteAnimation::setFrame(const int &frame)
{
    m_spriteSheet->setFrame(frame);
}

int SpriteAnimation::initialFrame() const
{
    return m_spriteSheet->initialFrame();
}

void SpriteAnimation::setInitialFrame(const int &initialFrame)
{
    m_spriteSheet->setInitialFrame(initialFrame);
    m_spriteAnimation->setStartValue(initialFrame);
}

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

SpriteSheet *SpriteAnimation::spriteSheet()
{
    return m_spriteSheet;
}

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

bool SpriteAnimation::verticalMirror() const
{
    return m_spriteSheet->verticalMirror();
}

void SpriteAnimation::setVerticalMirror(const bool &verticalMirror)
{
    m_spriteSheet->setVerticalMirror(verticalMirror);
}

bool SpriteAnimation::horizontalMirror() const
{
    return m_spriteSheet->horizontalMirror();
}

void SpriteAnimation::setHorizontalMirror(const bool &horizontalMirror)
{
    m_spriteSheet->setHorizontalMirror(horizontalMirror);
}
