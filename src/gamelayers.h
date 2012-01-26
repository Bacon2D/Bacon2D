#ifndef _GAMELAYERS_H_
#define _GAMELAYERS_H_

#include <QList>
#include <QString>
#include <QtQuick/QQuickPaintedItem>

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
