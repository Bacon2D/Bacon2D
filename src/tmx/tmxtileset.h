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

#ifndef TMXTILESET
#define TMXTILESET

#include "tmxobject.h"
#include "tmxtile.h"

#include <libtiled/tileset.h>

class TMXMap;

class TMXTileset: public TMXObject
{
    Q_OBJECT

public:
    explicit TMXTileset(Tiled::Tileset *tileset, QObject *parent = 0)
        : TMXObject(tileset, parent), m_tileset(tileset) {}

    TMXTileset &operator=(const TMXTileset &other) { setTileset(other.tileset()); return *this; }

    Tiled::Tileset *tileset() const { return m_tileset; }
    void setTileset(Tiled::Tileset *tileset) { m_tileset = tileset; }

    int tileWidth() const { return m_tileset->tileWidth(); }
    int tileHeight() const { return m_tileset->tileHeight(); }

    int imageWidth() const { return m_tileset->imageWidth(); }
    int imageHeight() const { return m_tileset->imageHeight(); }

    QString imageSource() const { return m_tileset->imageSource(); }

    TMXTile tileAt(int id) const { return TMXTile(m_tileset->tileAt(id)); }

    const QList<TMXTile> &tiles() const {
        QList<TMXTile> allTiles;
        foreach(Tiled::Tile *tile, m_tileset->tiles())
            allTiles.append(TMXTile(tile));

        return allTiles;
    }

    QString name() const { return m_tileset->name(); }
    void setName(const QString &name) { m_tileset->setName(name); }

    QString fileName() const { return m_tileset->fileName(); }
    void setFileName(const QString &fileName) { m_tileset->setFileName(fileName); }

    int tileCount() const { return m_tileset->tileCount(); }
    int columnCount() const { return m_tileset->columnCount(); }

    bool loadFromImage(const QImage &image, const QString &fileName) { return m_tileset->loadFromImage(image, fileName); }
    bool loadFromImage(const QString &fileName) { return m_tileset->loadFromImage(fileName); }
private:
    Tiled::Tileset *m_tileset;
    TMXMap *m_map;
};

#endif // TMXTILESET

