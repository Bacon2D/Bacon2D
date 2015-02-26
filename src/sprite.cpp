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

#include "scene.h"
#include "sprite.h"
#include "spritesheet.h"
#include "spriteanimation.h"
#include "animationchangeevent.h"
#include "animationtransition.h"

void Sprite::append_animation(QQmlListProperty<SpriteAnimation> *list, SpriteAnimation *animation)
{
    Sprite *spriteItem = qobject_cast<Sprite *>(list->object);

    if (!spriteItem)
        return;

    spriteItem->m_states.insert(animation->name(), animation);
    animation->spriteSheet()->setParentItem(spriteItem);
}

/*!
  \qmltype Sprite
  \inqmlmodule Bacon2D
  \inherits Item
  \brief A Sprite, providing state based
   management of multiple SpriteAnimation animations.
 */
Sprite::Sprite(QQuickItem *parent)
    : QQuickItem(parent)
    , m_entity(0)
    , m_game(0)
    , m_stateMachine(0)
    , m_stateGroup(0)
    , m_verticalMirror(false)
    , m_horizontalMirror(false)
    , m_state(Bacon2D::Running)
{
}

QQmlListProperty<SpriteAnimation> Sprite::animations() const
{
    return QQmlListProperty<SpriteAnimation>(const_cast<Sprite *>(this), 0, &Sprite::append_animation, 0, 0, 0);
}

/*!
 * \qmlproperty string Sprite::animation
 * \brief The current SpriteAnimation state of the Sprite as a string
 */
QString Sprite::animation() const
{
    return m_animation;
}

void Sprite::setAnimation(const QString &animation, const bool &force)
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
        if (m_animation != QString() && m_states.contains(m_animation)) {
            SpriteAnimation *animationItem = m_states[m_animation];
            animationItem->setRunning(false);
            animationItem->setVisible(false);
        }
        m_animation = animation;

        if (!m_stateMachine)
            initializeMachine();

        if (m_stateMachine && m_stateMachine->isRunning())
            m_stateMachine->postEvent(new AnimationChangeEvent(m_animation));

        emit animationChanged();
    }
}

void Sprite::initializeMachine()
{
    m_stateMachine= new QStateMachine;
    m_stateGroup = new QState(QState::ParallelStates);

    SpriteAnimation *animation;
    foreach (animation, m_states.values()) {
        AnimationTransition *transition = new AnimationTransition(animation);
        animation->setParent(m_stateGroup);
        animation->addTransition(transition);

        if (width() == 0 || height() == 0) {
            setWidth(animation->spriteSheet()->width());
            setHeight(animation->spriteSheet()->height());
        }
    }

    m_stateMachine->addState(m_stateGroup);
    m_stateMachine->setInitialState(m_stateGroup);

    connect(m_stateMachine, SIGNAL(started()), this, SLOT(initializeAnimation()));

    m_stateMachine->start();
}

void Sprite::initializeAnimation()
{
    if (m_animation != QString())
        setAnimation(m_animation, (m_state == Bacon2D::Running));
}

/*!
 * \qmlproperty bool Sprite::verticalMirror
 * \brief Shows the Sprite mirrored vertically (upside down)
 */
bool Sprite::verticalMirror() const
{
    return m_verticalMirror;
}

void Sprite::setVerticalMirror(const bool &verticalMirror)
{
    if (m_verticalMirror == verticalMirror)
        return;

    m_verticalMirror = verticalMirror;

    foreach (SpriteAnimation *animation, m_states.values())
        animation->setVerticalMirror(m_verticalMirror);

    emit verticalMirrorChanged();
}

/*!
 * \qmlproperty bool Sprite::horizontalMirror
 * \brief Shows the Sprite mirrored horizontally
 */
bool Sprite::horizontalMirror() const
{
    return m_horizontalMirror;
}

void Sprite::setHorizontalMirror(const bool &horizontalMirror)
{
    if (m_horizontalMirror == horizontalMirror)
        return;

    m_horizontalMirror = horizontalMirror;

    foreach (SpriteAnimation *animation, m_states.values())
        animation->setHorizontalMirror(m_horizontalMirror);

    emit horizontalMirrorChanged();
}

Entity *Sprite::entity() const
{
    return m_entity;
}

void Sprite::setEntity(Entity *entity)
{
    if (m_entity == entity)
        return;

    m_entity = entity;
    if (!m_game) {
        m_game = m_entity->scene()->game();
        connect(m_game, SIGNAL(gameStateChanged()), this, SLOT(onGameStateChanged()));
    }
    emit entityChanged();
}

void Sprite::onGameStateChanged()
{
    if (m_state != Bacon2D::Inactive)
        this->setSpriteState(m_game->gameState());
}

/*!
  \qmlproperty Bacon2D.State Sprite::spriteState
  \brief This property holds the current spriteState.
*/
void Sprite::setSpriteState(const Bacon2D::State &state)
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
