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

#ifndef _ENUMS_H_
#define _ENUMS_H_

#include <QObject>

class Bacon2D : public QObject
{
    Q_OBJECT
public:
    Bacon2D(QObject *parent = 0);

    enum State {
        Active = 0,
        Inactive = 1,
        Running = 2,
        Paused = 3,
        Suspended = 4
    }; Q_ENUM(State)

    enum FillMode {
        Stretch,
        PreserveAspectFit,
        PreserveAspectCrop,
        Tile,
        TileVertically,
        TileHorizontally,
        Pad
    }; Q_ENUM(FillMode)
};

#endif /* _ENUMS_H_ */
