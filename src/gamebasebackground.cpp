#include <QImage>
#include <QPixmapCache>

#include "gamebasebackground.h"

GameBaseBackground::GameBaseBackground(QQuickItem *parent)
    : QQuickPaintedItem(parent)
      , m_numColumns(0)
      , m_numRows(0)
      , m_tileWidth(0)
      , m_tileHeight(0)
      , m_totalColumns(0)
{
    setZ(0);

    connect(this, SIGNAL(widthChanged()), this, SLOT(updateTiles()));
    connect(this, SIGNAL(heightChanged()), this, SLOT(updateTiles()));

    // control variables
    m_drawGrid = false;
    m_gridColor = Qt::red;
}

GameBaseBackground::~GameBaseBackground()
{
    QPixmapCache::clear();
}

void GameBaseBackground::setTileHeight(const int value)
{
    if (value != m_tileHeight){
        m_tileHeight = value;

        if (m_tileWidth != 0 && m_tileHeight != 0 && m_source != QString()){
            updateTiles();
            emit tilesChanged();
        }
    }
}

void GameBaseBackground::setTileWidth(const int value)
{
    if (value != m_tileWidth){
        m_tileWidth = value;

        if (m_tileWidth != 0 && m_tileHeight != 0 && m_source != QString()){
            updateTiles();
            emit tilesChanged();
        }
    }
}

void GameBaseBackground::setSource(const QString &source)
{
    if (source != m_source){
        m_source = source;

        if (m_numColumns != 0 && m_numRows != 0 && m_source != QString()){
            updateTiles();
            emit tilesChanged();
        }
    }
}
