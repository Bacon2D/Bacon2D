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

#include "spriteanimationitem.h"

#include <QPropertyAnimation>

#include "spritesheet.h"

SpriteAnimationItem::SpriteAnimationItem(QState *parent)
    : QState(parent)
    , m_spriteSheet(new SpriteSheet)
    , m_spriteAnimation(new QPropertyAnimation(this))
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

QString SpriteAnimationItem::name() const
{
    return m_name;
}

void SpriteAnimationItem::setName(const QString &name)
{
    m_name = name;
}

bool SpriteAnimationItem::running() const
{
    return m_spriteAnimation->state() == QAbstractAnimation::Running;
}

void SpriteAnimationItem::setRunning(const bool &running)
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

int SpriteAnimationItem::loops() const
{
    return m_spriteAnimation->loopCount();
}

void SpriteAnimationItem::setLoops(const int &loops)
{
    int currentState = m_spriteAnimation->loopCount();

    if (currentState != loops) {
        m_spriteAnimation->setLoopCount(loops);

        emit loopsChanged();
    }
}

QString SpriteAnimationItem::source() const
{
    return m_spriteSheet->source();
}

void SpriteAnimationItem::setSource(const QString &source)
{
    m_spriteSheet->setSource(source);
}

int SpriteAnimationItem::frames() const
{
    return m_spriteSheet->frames();
}

void SpriteAnimationItem::setFrames(const int &frames)
{
    m_spriteSheet->setFrames(frames);
    m_spriteAnimation->setEndValue(frames);
}

int SpriteAnimationItem::frame() const
{
    return m_spriteSheet->frame();
}

void SpriteAnimationItem::setFrame(const int &frame)
{
    m_spriteSheet->setFrame(frame);
}

int SpriteAnimationItem::initialFrame() const
{
    return m_spriteSheet->initialFrame();
}

void SpriteAnimationItem::setInitialFrame(const int &initialFrame)
{
    m_spriteSheet->setInitialFrame(initialFrame);
    m_spriteAnimation->setStartValue(initialFrame);
}

bool SpriteAnimationItem::visible() const
{
    return m_spriteSheet->isVisible();
}

void SpriteAnimationItem::setVisible(const bool &visible)
{
    bool currentState = m_spriteSheet->isVisible();
    if (currentState != visible) {
        m_spriteSheet->setVisible(visible);

        emit visibleChanged();
    }
}

SpriteSheet *SpriteAnimationItem::spriteSheet()
{
    return m_spriteSheet;
}

int SpriteAnimationItem::duration() const
{
    return m_spriteAnimation->duration();
}

void SpriteAnimationItem::setDuration(const int &duration)
{
    int currentState = m_spriteAnimation->duration();
    if (currentState != duration) {
        m_spriteAnimation->setDuration(duration);

        emit durationChanged();
    }
}
