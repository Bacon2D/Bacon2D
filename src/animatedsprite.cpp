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
#include "animatedsprite.h"
#include "spritesheet.h"
#include "spriteanimation.h"
#include "animationchangeevent.h"
#include "animationtransition.h"
#include "spritesheetgrid.h"
#include "spritestrip.h"

#include <QTime>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QPainter>
#include <QQmlProperty>

void AnimatedSprite::append_animation(QQmlListProperty<SpriteAnimation> *list, SpriteAnimation *spriteAnimation)
{
    AnimatedSprite *spriteItem = qobject_cast<AnimatedSprite *>(list->object);

    if (!spriteItem)
        return;

    spriteItem->m_states.insert(spriteAnimation->name(), spriteAnimation);
    connect(spriteAnimation, &SpriteAnimation::frameChanged, spriteItem, [=]() { spriteItem->update(); });

    if (spriteAnimation->spriteStrip() && !spriteAnimation->spriteStrip()->spriteSheet())
        spriteAnimation->spriteStrip()->setSpriteSheet(spriteItem->spriteSheet());
}

int AnimatedSprite::count_animation(QQmlListProperty<SpriteAnimation> *list)
{
    AnimatedSprite *spriteItem = qobject_cast<AnimatedSprite *>(list->object);

    if (!spriteItem)
        return 0;

    return spriteItem->m_states.values().length();
}

SpriteAnimation *AnimatedSprite::at_animation(QQmlListProperty<SpriteAnimation> *list, int index)
{
    AnimatedSprite *spriteItem = qobject_cast<AnimatedSprite *>(list->object);

    if (!spriteItem)
        return nullptr;

    return spriteItem->m_states.values().at(index);
}

/*!
  \qmltype AnimatedSprite
  \inqmlmodule Bacon2D
  \inherits Item
  \brief An Sprite, providing state based
   management of multiple SpriteAnimation animations.
 */
