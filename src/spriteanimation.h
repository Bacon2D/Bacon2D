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

#ifndef _SPRITEANIMATION_H_
#define _SPRITEANIMATION_H_

#include <QtCore/QState>
#include <QtCore/QPropertyAnimation>
#include <QUrl>
#include <QSize>

class SpriteSheet;
class QPropertyAnimation;

class SpriteAnimation : public QState
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(qreal frameX READ frameX WRITE setFrameX NOTIFY frameXChanged)
    Q_PROPERTY(qreal frameY READ frameY WRITE setFrameY NOTIFY frameYChanged)
    Q_PROPERTY(qreal frameWidth READ frameWidth WRITE setFrameWidth NOTIFY frameWidthChanged)
    Q_PROPERTY(qreal frameHeight READ frameHeight WRITE setFrameHeight NOTIFY frameHeightChanged)
    Q_PROPERTY(int frames READ frames WRITE setFrames NOTIFY framesChanged)
    Q_PROPERTY(int frame READ frame WRITE setFrame NOTIFY frameChanged)
    Q_PROPERTY(int initialFrame READ initialFrame WRITE setInitialFrame NOTIFY initialFrameChanged)
    Q_PROPERTY(int finalFrame READ finalFrame WRITE setFinalFrame NOTIFY finalFrameChanged)
    Q_PROPERTY(bool running READ running  NOTIFY runningChanged)
    Q_PROPERTY(int loops READ loops WRITE setLoops NOTIFY loopsChanged)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(int duration READ duration WRITE setDuration NOTIFY durationChanged)
    Q_PROPERTY(bool inverse READ inverse WRITE setInverse NOTIFY inverseChanged)
public:
    SpriteAnimation(QState *parent = 0);
    ~SpriteAnimation();

    QString name() const;
    void setName(const QString &name);

    bool running() const;
    void setRunning(const bool &running);

    int loops() const;
    void setLoops(const int &loops);

    int frames() const;
    void setFrames(const int &frames);

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

    bool visible() const;
    void setVisible(const bool &visible);

    int duration() const;
    void setDuration(const int &duration);

    bool inverse() const;
    void setInverse(const bool &inverse);

    bool verticalMirror() const;
    void setVerticalMirror(const bool &verticalMirror);

    bool horizontalMirror() const;
    void setHorizontalMirror(const bool &horizontalMirror);

    SpriteSheet *spriteSheet();

    SpriteAnimation *previousAnimation() const;
    void setPreviousAnimation(SpriteAnimation *);

signals:
    void runningChanged();
    void loopsChanged();
    void sourceChanged();
    void framesChanged();
    void frameChanged();
    void frameXChanged();
    void frameYChanged();
    void frameWidthChanged();
    void frameHeightChanged();
    void sourceSizeChanged();
    void initialFrameChanged();
    void finalFrameChanged();
    void visibleChanged();
    void durationChanged();
    void inverseChanged();
    void finished();

private slots:
    void onStateChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);

private:
    QString m_name;
    SpriteSheet *m_spriteSheet;
    QPropertyAnimation *m_spriteAnimation;
    SpriteAnimation *m_previousAnimationItem;
    bool m_inverse;
};

#endif /* _SPRITEANIMATION_H_ */
