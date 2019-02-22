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
#include <QQmlParserStatus>

class SpriteSheetGrid;
class SpriteStrip;

class SpriteAnimation : public QObject, public QQmlParserStatus
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(SpriteStrip* spriteStrip READ spriteStrip WRITE setSpriteStrip NOTIFY spriteStripChanged)
    Q_PROPERTY(int frames READ frames NOTIFY framesChanged)
    Q_PROPERTY(int frame READ frame NOTIFY frameChanged)
    Q_PROPERTY(bool running READ running  NOTIFY runningChanged)
    Q_PROPERTY(int loops READ loops WRITE setLoops NOTIFY loopsChanged)
    Q_PROPERTY(int duration READ duration WRITE setDuration NOTIFY durationChanged)
    Q_PROPERTY(bool inverse READ inverse WRITE setInverse NOTIFY inverseChanged)

public:
    explicit SpriteAnimation(QObject *parent = nullptr);
    ~SpriteAnimation() override;

    QString name() const;
    void setName(const QString &name);

    int frames() const;
    int frame() const;

    bool running() const;
    void setRunning(const bool &running);

    int loops() const;
    void setLoops(const int &loops);

    SpriteStrip *spriteStrip() const;
    void setSpriteStrip(SpriteStrip *spriteStrip);

    int duration() const;
    void setDuration(const int &duration);

    bool inverse() const;
    void setInverse(const bool &inverse);

    SpriteSheetGrid *spriteSheet() const;

    SpriteAnimation *previousAnimation() const;
    void setPreviousAnimation(SpriteAnimation *previousAnimation);

    QState *state() const;
    QAbstractAnimation *animation() const;

    void classBegin() override;
    void componentComplete() override;

    void setParentState(QState *state);

signals:
    void spriteStripChanged();
    void runningChanged();
    void loopsChanged();
    void framesChanged();
    void frameChanged();
    void durationChanged();
    void inverseChanged();
    void finished();
private:
    QString m_name;
    SpriteStrip *m_spriteStrip;
    SpriteStrip *m_defaultSpriteStrip;
    SpriteSheetGrid *m_spriteSheet;
    QPropertyAnimation *m_animation;
    QState *m_state;
    SpriteAnimation *m_previousSpriteAnimation;
    bool m_inverse;

    void onStateChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);
    void updateStartValue();
    void updateEndValue();
};

#endif /* _SPRITEANIMATION_H_ */
