/**
 * The MIT License (MIT)
 *
 * Copyright (C) 2012 by INdT
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

#include "animationtransition.h"

#include "animationchangeevent.h"
#include "spriteanimation.h"
#include "animatedsprite.h"
#include "spritestrip.h"

#include <QDebug>

AnimationTransition::AnimationTransition(SpriteAnimation *spriteAnimation)
    : QAbstractTransition()
    , m_spriteAnimation(spriteAnimation)
{
}


bool AnimationTransition::eventTest(QEvent *e)
{
    if (e->type() != QEvent::Type(QEvent::User+1))
        return false;

    AnimationChangeEvent *ae = static_cast<AnimationChangeEvent*>(e);
    return (m_spriteAnimation->name() == ae->animationName);
}

void AnimationTransition::onTransition(QEvent *e)
{
    Q_UNUSED(e)

    if (m_spriteAnimation->previousAnimation())
        m_spriteAnimation->previousAnimation()->setRunning(false);

    m_spriteAnimation->setRunning(true);
}
