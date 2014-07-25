/**
 * Copyright (C) 2012 by INdT
 * Copyright (C) 2014 Bacon2D Project
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
