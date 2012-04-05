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

#ifndef _LAYER_H_
#define _LAYER_H_

#include "enums.h"
#include "gameitem.h"
#include "quasipainteditem.h"

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtGui/QPixmap>

class Offsets {
public:
    typedef QList<Offsets> OffsetsList;

    Offsets() { m_point = m_size = 0; }
    Offsets(int point, int size)
    {
        m_point = point;
        m_size = size;
    }
    ~Offsets() {}

    int point() const { return m_point; }
    void setPoint(int point)
    {
        if (point != m_point)
            m_point = point;
    }

    int size() const { return m_size; }
    void setSize(int size)
    {
        if (size != m_size)
            m_size = size;
    }
    bool operator==(const Offsets &other) const {
        return ((this->point() == other.point())
                && (this->size() == other.size()));
    }

private:
    int m_point;
    int m_size;
};

//! A layer class
class Layer: public QuasiPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(QString source READ source WRITE setSource)
    Q_PROPERTY(qreal factor READ factor WRITE setFactor)
    Q_PROPERTY(Quasi::Ordering order READ order WRITE setOrder)
    Q_PROPERTY(Quasi::LayerType layerType READ layerType WRITE setLayerType NOTIFY layerTypeChanged)
    Q_PROPERTY(Quasi::LayerDirection direction READ direction WRITE setDirection NOTIFY directionChanged)

public:
    typedef QList<Layer *> LayerList; //! A layer list based on QList

    Layer(QuasiDeclarativeItem *parent = 0);
    ~Layer();

    void setSource(const QString &source);
    QString source() const;

    void setDrawType(Quasi::DrawType drawType);
    Quasi::DrawType drawType() const;

    void setFactor(qreal factor);
    qreal factor() const;

    void setOrder(Quasi::Ordering order);
    Quasi::Ordering order() const;

    Quasi::LayerType layerType() const { return m_type; };
    void setLayerType(const Quasi::LayerType &type);

    Quasi::LayerDirection direction() const { return m_direction; };
    void setDirection(const Quasi::LayerDirection &direction);

    int tileHeight() const { return m_tileHeight; }
    void setTileHeight(const int &value);

    int tileWidth() const { return m_tileWidth; }
    void setTileWidth(const int &value);

    int addTile(const QPixmap &pix);
    QPixmap getTile(int pos) const;

    bool drawGrid() const { return m_drawGrid; }
    void setDrawGrid(bool draw);

    QColor gridColor() const { return m_gridColor; }
    void setGridColor(const QColor &color);

    int count() const;

    void drawPixmap();

public slots:
    virtual void updateTiles();

signals:
    void tilesChanged();
    void directionChanged();
    void layerTypeChanged();

protected:
    QImage *m_currentImage;
    Quasi::LayerDirection m_direction;

    int m_tileWidth;
    int m_tileHeight;
    int m_numColumns;
    int m_numRows;
    int m_totalColumns;
    int m_totalRows;

    qreal m_factor;

private:
    QPixmap generatePartialPixmap(int startPoint, int size);
    void generateOffsets();

    QList<Offsets::OffsetsList> m_offsets;
    QList<QPixmap> m_pixmaps;

    QString m_source;
    Quasi::DrawType m_drawType;
    Quasi::LayerType m_type;

    const float m_areaToDraw;
    int m_columnOffset;
    int m_latestPoint;

    bool m_drawGrid;
    QColor m_gridColor;
};

#endif /* _LAYER */
