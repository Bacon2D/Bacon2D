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

#ifndef TMXMAP_H
#define TMXMAP_H

#include "tmximagelayer.h"
#include "tmxobject.h"
#include "tmxobjectlayer.h"
#include "tmxtilelayer.h"
#include "tmxlayer.h"
#include "tmxobjectgroup.h"
#include "tmxtileset.h"

#include <libtiled/map.h>
#include <libtiled/objectgroup.h>

class TMXMap : public TMXObject
{
    Q_OBJECT

public:
    explicit TMXMap(Tiled::Map *tiledMap, QObject *parent = 0)
        : TMXObject(tiledMap, parent), m_tiledMap(tiledMap) {}

    Tiled::Map *tiledMap() const { return m_tiledMap; }
    void setTiledMap(Tiled::Map *tiledMap) { m_tiledMap = tiledMap; }

    int width() const { return m_tiledMap->width(); }
    void setWidth(int width) { m_tiledMap->setWidth(width); }

    int height() const { return m_tiledMap->height(); }
    void setHeight(int height) { m_tiledMap->setHeight(height); }

    int tileWidth() const { return m_tiledMap->tileWidth(); }
    int tileHeight() const { return m_tiledMap->tileHeight(); }
    QSize tileSize() const { return m_tiledMap->tileSize(); }

    QList<TMXLayer> layers() const {
        QList<TMXLayer> allLayers;
        foreach(Tiled::Layer *layer, m_tiledMap->layers())
            allLayers.append(TMXLayer(layer));

        return allLayers;
    }

    QList<TMXObjectGroup> objectGroups() const {
        QList<TMXObjectGroup> allObjectGroups;
        foreach(Tiled::ObjectGroup *objectGroup, m_tiledMap->objectGroups())
            allObjectGroups.append(TMXObjectGroup(objectGroup));

        return allObjectGroups;
    }

    QList<TMXTileLayer> tileLayers() const {
        QList<TMXTileLayer> allTileLayers;
        foreach(Tiled::TileLayer *tileLayer, m_tiledMap->tileLayers())
            allTileLayers.append(TMXTileLayer(tileLayer));

        return allTileLayers;
    }

    QList<TMXTileset> tilesets() const {
        QList<TMXTileset> allTilesets;

        foreach(Tiled::SharedTileset tileset, m_tiledMap->tilesets())
            allTilesets.append(TMXTileset(tileset.data()));

        return allTilesets;
    }

private:
    Tiled::Map *m_tiledMap;
    QList<TMXTileset> m_tilesets;
};

#endif // TMXMAP_H
