#ifndef _LAYER_H_
#define _LAYER_H_

#include <QList>
#include <QPixmap>
#include <QString>
#include <QtQuick/QQuickPaintedItem>

#include "gameitem.h"
#include "enums.h"

//! A layer class
class Layer: public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(QString source READ source WRITE setSource)
    Q_PROPERTY(qreal factor READ factor WRITE setFactor)
    Q_PROPERTY(Quasi::Ordering order READ order WRITE setOrder)
    Q_PROPERTY(Quasi::LayerType type READ type WRITE setType NOTIFY typeChanged)

public:
    typedef QList<Layer *> LayerList; //! A layer list based on QList

    Layer(QQuickItem *parent = 0);
    ~Layer();

    void setSource(const QString &source);
    QString source() const;

    void setDrawType(Quasi::DrawType drawType);
    Quasi::DrawType drawType() const;

    void setFactor(qreal factor);
    qreal factor() const;

    void setOrder(Quasi::Ordering order);
    Quasi::Ordering order() const;

    Quasi::LayerType type() const { return m_type; };
    void setType(const Quasi::LayerType &type);

    int tileHeight() const { return m_tileHeight; }
    void setTileHeight(const int &value);

    int tileWidth() const { return m_tileWidth; }
    void setTileWidth(const int &value);

    int addTile(const QPixmap &pix);
    QPixmap getTile(int pos) const;

    int setPixmap(const QPixmap &pix);
    QPixmap getPixmap() const;

    bool drawGrid() const { return m_drawGrid; }
    void setDrawGrid(bool draw);

    QColor gridColor() const { return m_gridColor; }
    void setGridColor(const QColor &color);

    int count() const;

    void drawPixmap();
    virtual void paint(QPainter *painter) { Q_UNUSED(painter) };

public slots:
    virtual void updateTiles();

signals:
    void tilesChanged();
    void typeChanged();

protected:
    QPixmap *m_currentPixmap;

    int m_tileWidth;
    int m_tileHeight;
    int m_numColumns;
    int m_numRows;
    int m_totalColumns;
    int m_totalRows;

    qreal m_factor;

private:
    QList<QPixmap> m_pixmaps; // can be a list of tiles or a single image
    QList<QPixmap> m_mirroredTiles;

    QString m_source;
    Quasi::DrawType m_drawType;
    Quasi::LayerType m_type;

    const float m_areaToDraw;
    int m_columnOffset;
    bool m_drawingMirrored;
    bool m_shouldMirror;

    bool m_drawGrid;
    QColor m_gridColor;
};

#endif /* _LAYER */
