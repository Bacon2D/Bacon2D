/**
 * The MIT License (MIT)
 *
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
