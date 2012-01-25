#ifndef _GAMEBASEBACKGROUND_H_
#define _GAMEBASEBACKGROUND_H_

#include <QList>
#include <QString>
#include <QtQuick/QQuickPaintedItem>

#include "layer.h"

class GameBaseBackground : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(QString source READ source WRITE setSource)

public:
    GameBaseBackground(QQuickItem *parent = 0);
    virtual ~GameBaseBackground();

    int tileHeight() const { return m_tileHeight; }
    void setTileHeight(const int &value);

    int tileWidth() const { return m_tileWidth; }
    void setTileWidth(const int &value);

    QString source() const { return m_source; };
    void setSource(const QString &source);

    virtual void paint(QPainter *painter) { Q_UNUSED(painter); };

public slots:
    virtual void updateTiles() {};

signals:
    void tilesChanged();

protected:
    int m_numColumns;
    int m_numRows;
    int m_tileWidth;
    int m_tileHeight;
    int m_totalColumns;
    int m_totalRows;

    QString m_source;
    Layer::LayerList m_layers;

    QPixmap *m_currentPixmap;

    // control variables
    bool m_drawGrid;
    QColor m_gridColor;
};

#endif /* _GAMEBASEBACKGROUND_H_ */
