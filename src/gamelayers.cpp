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

#include "gamelayers.h"

void GameLayers::append_layer(QQmlListProperty<Layer> *list, Layer *layer)
{
    GameLayers *layers = qobject_cast<GameLayers *>(list->object);
    if (layers) {
        layer->setParentItem((QuasiDeclarativeItem *)layers->parent());
        layers->m_layers.append(layer);
    }
}

GameLayers::GameLayers(GameScene *parent)
    : GameItem(parent)
      , m_tileWidth(32)
      , m_tileHeight(32)
      , m_totalColumns(0)
      , m_drawType(Quasi::TiledDrawType)
{
    // control variables
    m_drawGrid = false;
    m_gridColor = Qt::red;
}

QQmlListProperty<Layer> GameLayers::layers() const
{
    return QQmlListProperty<Layer>(const_cast<GameLayers *>(this), 0, &GameLayers::append_layer);
}

GameLayers::~GameLayers()
{
    m_layers.clear();
}

void GameLayers::setTileHeight(const int &value)
{
    if (value != m_tileHeight)
        m_tileHeight = value;
}

void GameLayers::setTileWidth(const int &value)
{
    if (value != m_tileWidth)
        m_tileWidth = value;
}

void GameLayers::setDrawGrid(bool draw)
{
    if (draw != m_drawGrid)
        m_drawGrid = draw;
}

void GameLayers::setGridColor(const QColor &color)
{
    if (color != m_gridColor)
        m_gridColor = color;
}

//! Stores the layer type
/*!
 * \param drawType can be Tiled (default) or Plane
 */
void GameLayers::setDrawType(Quasi::DrawType drawType)
{
    if (m_drawType != drawType)
        m_drawType = drawType;
}

//! Gets the layer type
/*!
 * \return Tiled or Plane according the layer draw type
 */
Quasi::DrawType GameLayers::drawType() const
{
    return m_drawType;
}

void GameLayers::update(const long &delta)
{
    foreach (Layer *layer, m_layers) {
        // If the layer isn't initialized, set their properties
        if (layer->boundingRect() == QRectF()) {
            layer->setDrawType(m_drawType);
            layer->setTileWidth(m_tileWidth);
            layer->setTileHeight(m_tileHeight);
            layer->setWidth(width());
            layer->setHeight(height());

            layer->setDrawGrid(m_drawGrid);
            layer->setGridColor(m_gridColor);

            layer->updateTiles();
        }

        layer->update();
    }
}
