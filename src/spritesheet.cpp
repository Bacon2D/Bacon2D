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

#include "spritesheet.h"

#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtQml/QQmlProperty>

SpriteSheet::SpriteSheet(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , m_pixmap(QPixmap())
    , m_horizontalFrameCount(0)
    , m_verticalFrameCount(0)
    , m_frames(0)
    , m_frame(0)
    , m_initialFrame(0)
    , m_finalFrame(0)
    , m_vertical(1)
    , m_horizontal(1)
    , m_frameX(0.0)
    , m_frameY(0.0)
    , m_frameWidth(0.0)
    , m_frameHeight(0.0)
    , m_mirror(false)
{
    setVisible(false);
    QQmlProperty(this, "layer.enabled").write(true);
}

void SpriteSheet::setPixmap(const QPixmap &pixmap)
{
    m_pixmap = pixmap;
    updateSizeInfo();
}

void SpriteSheet::paint(QPainter *painter)
{
    if (!m_pixmap.isNull()) {
        if (!m_frames)
            painter->drawPixmap(0, 0, m_pixmap);
        else {
            QRectF target = QRectF(boundingRect());
            QPixmap pixmap = m_pixmap.transformed(QTransform().scale(m_horizontal, m_vertical), Qt::FastTransformation);
            QRectF source = QRectF((horizontalMirror() ? ((m_frames - (m_finalFrame + 1) + m_frame - m_initialFrame) * frameWidth())
                                                       : (m_frame * frameWidth())) + frameX(),
                                   frameY(),
                                   frameWidth(),
                                   frameHeight());

            painter->drawPixmap(target, pixmap, source);
        }
    }
}

int SpriteSheet::frames() const
{
    return m_frames;
}

void SpriteSheet::setFrames(const int &frames)
{
    if (m_frames != frames) {
        m_frames = frames;

        if (!m_finalFrame)
            m_finalFrame = m_frames - 1;

        updateSizeInfo();

        emit framesChanged();
    }
}

int SpriteSheet::horizontalFrameCount() const
{
    return m_horizontalFrameCount;
}

void SpriteSheet::setHorizontalFrameCount(const int &horizontalFrameCount)
{
    if (m_horizontalFrameCount == horizontalFrameCount)
       return;

    m_horizontalFrameCount = horizontalFrameCount;
    emit horizontalFrameCountChanged();
}

int SpriteSheet::verticalFrameCount() const
{
    return m_verticalFrameCount;
}

void SpriteSheet::setVerticalFrameCount(const int &verticalFrameCount)
{
    if (m_verticalFrameCount = verticalFrameCount)
        return;

    m_verticalFrameCount = verticalFrameCount;
    emit verticalFrameCountChanged();
}

int SpriteSheet::frame() const
{
    return m_frame;
}

void SpriteSheet::setFrame(const int &frame)
{
    if (m_frame != frame && frame >= 0 && frame < m_frames) {
        m_frame = frame;
        update();

        emit frameChanged();
    }
}

qreal SpriteSheet::frameX() const
{
    return m_frameX <= 0.0 ? 0.0 : m_frameX;
}

void SpriteSheet::setFrameX(const qreal &frameX)
{
    if (frameX == m_frameX)
        return;

    m_frameX = frameX;
    emit frameXChanged();
}

qreal SpriteSheet::frameY() const
{
    return m_frameY <= 0.0 ? 0.0 : m_frameY;
}

void SpriteSheet::setFrameY(const qreal &frameY)
{
    if (m_frameY == frameY)
        return;

    m_frameY = frameY;
    emit frameYChanged();
}

qreal SpriteSheet::frameWidth() const
{
    if (m_frameWidth <= 0.0 && m_frames <= 0 && m_horizontalFrameCount > 0)
        return m_pixmap.width() / m_horizontalFrameCount;

    return m_frameWidth <= 0.0 && m_frames > 0? m_pixmap.width() / m_frames : m_frameWidth;
}

void SpriteSheet::setFrameWidth(const qreal &frameWidth)
{
    if (m_frameWidth == frameWidth)
        return;

    m_frameWidth = frameWidth;
    updateSizeInfo();
    emit frameWidthChanged();
}

qreal SpriteSheet::frameHeight() const
{
    return m_frameHeight <= 0.0 ? (m_horizontalFrameCount == 0 ? m_pixmap.height() : m_pixmap.height() / m_horizontalFrameCount) : m_frameHeight;
}

void SpriteSheet::setFrameHeight(const qreal &frameHeight)
{
    if (m_frameHeight == frameHeight)
        return;

    m_frameHeight = frameHeight;
    updateSizeInfo();
    emit frameHeightChanged();
}

void SpriteSheet::updateSizeInfo()
{
    if (m_pixmap.isNull() || (m_frames <= 0 && m_horizontalFrameCount <= 0))
        return;

    setImplicitWidth(frameWidth());
    setImplicitHeight(frameHeight());
}

int SpriteSheet::initialFrame() const
{
    return m_initialFrame;
}

void SpriteSheet::setInitialFrame(const int &initialFrame)
{
    if (m_initialFrame != initialFrame) {
        m_initialFrame = initialFrame;

        emit initialFrameChanged();
    }
}

int SpriteSheet::finalFrame() const
{
    return m_finalFrame;
}

void SpriteSheet::setFinalFrame(const int &finalFrame)
{
    if (m_finalFrame == finalFrame)
        return;

    m_finalFrame = finalFrame;
    emit finalFrameChanged();
}

bool SpriteSheet::verticalMirror() const
{
    return m_vertical == -1;
}

void SpriteSheet::setVerticalMirror(const bool &verticalMirror)
{
    m_vertical = (verticalMirror) ? -1 : 1;

    if (m_vertical == -1 || m_horizontal == -1)
        m_mirror = true;

    update();
}

bool SpriteSheet::horizontalMirror() const
{
    return m_horizontal == -1;
}

void SpriteSheet::setHorizontalMirror(const bool &horizontalMirror)
{
    m_horizontal = (horizontalMirror) ? -1 : 1;

    if (m_vertical == -1 || m_horizontal == -1)
        m_mirror = true;

    update();
}
