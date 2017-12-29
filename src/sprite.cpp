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

#include "game.h"
#include "scene.h"
#include "sprite.h"
#include "spritesheet.h"
#include "spriteanimation.h"
#include "animationchangeevent.h"
#include "animationtransition.h"
#include "spritecollection.h"

#include <QTime>
#include <QDebug>

/*!
  \qmltype Sprite
  \inqmlmodule Bacon2D
  \inherits Item
  \brief An Sprite, providing state based
   management of multiple SpriteAnimation animations.
 */
Sprite::Sprite(QQuickItem *parent)
    : QQuickItem(parent)
    , m_spriteSheet(new SpriteSheet(this))
    , m_verticalMirror(false)
    , m_horizontalMirror(false)
    , m_verticalFrameCount(0)
    , m_horizontalFrameCount(0)
{
}

Sprite::~Sprite()
{
    SpriteCollection::instance().removeSprite(this);
}

/*!
 * \qmlproperty string SpriteAnimation::source
 * \brief QUrl for the source image
 */

QUrl Sprite::source() const
{
    return m_source;
}

void Sprite::setSource(const QUrl &source)
{
    if (m_source == source)
        return;

    m_source = source;

    m_pixmap = SpriteCollection::instance().addSprite(this);

    setSourceSize(m_pixmap.size());

    emit sourceChanged();
}

QSize Sprite::sourceSize() const
{
    return m_sourceSize;
}

void Sprite::setSourceSize(const QSize &sourceSize)
{
    if (m_sourceSize == sourceSize)
        return;

    m_sourceSize = sourceSize;
    setImplicitWidth(sourceSize.width());
    setImplicitHeight(sourceSize.height());

    emit sourceSizeChanged();
}

/*!
 * \qmlproperty bool Sprite::verticalMirror
 * \brief Shows the Sprite mirrored vertically (upside down)
 */
bool Sprite::verticalMirror() const
{
    return m_verticalMirror;
}

void Sprite::setVerticalMirror(const bool &verticalMirror)
{
    if (m_verticalMirror == verticalMirror)
        return;

    m_verticalMirror = verticalMirror;
    emit verticalMirrorChanged();
}

/*!
 * \qmlproperty bool Sprite::horizontalMirror
 * \brief Shows the Sprite mirrored horizontally
 */
bool Sprite::horizontalMirror() const
{
    return m_horizontalMirror;
}

void Sprite::setHorizontalMirror(const bool &horizontalMirror)
{
    if (m_horizontalMirror == horizontalMirror)
        return;

    m_horizontalMirror = horizontalMirror;
    emit horizontalMirrorChanged();
}

int Sprite::verticalFrameCount() const
{
    return m_verticalFrameCount;
}

void Sprite::setVerticalFrameCount(const int &verticalFrameCount)
{
    if (m_verticalFrameCount == verticalFrameCount)
        return;

    m_verticalFrameCount = verticalFrameCount;
    emit verticalFrameCountChanged();
}

int Sprite::horizontalFrameCount() const
{
    return m_horizontalFrameCount;
}

void Sprite::setHorizontalFrameCount(const int &horizontalFrameCount)
{
    if (m_horizontalFrameCount == horizontalFrameCount)
        return;

    m_horizontalFrameCount = horizontalFrameCount;
    emit horizontalFrameCountChanged();
}

qreal Sprite::frameX() const
{
    return m_spriteSheet->frameX();
}

void Sprite::setFrameX(const qreal &frameX)
{
    m_spriteSheet->setFrameX(frameX);
}

qreal Sprite::frameY() const
{
    return m_spriteSheet->frameY();
}

void Sprite::setFrameY(const qreal &frameY)
{
    m_spriteSheet->setFrameY(frameY);
}

qreal Sprite::frameWidth() const
{
    return m_spriteSheet->frameWidth();
}

void Sprite::setFrameWidth(const qreal &frameWidth)
{
    m_spriteSheet->setFrameWidth(frameWidth);
}

qreal Sprite::frameHeight() const
{
    return m_spriteSheet->frameHeight();
}

void Sprite::setFrameHeight(const qreal &frameHeight)
{
    m_spriteSheet->setFrameHeight(frameHeight);
}

QPixmap Sprite::pixmap() const
{
    return m_pixmap;
}
