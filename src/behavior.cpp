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

#include "behavior.h"

/*!
  \qmltype Behavior
  \inqmlmodule Bacon2D
  \brief Provides an easy way to add custom behaviors to the game, like 
         artificial intelligence or other game logic
*/
Behavior::Behavior(QObject *parent)
    : QObject(parent)
    , m_target(0)
    , m_delta(0)
{
}

QQuickItem *Behavior::target() const
{
    return m_target;
}

void Behavior::setTarget(QQuickItem *target)
{
    m_target = target;
}

/*!
  \qmlproperty int Behavior::delta
  \brief This property holds the delta in milliseconds since the last update tick.
*/

int Behavior::delta() const
{
    return m_delta;
}

void Behavior::setDelta(int delta)
{
    m_delta = delta;
}
