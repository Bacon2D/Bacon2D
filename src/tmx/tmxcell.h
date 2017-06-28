/**
 * The MIT License (MIT)
 *
 * Copyright (C) 2017 Bacon2D Project
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
 */

#ifndef TMXCELL
#define TMXCELL

#include "tmxlayer.h"
#include "tmxcell.h"
#include "tmxtile.h"

#include <libtiled/tilelayer.h>
#include <QDebug>

class TMXCell : public QObject
{
    Q_OBJECT
public:
    explicit TMXCell(const Tiled::Cell &cell, QObject *parent = 0)   : QObject(parent), m_cell(cell.tile()){
        m_cell.setFlippedAntiDiagonally(cell.flippedAntiDiagonally());
        m_cell.setFlippedHorizontally(cell.flippedHorizontally());
        m_cell.setFlippedVertically(cell.flippedVertically());
    }
    TMXCell(const TMXCell &other) { setCell(other.cell()); }
    TMXCell &operator=(const TMXCell &other) { setCell(other.cell()); return *this; }

    Tiled::Cell cell() const { return m_cell; }
    void setCell(const Tiled::Cell &cell) { m_cell = cell; }

    bool isEmpty() const { return m_cell.isEmpty(); }
    
    bool flippedHorizontally() const { return m_cell.flippedHorizontally(); }
    bool flippedVertically() const { return m_cell.flippedVertically(); }
    bool flippedAntiDiagonally() const { return m_cell.flippedAntiDiagonally(); }

    TMXTile tile() const { return TMXTile(m_cell.tile()); }
private:
    Tiled::Cell m_cell;
};

#endif // TMXCELL

