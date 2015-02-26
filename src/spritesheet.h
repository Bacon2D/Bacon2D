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

#ifndef _SPRITESHEET_H_
#define _SPRITESHEET_H_

#include <QtQuick/QQuickPaintedItem>
#include <QUrl>
#include <QtCore/QtGlobal>

class QPixmap;

class SpriteSheet : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(int frame READ frame WRITE setFrame NOTIFY frameChanged)

public:
    SpriteSheet(QQuickItem *parent = 0);

    QUrl source() const;
    void setSource(const QUrl &source);

    int frames() const;
    void setFrames(const int &frames);

    int frame() const;
    void setFrame(const int &frame);

    int initialFrame() const;
    void setInitialFrame(const int &initialFrame);

    bool verticalMirror() const;
    void setVerticalMirror(const bool &verticalMirror);

    bool horizontalMirror() const;
    void setHorizontalMirror(const bool &horizontalMirror);

    void paint(QPainter *painter);

signals:
    void sourceChanged();
    void framesChanged();
    void frameChanged();
    void initialFrameChanged();

private:
    void updateSizeInfo();

private:
    QPixmap *m_pixMap;
    QUrl m_source;
    int m_frames;
    int m_frame;
    int m_initialFrame;
    int m_frameWidth;
    int m_vertical;
    int m_horizontal;
    bool m_mirror;
};

#endif /* _SPRITESHEET_H_ */
