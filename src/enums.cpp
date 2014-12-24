/**
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
 * @author Ken VanDine <ken@vandine.org>
 */

#include "enums.h"

/*!
  \qmltype State
  \inqmlmodule Bacon2D
  \brief This enum type is used to specify the current state of the game.
  \sa {http://doc.qt.io/qt-5/qt.html#ApplicationState-enum} {Qt.ApplicationState}
  \table
  \header
    \li State
    \li Description
  \row
    \li Bacon2D.Active
    \li Game is active and the currentScene is not running
  \row
    \li Bacon2D.Inactive
    \li Game is inactive
  \row
    \li Bacon2D.Running
    \li Game is active and the currentScene is running
  \row
    \li Bacon2D.Paused
    \li Game is paused by user request.
  \row
    \li Bacon2D.Suspended
    \li Game is suspended, usually means the platform has stopped the process or the game is no longer focused.
  \endtable
*/

Bacon2D::Bacon2D(QObject *parent)
    : QObject(parent)
{
}
