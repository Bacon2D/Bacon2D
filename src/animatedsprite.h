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
#include "spritesheetgrid.h"

#include <QtCore/QHash>
#include <QtCore/QStateMachine>
#include <QQuickPaintedItem>
#include <QtCore/QtGlobal>
#include <QPixmap>

class Scene;
class SpriteAnimation;
class SpriteSheet;

class AnimatedSprite : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(SpriteSheetGrid* spriteSheet READ spriteSheet WRITE setSpriteSheet NOTIFY spriteSheetChanged)
    Q_PROPERTY(QQmlListProperty<SpriteAnimation> animations READ animations)
    Q_PROPERTY(QString animation READ animation WRITE setAnimation NOTIFY animationChanged)
    Q_PROPERTY(bool verticalMirror READ verticalMirror WRITE setVerticalMirror NOTIFY verticalMirrorChanged)
    Q_PROPERTY(bool horizontalMirror READ horizontalMirror WRITE setHorizontalMirror NOTIFY horizontalMirrorChanged)
    Q_PROPERTY(Entity *entity READ entity WRITE setEntity NOTIFY entityChanged)
    Q_PROPERTY(Bacon2D::State spriteState READ spriteState WRITE setSpriteState NOTIFY spriteStateChanged)

public:
    explicit AnimatedSprite(QQuickItem *parent = nullptr);

    SpriteSheetGrid *spriteSheet() const;
    void setSpriteSheet(SpriteSheetGrid *spriteSheet);

    QQmlListProperty<SpriteAnimation> animations() const;

    QString animation() const;
    void setAnimation(const QString &animationName, const bool &force = false);

    bool verticalMirror() const;
    void setVerticalMirror(const bool &verticalMirror);

    bool horizontalMirror() const;
    void setHorizontalMirror(const bool &horizontalMirror);

    Bacon2D::FillMode fillMode() const;
    void setFillMode(Bacon2D::FillMode fillMode);

    Entity *entity() const;
    void setEntity(Entity *entity);

    Bacon2D::State spriteState() const { return m_state; }
    void setSpriteState(const Bacon2D::State &state);

    QPixmap pixmap() const;

    void updateSize();

    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;
    void componentComplete() override;
    void paint(QPainter *painter) override;

public slots:
    void initializeAnimation();
    void onGameStateChanged();

signals:
    void spriteSheetChanged();
    void animationChanged();
    void verticalMirrorChanged();
    void horizontalMirrorChanged();
    void fillModeChanged();
    void entityChanged();
    void spriteStateChanged();

private:
    void initializeMachine();

private:
    QStateMachine *m_stateMachine;
    QState *m_stateGroup;
    SpriteSheetGrid *m_spriteSheet;
    QHash<QString, SpriteAnimation *> m_states;
    QString m_animationName;
    int m_verticalScale;
    int m_horizontalScale;
    int m_fillMode;
    Entity *m_entity;
    Game *m_game;
    Bacon2D::State m_state;
    QPixmap m_pixmap;

    static void append_animation(QQmlListProperty<SpriteAnimation> *list, SpriteAnimation *spriteAnimation);
    static int count_animation(QQmlListProperty<SpriteAnimation> *list);
    static SpriteAnimation *at_animation(QQmlListProperty<SpriteAnimation> *list, int index);
};

#endif /* _ANIMATEDSPRITE_H_ */
