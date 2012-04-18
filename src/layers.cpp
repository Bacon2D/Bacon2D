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

#include "layers.h"
#include "staticlayer.h"

#if QT_VERSION >= 0x050000
void Layers::append_layer(QQmlListProperty<Layer> *list, Layer *layer)
#else
void Layers::append_layer(QDeclarativeListProperty<Layer> *list, Layer *layer)
#endif
{
    Layers *layers = qobject_cast<Layers *>(list->object);
    if (layers) {
        layer->setParentItem((QuasiDeclarativeItem *)layers->parent());
        layers->m_layers.append(layer);
    }
}

Layers::Layers(Scene *parent)
    : Entity(parent)
    , m_tileWidth(32)
    , m_tileHeight(32)
    , m_totalColumns(0)
    , m_drawType(Quasi::TiledDrawType)
    , m_xOffset(0)
    , m_yOffset(0)
{
    connect(this, SIGNAL(xOffsetChanged()), this, SLOT(changeXOffset()));
    connect(this, SIGNAL(yOffsetChanged()), this, SLOT(changeYOffset()));

    // control variables
    m_drawGrid = false;
    m_gridColor = Qt::red;
}

#if QT_VERSION >= 0x050000
QQmlListProperty<Layer> Layers::layers() const
{
    return QQmlListProperty<Layer>(const_cast<Layers *>(this), 0, &Layers::append_layer);
}
#else
QDeclarativeListProperty<Layer> Layers::layers() const
{
    return QDeclarativeListProperty<Layer>(const_cast<Layers *>(this), 0, &Layers::append_layer);
}
#endif

Layers::~Layers()
{
    m_layers.clear();
}

void Layers::setTileHeight(const int &tileHeight)
{
    if (m_tileHeight != tileHeight)
        m_tileHeight = tileHeight;
}

void Layers::setTileWidth(const int &tileWidth)
{
    if (m_tileWidth != tileWidth)
        m_tileWidth = tileWidth;
}

void Layers::setXOffset(const qreal &xOffset)
{
    if (m_xOffset != xOffset) {
        m_xOffset = xOffset;

        emit xOffsetChanged();
    }
}

void Layers::setYOffset(const qreal &yOffset)
{
    if (m_yOffset != yOffset) {
        m_yOffset = yOffset;

        emit yOffsetChanged();
    }
}

void Layers::setDrawGrid(bool draw)
{
    if (draw != m_drawGrid)
        m_drawGrid = draw;
}

void Layers::setGridColor(const QColor &color)
{
    if (color != m_gridColor)
        m_gridColor = color;
}

//! Stores the layer type
/*!
 * \param drawType can be Tiled (default) or Plane
 */
void Layers::setDrawType(Quasi::DrawType drawType)
{
    if (m_drawType != drawType)
        m_drawType = drawType;
}

//! Gets the layer type
/*!
 * \return Tiled or Plane according the layer draw type
 */
Quasi::DrawType Layers::drawType() const
{
    return m_drawType;
}

void Layers::update(const long &delta)
{
    Q_UNUSED(delta)

    foreach (Layer *layer, m_layers) {
        // If the layer isn't initialized, set their properties
        if (layer->boundingRect() == QRectF()) {
            layer->setDrawType(m_drawType);
            layer->setTileWidth(m_tileWidth);
            layer->setTileHeight(m_tileHeight);
            layer->setWidth(parentItem()->parentItem()->width()); // grandpa?
            layer->setHeight(parentItem()->parentItem()->height()); // grandpa!

            layer->setDrawGrid(m_drawGrid);
            layer->setGridColor(m_gridColor);

            layer->updateTiles();
        }

        layer->update();
    }
}

void Layers::changeXOffset()
{
    foreach (Layer *layer, m_layers) {
        layer->setX(m_xOffset);

        StaticLayer *sl = qobject_cast<StaticLayer *>(layer);
        if (sl)
            sl->moveX(m_xOffset);
    }
}

void Layers::changeYOffset()
{
    foreach (Layer *layer, m_layers) {
        layer->setY(m_xOffset);

        StaticLayer *sl = qobject_cast<StaticLayer *>(layer);
        if (sl)
            sl->moveY(m_yOffset);
    }
}
