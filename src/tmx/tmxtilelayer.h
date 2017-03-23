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

#ifndef TMXTILELAYER_H
#define TMXTILELAYER_H

#include "tmxlayer.h"
#include "tmxcell.h"

#include <libtiled/tilelayer.h>
#include <libtiled/map.h>

class TMXLayer;

class TMXTileLayer : public TMXLayer
{
    Q_OBJECT
public:
    explicit TMXTileLayer(Tiled::TileLayer *tileLayer, QObject *parent = 0)
        : TMXLayer(tileLayer, parent), m_tileLayer(tileLayer) {}
    explicit TMXTileLayer(const TMXLayer &layer, QObject *parent = 0)
        : TMXLayer(layer.layer()->asTileLayer(), parent), m_tileLayer(layer.layer()->asTileLayer()) {}

    bool isNull() const { return m_tileLayer == 0; }

    Tiled::TileLayer *tileLayer() const { return m_tileLayer; }
    void setTileLayer(Tiled::TileLayer *tileLayer) { m_tileLayer = tileLayer; }

    TMXCell cellAt(const QPoint &point) const {m_tileLayer->cellAt(point.x(), point.y()); }
    TMXCell cellAt(int x, int y) const {m_tileLayer->cellAt(x, y); }

    QList<TMXCell> cells() const
    {
        QList<TMXCell> allCells;
        for(int x = 0; x < m_tileLayer->width(); ++x) {
            for(int y = 0; y < m_tileLayer->height(); ++y)
                allCells.append(TMXCell(m_tileLayer->cellAt(x, y)));
        }

        return allCells;
    }

private:
    Tiled::TileLayer *m_tileLayer;
};

#endif // TMXTILELAYER_H
