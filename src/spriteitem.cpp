/**
 * Copyright (C) 2012 by INdT
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * @author Rodrigo Goncalves de Oliveira <rodrigo.goncalves@openbossa.org>
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

#include "spriteitem.h"

#include "gamescene.h"
#include "spritesheet.h"
#include "spriteanimationitem.h"
#include "animationchangeevent.h"
#include "animationtransition.h"

#if QT_VERSION >= 0x050000
void SpriteItem::append_animation(QQmlListProperty<SpriteAnimationItem> *list, SpriteAnimationItem *animation)
#else
void SpriteItem::append_animation(QDeclarativeListProperty<SpriteAnimationItem> *list, SpriteAnimationItem *animation)
#endif
{
    SpriteItem *spriteItem = qobject_cast<SpriteItem *>(list->object);

    if (spriteItem) {
        spriteItem->m_states.insert(animation->name(), animation);
        animation->spriteSheet()->setParentItem(spriteItem);
    }
}

SpriteItem::SpriteItem(GameScene *parent)
    : GameItem(parent)
    , m_stateMachine(0)
    , m_stateGroup(0)
    , m_verticalMirror(false)
    , m_horizontalMirror(false)
{
}

#if QT_VERSION >= 0x050000
QQmlListProperty<SpriteAnimationItem> SpriteItem::animations() const
{
    return QQmlListProperty<SpriteAnimationItem>(const_cast<SpriteItem *>(this), 0, &SpriteItem::append_animation);
}
#else
QDeclarativeListProperty<SpriteAnimationItem> SpriteItem::animations() const
{
    return QDeclarativeListProperty<SpriteAnimationItem>(const_cast<SpriteItem *>(this), 0, &SpriteItem::append_animation);
}
#endif

QString SpriteItem::animation() const
{
    return m_animation;
}

void SpriteItem::setAnimation(const QString &animation, const bool &force)
{
    if (force || (m_animation != animation)) {
        if (m_animation != QString()) {
            SpriteAnimationItem *animationItem = m_states[m_animation];
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

void SpriteItem::initializeMachine()
{
    m_stateMachine= new QStateMachine;
    m_stateGroup = new QState(QState::ParallelStates);

    SpriteAnimationItem *animation;
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

void SpriteItem::initializeAnimation()
{
    if (m_animation != QString())
        setAnimation(m_animation, true);
}

bool SpriteItem::verticalMirror() const
{
    return m_verticalMirror;
}

void SpriteItem::setVerticalMirror(const bool &verticalMirror)
{
    if (m_verticalMirror != verticalMirror) {
        m_verticalMirror = verticalMirror;

        foreach (SpriteAnimationItem *animation, m_states.values())
            animation->setVerticalMirror(m_verticalMirror);

        emit verticalMirrorChanged();
    }
}

bool SpriteItem::horizontalMirror() const
{
    return m_horizontalMirror;
}

void SpriteItem::setHorizontalMirror(const bool &horizontalMirror)
{
    if (m_horizontalMirror != horizontalMirror) {
        m_horizontalMirror = horizontalMirror;

        foreach (SpriteAnimationItem *animation, m_states.values())
            animation->setHorizontalMirror(m_horizontalMirror);

        emit horizontalMirrorChanged();
    }
}