AnimatedSprite::AnimatedSprite(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , m_stateMachine(nullptr)
    , m_stateGroup(nullptr)
    , m_spriteSheet(nullptr)
    , m_verticalScale(1)
    , m_horizontalScale(1)
    , m_fillMode(Bacon2D::PreserveAspectFit)
    , m_entity(nullptr)
    , m_game(nullptr)
    , m_state(Bacon2D::Running)
{
    QQmlProperty(this, "layer.enabled").write(true);
    setFlag(QQuickItem::ItemHasContents);
    setVisible(true);
    setSmooth(true);
}

SpriteSheetGrid *AnimatedSprite::spriteSheet() const
{
    return m_spriteSheet;
}

void AnimatedSprite::setSpriteSheet(SpriteSheetGrid *spriteSheet)
{
    if (m_spriteSheet == spriteSheet)
        return;

    m_spriteSheet = spriteSheet;
    emit spriteSheetChanged();
}

QQmlListProperty<SpriteAnimation> AnimatedSprite::animations() const
{
    return QQmlListProperty<SpriteAnimation>(const_cast<AnimatedSprite *>(this), nullptr,
                                             &AnimatedSprite::append_animation,
                                             &AnimatedSprite::count_animation,
                                             &AnimatedSprite::at_animation,
                                             nullptr);
}

/*!
 * \qmlproperty string AnimatedSprite::animation
 * \brief The current SpriteAnimation state of the Sprite as a string
 */
QString AnimatedSprite::animation() const
{
    return m_animationName;
}

void AnimatedSprite::setAnimation(const QString &animationName, const bool &force)
{
    if (!m_states.contains(animationName)) {
        qWarning() << "SpriteAnimation:" << animationName << "invalid";
        return;
    }

    if (m_state == Bacon2D::Paused || m_state == Bacon2D::Suspended) {
        qWarning() << "SpriteAnimation: isn't active";
        return;
    }

    if (force || (m_animationName != animationName)) {
        // Store previous animation to stop it later
        SpriteAnimation *previousSpriteAnimation = nullptr;
        if (m_states.contains(m_animationName))
            previousSpriteAnimation = m_states[m_animationName];

        m_animationName = animationName;

        // Set width and height after animation is set, also set previous animation
        if (m_states.contains(m_animationName)) {
            SpriteAnimation *spriteAnimation = m_states[m_animationName];

            if (spriteAnimation->spriteSheet()) {
                setImplicitWidth(spriteAnimation->spriteSheet()->width());
                setImplicitHeight(spriteAnimation->spriteSheet()->height());

                spriteAnimation->setPreviousAnimation(previousSpriteAnimation);
            }
        }

        if (!m_stateMachine)
            initializeMachine();

        if (m_stateMachine && m_stateMachine->isRunning())
            m_stateMachine->postEvent(new AnimationChangeEvent(m_animationName));

        emit animationChanged();
    }
}

void AnimatedSprite::initializeMachine()
{
    m_stateMachine = new QStateMachine(this);

    for (SpriteAnimation *spriteAnimation : m_states.values()) {
        AnimationTransition *transition = new AnimationTransition(spriteAnimation);
        spriteAnimation->setParentState(m_stateMachine);
        m_stateMachine->addTransition(transition);
    }

    m_stateMachine->setInitialState(m_states.value(m_animationName)->state());

    connect(m_stateMachine, SIGNAL(started()), this, SLOT(initializeAnimation()));

    m_stateMachine->start();
}

void AnimatedSprite::initializeAnimation()
{
    if (!m_animationName.isEmpty())
        setAnimation(m_animationName, (m_state == Bacon2D::Running));
}

/*!
 * \qmlproperty bool AnimatedSprite::verticalMirror
 * \brief Shows the Sprite mirrored vertically (upside down)
 */
bool AnimatedSprite::verticalMirror() const
{
    return m_verticalScale == -1;
}

void AnimatedSprite::setVerticalMirror(const bool &verticalMirror)
{
    const bool currentState = this->verticalMirror();
    if (currentState == verticalMirror)
        return;

    m_verticalScale = verticalMirror ? -1 : 1;

    for (SpriteAnimation *animation : m_states.values())
        animation->setVerticalMirror(verticalMirror);

    emit verticalMirrorChanged();
}

/*!
 * \qmlproperty bool AnimatedSprite::horizontalMirror
 * \brief Shows the Sprite mirrored horizontally
 */
bool AnimatedSprite::horizontalMirror() const
{
    return m_horizontalScale == -1;
}

void AnimatedSprite::setHorizontalMirror(const bool &horizontalMirror)
{
    const bool currentState = this->horizontalMirror();
    if (currentState == horizontalMirror)
        return;

    m_horizontalScale = horizontalMirror ? -1 : 1;

    for (SpriteAnimation *animation : m_states.values())
        animation->setHorizontalMirror(horizontalMirror);

    emit horizontalMirrorChanged();
}

Entity *AnimatedSprite::entity() const
{
    return m_entity;
}

void AnimatedSprite::setEntity(Entity *entity)
{
    if (m_entity == entity)
        return;

    m_entity = entity;
    emit entityChanged();
}

void AnimatedSprite::onGameStateChanged()
{
    if (m_state != Bacon2D::Inactive)
        setSpriteState(m_game->gameState());
}

void AnimatedSprite::componentComplete()
{
    QQuickItem::componentComplete();

    if (!m_game) {
        QQmlApplicationEngine *engine = qobject_cast<QQmlApplicationEngine *>(qmlEngine(this));

        if (engine && !engine->rootObjects().isEmpty()) {
            m_game = engine->rootObjects().first()->findChild<Game *>();
            connect(m_game, &Game::gameStateChanged, this, &AnimatedSprite::onGameStateChanged);
        }
    }

    m_entity = qobject_cast<Entity *>(parentItem());

    if (m_spriteSheet) {
        for (SpriteAnimation *spriteAnimation : m_states.values()) {
            if (spriteAnimation->spriteStrip()) {
                if (!spriteAnimation->spriteStrip()->spriteSheet())
                    spriteAnimation->spriteStrip()->setSpriteSheet(m_spriteSheet);

                setImplicitWidth(spriteAnimation->spriteStrip()->frameWidth());
                setImplicitHeight(spriteAnimation->spriteStrip()->frameHeight());
            }
        }
    }
}

void AnimatedSprite::paint(QPainter *painter)
{
    if (!painter)
        return;

    const SpriteAnimation *currentSpriteAnimation = m_states.value(m_animationName);

    if (m_spriteSheet && currentSpriteAnimation->spriteStrip() && !m_spriteSheet->pixmap().isNull()) {
        const SpriteStrip *spriteStrip = currentSpriteAnimation->spriteStrip();
        if (spriteStrip->frameWidth() <= 0.0) {
            QPixmap pixmap = m_spriteSheet->pixmap().scaled(width(), height(),
                                                  Bacon2D::PreserveAspectFit ? Qt::KeepAspectRatio : (Bacon2D::PreserveAspectCrop ? Qt::KeepAspectRatioByExpanding : Qt::IgnoreAspectRatio),
                                                  smooth() ? Qt::SmoothTransformation : Qt::FastTransformation);
            painter->drawPixmap(0, 0, pixmap);
        } else if(m_fillMode == Bacon2D::TileHorizontally) {
            QRectF target = QRectF(boundingRect());
            QPixmap pixmap = m_spriteSheet->pixmap().transformed(QTransform().scale(m_horizontalScale, m_verticalScale),
                                                       smooth() ? Qt::SmoothTransformation : Qt::FastTransformation);
            QRectF source = QRectF(spriteStrip->currentFrameX(),
                                   spriteStrip->frameY(),
                                   spriteStrip->frameWidth(),
                                   spriteStrip->frameHeight());

            for (qreal x = 0.0; x < boundingRect().width(); x += spriteStrip->frameWidth()) {
                painter->drawPixmap(target, pixmap, source);
                target.setX(x + spriteStrip->frameWidth());
            }
        } else if (m_fillMode == Bacon2D::TileVertically) {
            QRectF target = QRectF(boundingRect());
            QPixmap pixmap = m_spriteSheet->pixmap().transformed(QTransform().scale(m_horizontalScale, m_verticalScale),
                                                       smooth() ? Qt::SmoothTransformation : Qt::FastTransformation);
            QRectF source = QRectF(spriteStrip->currentFrameX(),
                                   spriteStrip->frameY(),
                                   spriteStrip->frameWidth(),
                                   spriteStrip->frameHeight());

            for (qreal y = 0.0; y < boundingRect().height(); y += spriteStrip->frameHeight()) {
                painter->drawPixmap(target, pixmap, source);
                target.setY(y + spriteStrip->frameHeight());
            }
        } else if (m_fillMode == Bacon2D::Tile) {
            qWarning() << "Untested implementation for Bacon2D::Tile!";

            QRectF target = QRectF(boundingRect());
            QPixmap pixmap = m_spriteSheet->pixmap().transformed(QTransform().scale(m_horizontalScale, m_verticalScale),
                                                       smooth() ? Qt::SmoothTransformation : Qt::FastTransformation);
            QRectF source = QRectF(spriteStrip->currentFrameX(),
                                   spriteStrip->frameY(),
                                   spriteStrip->frameWidth(),
                                   spriteStrip->frameHeight());

            for (qreal x = 0.0; x < boundingRect().width(); x += spriteStrip->frameWidth()) {
                painter->drawPixmap(target, pixmap, source);
                target.setX(x + spriteStrip->frameWidth());
            }

            for (qreal y = 0.0; y < boundingRect().height(); y += spriteStrip->frameHeight()) {
                painter->drawPixmap(target, pixmap, source);
                target.setY(y + spriteStrip->frameHeight());
            }
        } else {
            QRectF target = QRectF(boundingRect());
            QPixmap pixmap = m_spriteSheet->pixmap().transformed(QTransform().scale(m_horizontalScale, m_verticalScale),
                                                       smooth() ? Qt::SmoothTransformation : Qt::FastTransformation);
            QRectF source = QRectF(spriteStrip->currentFrameX(),
                                   spriteStrip->frameY(),
                                   spriteStrip->frameWidth(),
                                   spriteStrip->frameHeight());

            painter->drawPixmap(target, pixmap, source);
        }
    }
}

/*!
  \qmlproperty Bacon2D.State AnimatedSprite::spriteState
  \brief This property holds the current spriteState.
*/
void AnimatedSprite::setSpriteState(const Bacon2D::State &state)
{
    if (state == m_state)
        return;

    m_state = state;

    if (!m_animationName.isEmpty() && m_states.contains(m_animationName)) {
        SpriteAnimation *spriteAnimation = m_states[m_animationName];
        spriteAnimation->setRunning(m_state == Bacon2D::Running);
    }

    emit spriteStateChanged();

    if (!m_stateMachine)
        initializeMachine();

    if (m_state == Bacon2D::Running && !m_stateMachine->isRunning())
        m_stateMachine->start();
    else if (m_state != Bacon2D::Running && m_stateMachine->isRunning())
        m_stateMachine->stop();
}

QPixmap AnimatedSprite::pixmap() const
{
    return m_pixmap;
}

void AnimatedSprite::updateSize()
{
    const SpriteAnimation *currentSpriteAnimation = m_states.value(m_animationName);
    if (currentSpriteAnimation && currentSpriteAnimation->spriteStrip()) {
        setImplicitWidth(currentSpriteAnimation->spriteStrip()->frameWidth());
        setImplicitHeight(currentSpriteAnimation->spriteStrip()->height());
    }
}

void AnimatedSprite::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
//    const QStringList &names = m_states.keys();

//    for (const QString &name : names) {
//        SpriteSheet *spriteSheet = m_states.value(name)->spriteSheet();
//        if (spriteSheet) {
//            spriteSheet->setWidth(newGeometry.width());
//            spriteSheet->setHeight(newGeometry.height());
//        }
//    }
}
