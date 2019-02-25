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

#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <QtQuick/QQuickPaintedItem>
#include <QUrl>
#include <QtCore/QtGlobal>
#include <QPixmap>
#include "enums.h"

class SpriteSheet : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(int frame READ frame WRITE setFrame NOTIFY frameChanged)

public:
    explicit SpriteSheet(QQuickItem *parent = nullptr);

    void setPixmap(const QPixmap &pixmap);

    int frames() const;
    void setFrames(const int &frames);

    int horizontalFrameCount() const;
    void setHorizontalFrameCount(const int &horizontalFrameCount);

    int verticalFrameCount() const;
    void setVerticalFrameCount(const int &verticalFrameCount);

    int frame() const;
    void setFrame(const int &frame);

    qreal frameX() const;
    void setFrameX(const qreal &frameX);

    qreal frameY() const;
    void setFrameY(const qreal &frameY);

    qreal frameWidth() const;
    void setFrameWidth(const qreal &frameWidth);

    qreal frameHeight() const;
    void setFrameHeight(const qreal &frameHeight);

    int initialFrame() const;
    void setInitialFrame(const int &initialFrame);

    int finalFrame() const;
    void setFinalFrame(const int &finalFrame);

    bool verticalMirror() const;
    void setVerticalMirror(const bool &verticalMirror);

    bool horizontalMirror() const;
    void setHorizontalMirror(const bool &horizontalMirror);

    Bacon2D::FillMode fillMode() const;
    void setFillMode(Bacon2D::FillMode fillMode);

    void paint(QPainter *painter);
signals:
    void sourceChanged();
    void horizontalFrameCountChanged();
    void verticalFrameCountChanged();
    void framesChanged();
    void frameChanged();
    void frameXChanged();
    void frameYChanged();
    void frameWidthChanged();
    void frameHeightChanged();
    void initialFrameChanged();
    void finalFrameChanged();
    void sourceSizeChanged();
    void fillModeChanged();
private:
    QPixmap m_pixmap;
    int m_horizontalFrameCount;
    int m_verticalFrameCount;
    int m_frames;
    int m_frame;
    int m_initialFrame;
    int m_finalFrame;
    qreal m_frameX;
    qreal m_frameY;
    qreal m_frameWidth;
    qreal m_frameHeight;
    int m_vertical;
    int m_horizontal;
    bool m_mirror;
    Bacon2D::FillMode m_fillMode;
private:
    void updateSizeInfo();
};

#endif // SPRITESHEET_H
