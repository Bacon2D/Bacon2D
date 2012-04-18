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

#include "animationtransition.h"

#include "animationchangeevent.h"
#include "spriteanimation.h"
#include "sprite.h"
#include "spritesheet.h"

AnimationTransition::AnimationTransition(SpriteAnimation *spriteAnimationItem)
    : QAbstractTransition()
    , m_spriteAnimationItem(spriteAnimationItem)
{
}


bool AnimationTransition::eventTest(QEvent *e)
{
    if (e->type() != QEvent::Type(QEvent::User+1))
        return false;

    AnimationChangeEvent *ae = static_cast<AnimationChangeEvent*>(e);
    return (m_spriteAnimationItem->name() == ae->animation);
}

void AnimationTransition::onTransition(QEvent *e)
{
    Q_UNUSED(e)

    m_spriteAnimationItem->spriteSheet()->setVisible(true);
    m_spriteAnimationItem->setRunning(true);
}
