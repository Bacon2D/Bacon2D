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

#include <QTime>
#include <QDebug>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQmlApplicationEngine>

void AnimatedSprite::append_animation(QQmlListProperty<SpriteAnimation> *list, SpriteAnimation *animation)
{
    AnimatedSprite *spriteItem = qobject_cast<AnimatedSprite *>(list->object);

    if (!spriteItem)
        return;

    spriteItem->m_states.insert(animation->name(), animation);
    animation->spriteSheet()->setParentItem(spriteItem);
    animation->spriteSheet()->setPixmap(spriteItem->pixmap());
    animation->spriteSheet()->setHorizontalFrameCount(spriteItem->horizontalFrameCount());
    animation->spriteSheet()->setVerticalFrameCount(spriteItem->verticalFrameCount());

    connect(spriteItem, &AnimatedSprite::sourceChanged, [animation, spriteItem]() {
        animation->spriteSheet()->setPixmap(spriteItem->pixmap());
    });
    connect(spriteItem, &AnimatedSprite::verticalFrameCountChanged, [animation, spriteItem]() {
        animation->spriteSheet()->setVerticalFrameCount(spriteItem->verticalFrameCount());
    });

    connect(spriteItem, &AnimatedSprite::horizontalFrameCountChanged, [animation, spriteItem]() {
        animation->spriteSheet()->setHorizontalFrameCount(spriteItem->horizontalFrameCount());
        animation->setFrames(animation->spriteSheet()->frames());
    });
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
    : QQuickItem(parent)
    , m_stateMachine(0)
    , m_stateGroup(0)
    , m_entity(0)
    , m_game(0)
    , m_verticalMirror(false)
    , m_horizontalMirror(false)
    , m_verticalFrameCount(0)
    , m_horizontalFrameCount(0)
    , m_state(Bacon2D::Running)
{
}

/*!
 * \qmlproperty string SpriteAnimation::source
 * \brief QUrl for the source image
 */

QUrl AnimatedSprite::source() const
{
    return m_source;
}

void AnimatedSprite::setSource(const QUrl &source)
{
    if (m_source == source)
        return;

    m_source = source;

    if (Game::loadedPixmaps().contains(m_source))
        m_pixmap = Game::loadedPixmaps().value(m_source);
    else {
        if (m_source.url().startsWith("qrc:/"))
            m_pixmap = QPixmap(m_source.url().replace(QString("qrc:/"), QString(":/")));
        else
            m_pixmap = QPixmap(m_source.toLocalFile());
    }

    if (m_pixmap.isNull())
        qCritical() << QString("Bacon2D>>Image \'%1\' failed to load!").arg(m_source.url());
    else
        Game::loadedPixmaps().insert(m_source, m_pixmap);

    setSourceSize(m_pixmap.size());

    emit sourceChanged();
}

QSize AnimatedSprite::sourceSize() const
{
    return m_sourceSize;
}

void AnimatedSprite::setSourceSize(const QSize &sourceSize)
{
    if (m_sourceSize == sourceSize)
        return;

    m_sourceSize = sourceSize;
    setImplicitWidth(sourceSize.width());
    setImplicitHeight(sourceSize.height());

    emit sourceSizeChanged();
}

QQmlListProperty<SpriteAnimation> AnimatedSprite::animations() const
{
    return QQmlListProperty<SpriteAnimation>(const_cast<AnimatedSprite *>(this), 0,
                                             &AnimatedSprite::append_animation,
                                             &AnimatedSprite::count_animation,
                                             &AnimatedSprite::at_animation,
                                             0);
}

/*!
 * \qmlproperty string AnimatedSprite::animation
 * \brief The current SpriteAnimation state of the Sprite as a string
 */
QString AnimatedSprite::animation() const
{
    return m_animation;
}

void AnimatedSprite::setAnimation(const QString &animation, const bool &force)
{
    if (!m_states.contains(animation)) {
        qWarning() << "SpriteAnimation:" << animation << "invalid";
        return;
    }

    if (m_state == Bacon2D::Paused || m_state == Bacon2D::Suspended) {
        qWarning() << "SpriteAnimation: isn't active";
        return;
    }

    if (force || (m_animation != animation)) {
        // Store previous animation to stop it later
        SpriteAnimation *previousAnimationItem = nullptr;
        if (m_animation != QString() && m_states.contains(m_animation))
            previousAnimationItem = m_states[m_animation];

        m_animation = animation;

        // Set width and height after animation is set, also set previous animation
        if (m_animation != QString() && m_states.contains(m_animation)) {
            SpriteAnimation *animationItem = m_states[m_animation];
            setImplicitWidth(animationItem->spriteSheet()->width());
            setImplicitHeight(animationItem->spriteSheet()->height());

            animationItem->setPreviousAnimation(previousAnimationItem);
        }

        if (!m_stateMachine)
            initializeMachine();

        if (m_stateMachine && m_stateMachine->isRunning())
            m_stateMachine->postEvent(new AnimationChangeEvent(m_animation));

        emit animationChanged();
    }
}

void AnimatedSprite::initializeMachine()
{
    m_stateMachine= new QStateMachine;
    m_stateGroup = new QState(QState::ParallelStates);

    SpriteAnimation *animation;
    foreach (animation, m_states.values()) {
        AnimationTransition *transition = new AnimationTransition(animation);
        animation->setParent(m_stateGroup);
        animation->addTransition(transition);
    }

    m_stateMachine->addState(m_stateGroup);
    m_stateMachine->setInitialState(m_stateGroup);

    connect(m_stateMachine, SIGNAL(started()), this, SLOT(initializeAnimation()));

    m_stateMachine->start();
}

void AnimatedSprite::initializeAnimation()
{
    if (m_animation != QString())
        setAnimation(m_animation, (m_state == Bacon2D::Running));
}

/*!
 * \qmlproperty bool AnimatedSprite::verticalMirror
 * \brief Shows the Sprite mirrored vertically (upside down)
 */
bool AnimatedSprite::verticalMirror() const
{
    return m_verticalMirror;
}

void AnimatedSprite::setVerticalMirror(const bool &verticalMirror)
{
    if (m_verticalMirror == verticalMirror)
        return;

    m_verticalMirror = verticalMirror;

    foreach (SpriteAnimation *animation, m_states.values())
        animation->setVerticalMirror(m_verticalMirror);

    emit verticalMirrorChanged();
}

/*!
 * \qmlproperty bool AnimatedSprite::horizontalMirror
 * \brief Shows the Sprite mirrored horizontally
 */
bool AnimatedSprite::horizontalMirror() const
{
    return m_horizontalMirror;
}

void AnimatedSprite::setHorizontalMirror(const bool &horizontalMirror)
{
    if (m_horizontalMirror == horizontalMirror)
        return;

    m_horizontalMirror = horizontalMirror;

    foreach (SpriteAnimation *animation, m_states.values())
        animation->setHorizontalMirror(m_horizontalMirror);

    emit horizontalMirrorChanged();
}

int AnimatedSprite::verticalFrameCount() const
{
    return m_verticalFrameCount;
}

void AnimatedSprite::setVerticalFrameCount(const int &verticalFrameCount)
{
    if (m_verticalFrameCount == verticalFrameCount)
        return;

    m_verticalFrameCount = verticalFrameCount;
    emit verticalFrameCountChanged();
}

int AnimatedSprite::horizontalFrameCount() const
{
    return m_horizontalFrameCount;
}

void AnimatedSprite::setHorizontalFrameCount(const int &horizontalFrameCount)
{
    if (m_horizontalFrameCount == horizontalFrameCount)
        return;

    m_horizontalFrameCount = horizontalFrameCount;
    emit horizontalFrameCountChanged();
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
        this->setSpriteState(m_game->gameState());
}

void AnimatedSprite::componentComplete()
{
    QQuickItem::componentComplete();

    if (!m_game) {
        QQmlApplicationEngine *engine = qobject_cast<QQmlApplicationEngine *>(qmlEngine(this));

        if (engine && !engine->rootObjects().isEmpty()) {
            m_game = engine->rootObjects().first()->findChild<Game *>();
            connect(m_game, SIGNAL(gameStateChanged()), this, SLOT(onGameStateChanged()));
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

    if (m_animation != QString() && m_states.contains(m_animation)) {
        SpriteAnimation *animationItem = m_states[m_animation];
        animationItem->setRunning(m_state == Bacon2D::Running);
        if (m_state == Bacon2D::Running || m_state == Bacon2D::Paused)
            animationItem->setVisible(true);
    }

    emit spriteStateChanged();

    if (!m_stateMachine)
        return;

    if (m_state == Bacon2D::Running && !m_stateMachine->isRunning())
        m_stateMachine->start();
    else if (m_state != Bacon2D::Running && m_stateMachine->isRunning())
        m_stateMachine->stop();
}

QPixmap AnimatedSprite::pixmap() const
{
    return m_pixmap;
}
