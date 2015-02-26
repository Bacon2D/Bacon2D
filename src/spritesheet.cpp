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
    , m_pixMap(0)
    , m_frames(0)
    , m_frame(0)
    , m_initialFrame(0)
    , m_frameWidth(0)
    , m_vertical(1)
    , m_horizontal(1)
    , m_mirror(false)
{
    setVisible(false);
    QQmlProperty(this, "layer.enabled").write(true);
}

QUrl SpriteSheet::source() const
{
    return m_source;
}

void SpriteSheet::setSource(const QUrl &source)
{
    if (m_source == source)
        return;

    if (m_pixMap)
        delete m_pixMap;

    m_source = source;

    if (m_source.url().startsWith("qrc:/"))
        m_pixMap = new QPixmap(m_source.url().replace(QString("qrc:/"), QString(":/")));
    else
        m_pixMap = new QPixmap(m_source.toLocalFile());

    if (!m_pixMap)
        qCritical() << QString("Bacon2D>>Image \'%1\' failed to load!").arg(m_source.url());

    if (m_frames)
        updateSizeInfo();

    update();

    emit sourceChanged();
}

void SpriteSheet::paint(QPainter *painter)
{
    if (m_pixMap) {
        if (!m_frames)
            painter->drawPixmap(0, 0, *m_pixMap);
        else
            if (m_mirror)
                painter->drawPixmap(0, 0,
                        m_pixMap->transformed(QTransform().scale(m_horizontal, m_vertical),
                        Qt::FastTransformation), (m_frame * m_frameWidth), 0, m_frameWidth,
                        m_pixMap->height());
            else
                painter->drawPixmap(0, 0, *m_pixMap, (m_frame * m_frameWidth), 0, m_frameWidth, m_pixMap->height());
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

        if (m_pixMap)
            updateSizeInfo();

        update();

        emit framesChanged();
    }
}

int SpriteSheet::frame() const
{
    return m_frame;
}

void SpriteSheet::setFrame(const int &frame)
{
    if (m_frame != frame
        && frame < m_frames) { //FIXME: using qt5 and non infinite animations, the property animation updates this value to m_frames, the max should be m_frames-1
        m_frame = frame;

        update();

        emit frameChanged();
    }
}

void SpriteSheet::updateSizeInfo()
{
    m_frameWidth = m_pixMap->width() / m_frames;
    setWidth(m_frameWidth);
    setHeight(m_pixMap->height());
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

bool SpriteSheet::verticalMirror() const
{
    return m_vertical == -1;
}

void SpriteSheet::setVerticalMirror(const bool &verticalMirror)
{
    m_vertical = (verticalMirror) ? -1 : 1;

    if (m_vertical == -1 || m_horizontal == -1)
        m_mirror = true;
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
}
