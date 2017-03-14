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
