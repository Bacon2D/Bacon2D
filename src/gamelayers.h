/**
 * Copyright (C) 2012 by INdT
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

#ifndef _GAMELAYERS_H_
#define _GAMELAYERS_H_

#include <QList>
#include <QString>

#include "layer.h"
#include "enums.h"
#include "gameitem.h"

class GameLayers : public GameItem
{
    Q_OBJECT

    Q_PROPERTY(QDeclarativeListProperty<Layer> layers READ layers)
    Q_PROPERTY(Quasi::DrawType drawType READ drawType WRITE setDrawType)
    Q_PROPERTY(int tileHeight READ tileHeight WRITE setTileHeight)
    Q_PROPERTY(int tileWidth READ tileWidth WRITE setTileWidth)

    Q_PROPERTY(bool drawGrid READ drawGrid WRITE setDrawGrid)
    Q_PROPERTY(QColor gridColor READ gridColor WRITE setGridColor)

public:
    GameLayers(GameScene *parent = 0);
    virtual ~GameLayers();

    QDeclarativeListProperty<Layer> layers() const;

    void setDrawType(Quasi::DrawType drawType);
    Quasi::DrawType drawType() const;

    int tileHeight() const { return m_tileHeight; }
    void setTileHeight(const int &value);

    int tileWidth() const { return m_tileWidth; }
    void setTileWidth(const int &value);

    bool drawGrid() const { return m_drawGrid; }
    void setDrawGrid(bool draw);

    QColor gridColor() const { return m_gridColor; }
    void setGridColor(const QColor &color);

    void update(const long &delta);

private:
    static void append_layer(QDeclarativeListProperty<Layer> *list, Layer *layer);

    int m_tileWidth;
    int m_tileHeight;
    int m_totalColumns;
    int m_totalRows;
    Quasi::DrawType m_drawType;

    Layer::LayerList m_layers;

    bool m_drawGrid;
    QColor m_gridColor;
};

#endif /* _GAMELAYERS_H_ */
