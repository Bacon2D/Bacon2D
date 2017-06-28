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

#ifndef TMXTILE
#define TMXTILE

#include "tmxobject.h"

#include <libtiled/tile.h>

class TMXMap;

class TMXTile: public TMXObject
{
    Q_OBJECT

public:
    explicit TMXTile(Tiled::Tile *tile, QObject *parent = 0)
        : TMXObject(tile, parent), m_tile(tile) {}

    TMXTile &operator=(const TMXTile &other) { setTile(other.tile()); return *this; }

    Tiled::Tile *tile() const { return m_tile; }
    void setTile(Tiled::Tile *tile) { m_tile = tile; }

    const QPixmap &image() const { return m_tile->image(); }
    void setImage(const QPixmap &image) { m_tile->setImage(image); }

    QString imageSource() const { return m_tile->imageSource(); }
    void setImageSource(const QString &imageSource) { m_tile->setImageSource(imageSource); }

    int width() const { return m_tile->width(); }
    int height() const { return m_tile->height(); }
    QSize size() const { return m_tile->size(); }

    QPoint offset() const {return m_tile->offset(); }

    int id() const { return m_tile->id(); }
private:
    Tiled::Tile *m_tile;
    TMXMap *m_map;
};

#endif // TMXTILE

