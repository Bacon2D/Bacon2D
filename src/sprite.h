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

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "entity.h"
#include "enums.h"
#include "game.h"

#include <QtCore/QHash>
#include <QtCore/QStateMachine>
#include <QtQuick/QQuickItem>
#include <QtCore/QtGlobal>
#include <QPixmap>

class SpriteSheet;

class Sprite : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QSize sourceSize READ sourceSize NOTIFY sourceSizeChanged)
    Q_PROPERTY(bool verticalMirror READ verticalMirror WRITE setVerticalMirror NOTIFY verticalMirrorChanged)
    Q_PROPERTY(bool horizontalMirror READ horizontalMirror WRITE setHorizontalMirror NOTIFY horizontalMirrorChanged)
    Q_PROPERTY(int verticalFrameCount READ verticalFrameCount WRITE setVerticalFrameCount NOTIFY verticalFrameCountChanged)
    Q_PROPERTY(int horizontalFrameCount READ horizontalFrameCount WRITE setHorizontalFrameCount NOTIFY horizontalFrameCountChanged)
    Q_PROPERTY(qreal frameX READ frameX WRITE setFrameX NOTIFY frameXChanged)
    Q_PROPERTY(qreal frameY READ frameY WRITE setFrameY NOTIFY frameYChanged)
    Q_PROPERTY(qreal frameWidth READ frameWidth WRITE setFrameWidth NOTIFY frameWidthChanged)
    Q_PROPERTY(qreal frameHeight READ frameHeight WRITE setFrameHeight NOTIFY frameHeightChanged)
public:
    Sprite(QQuickItem *parent = 0);
    ~Sprite();

    QUrl source() const;
    void setSource(const QUrl &source);

    QSize sourceSize() const;
    void setSourceSize(const QSize &sourceSize);

    bool verticalMirror() const;
    void setVerticalMirror(const bool &verticalMirror);

    bool horizontalMirror() const;
    void setHorizontalMirror(const bool &horizontalMirror);

    int verticalFrameCount() const;
    void setVerticalFrameCount(const int &verticalFrameCount);

    int horizontalFrameCount() const;
    void setHorizontalFrameCount(const int &horizontalFrameCount);

    qreal frameX() const;
    void setFrameX(const qreal &frameX);

    qreal frameY() const;
    void setFrameY(const qreal &frameY);

    qreal frameWidth() const;
    void setFrameWidth(const qreal &frameWidth);

    qreal frameHeight() const;
    void setFrameHeight(const qreal &frameHeight);

    QPixmap pixmap() const;

signals:
    void verticalMirrorChanged();
    void horizontalMirrorChanged();
    void verticalFrameCountChanged();
    void horizontalFrameCountChanged();
    void sourceChanged();
    void sourceSizeChanged();
    void frameXChanged();
    void frameYChanged();
    void frameWidthChanged();
    void frameHeightChanged();

private:

private:
    QUrl m_source;
    QSize m_sourceSize;
    bool m_verticalMirror;
    bool m_horizontalMirror;
    int m_verticalFrameCount;
    int m_horizontalFrameCount;
    SpriteSheet *m_spriteSheet;
    QPixmap m_pixmap;
};

#endif /* _SPRITE_H_ */
