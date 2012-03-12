#include "gamelayers.h"

void GameLayers::append_layer(QDeclarativeListProperty<Layer> *list, Layer *layer)
{
    GameLayers *layers = qobject_cast<GameLayers *>(list->object);
    if (layers) {
        layer->setParentItem((QQuickItem*)layers->parent());
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

QDeclarativeListProperty<Layer> GameLayers::layers() const
{
    return QDeclarativeListProperty<Layer>(const_cast<GameLayers *>(this), 0, &GameLayers::append_layer);
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
