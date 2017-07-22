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

#ifndef _ANIMATEDSPRITE_H_
#define _ANIMATEDSPRITE_H_

#include "entity.h"
#include "enums.h"
#include "game.h"

#include <QtCore/QHash>
#include <QtCore/QStateMachine>
#include <QtQuick/QQuickItem>
#include <QtCore/QtGlobal>
#include <QPixmap>

class Scene;
class SpriteAnimation;
class SpriteSheet;

class AnimatedSprite : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QSize sourceSize READ sourceSize NOTIFY sourceSizeChanged)
    Q_PROPERTY(QQmlListProperty<SpriteAnimation> animations READ animations)
    Q_PROPERTY(QString animation READ animation WRITE setAnimation NOTIFY animationChanged)
    Q_PROPERTY(bool verticalMirror READ verticalMirror WRITE setVerticalMirror NOTIFY verticalMirrorChanged)
    Q_PROPERTY(bool horizontalMirror READ horizontalMirror WRITE setHorizontalMirror NOTIFY horizontalMirrorChanged)
    Q_PROPERTY(int verticalFrameCount READ verticalFrameCount WRITE setVerticalFrameCount NOTIFY verticalFrameCountChanged)
    Q_PROPERTY(int horizontalFrameCount READ horizontalFrameCount WRITE setHorizontalFrameCount NOTIFY horizontalFrameCountChanged)
    Q_PROPERTY(Entity *entity READ entity WRITE setEntity NOTIFY entityChanged)
    Q_PROPERTY(Bacon2D::State spriteState READ spriteState WRITE setSpriteState NOTIFY spriteStateChanged)

public:
    AnimatedSprite(QQuickItem *parent = 0);

    QUrl source() const;
    void setSource(const QUrl &source);

    QSize sourceSize() const;
    void setSourceSize(const QSize &sourceSize);

    QQmlListProperty<SpriteAnimation> animations() const;

    QString animation() const;
    void setAnimation(const QString &animation, const bool &force = false);

    bool verticalMirror() const;
    void setVerticalMirror(const bool &verticalMirror);

    bool horizontalMirror() const;
    void setHorizontalMirror(const bool &horizontalMirror);

    int verticalFrameCount() const;
    void setVerticalFrameCount(const int &verticalFrameCount);

    int horizontalFrameCount() const;
    void setHorizontalFrameCount(const int &horizontalFrameCount);

    Entity *entity() const;
    void setEntity(Entity *entity);

    Bacon2D::State spriteState() const { return m_state; }
    void setSpriteState(const Bacon2D::State &state);

    QPixmap pixmap() const;

public slots:
    void initializeAnimation();
    void onGameStateChanged();

signals:
    void animationChanged();
    void verticalMirrorChanged();
    void horizontalMirrorChanged();
    void verticalFrameCountChanged();
    void horizontalFrameCountChanged();
    void entityChanged();
    void spriteStateChanged();
    void sourceChanged();
    void sourceSizeChanged();

private:
    void initializeMachine();

private:
    static void append_animation(QQmlListProperty<SpriteAnimation> *list, SpriteAnimation *animation);
    static int count_animation(QQmlListProperty<SpriteAnimation> *list);
    static SpriteAnimation *at_animation(QQmlListProperty<SpriteAnimation> *list, int index);

    QStateMachine *m_stateMachine;
    QState *m_stateGroup;
    QHash<QString, SpriteAnimation *> m_states;
    QUrl m_source;
    QSize m_sourceSize;
    QString m_animation;
    bool m_verticalMirror;
    bool m_horizontalMirror;
    int m_verticalFrameCount;
    int m_horizontalFrameCount;
    Entity *m_entity;
    Game *m_game;
    Bacon2D::State m_state;
    QPixmap m_pixmap;
};

#endif /* _ANIMATEDSPRITE_H_ */
