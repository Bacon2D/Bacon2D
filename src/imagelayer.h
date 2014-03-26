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

#ifndef _IMAGELAYER_H_
#define _IMAGELAYER_H_

#include "layer.h"

#include <QtCore/QtGlobal>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>

class ImageLayer : public Layer
{
    Q_OBJECT

    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)

    // From Layers
    Q_PROPERTY(int tileHeight READ tileHeight WRITE setTileHeight)
    Q_PROPERTY(int tileWidth READ tileWidth WRITE setTileWidth)

    Q_PROPERTY(Quasi::DrawType drawType READ drawType WRITE setDrawType)
    Q_PROPERTY(bool drawGrid READ drawGrid WRITE setDrawGrid)
    Q_PROPERTY(QColor gridColor READ gridColor WRITE setGridColor)

public:
    ImageLayer(Layer *parent = 0);
    ~ImageLayer();

    void setSource(const QString &source);
    QString source() const;

    void setDrawType(Quasi::DrawType drawType);
    Quasi::DrawType drawType() const;

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

    void moveX(const qreal &x);
    void moveY(const qreal &y);

    void paint(QPainter *painter);

signals:
    void tilesChanged();
    void sourceChanged();

protected:
    void drawPixmap();
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

    QImage *m_currentImage;

    int m_tileWidth;
    int m_tileHeight;
    int m_numColumns;
    int m_numRows;
    int m_totalColumns;
    int m_totalRows;

protected slots:
    void onHorizontalDirectionChanged();

protected:
    void componentComplete();

private:
    QPixmap generatePartialPixmap(int startPoint, int size);
    void generateOffsets();
    void updateHorizontalStep();
    void updateTiles();

    QList<Offsets::OffsetsList> m_offsets;
    QList<QPixmap> m_pixmaps;

    QString m_source;
    Quasi::DrawType m_drawType;

    const float m_areaToDraw;
    int m_columnOffset;
    int m_latestPoint;

    bool m_drawGrid;
    QColor m_gridColor;

    qreal m_globalXPos;
    qreal m_globalYPos;
    qreal m_localXPos;
    qreal m_localYPos;
    qreal m_currentHorizontalStep;

    bool m_initialized;
};

#endif /* _IMAGELAYER_H_ */
