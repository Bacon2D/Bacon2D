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

#ifndef _LAYERS_H_
#define _LAYERS_H_

#include "enums.h"
#include "entity.h"
#include "layer.h"

#include <QtCore/QList>
#include <QtCore/QString>

class Layers : public Entity
{
    Q_OBJECT

#if QT_VERSION >= 0x050000
    Q_PROPERTY(QQmlListProperty<Layer> layers READ layers)
#else
    Q_PROPERTY(QDeclarativeListProperty<Layer> layers READ layers)
#endif
    Q_PROPERTY(Quasi::DrawType drawType READ drawType WRITE setDrawType)
    Q_PROPERTY(int tileHeight READ tileHeight WRITE setTileHeight)
    Q_PROPERTY(int tileWidth READ tileWidth WRITE setTileWidth)
    Q_PROPERTY(qreal xOffset READ xOffset WRITE setXOffset NOTIFY xOffsetChanged)
    Q_PROPERTY(qreal yOffset READ yOffset WRITE setYOffset NOTIFY yOffsetChanged)

    Q_PROPERTY(bool drawGrid READ drawGrid WRITE setDrawGrid)
    Q_PROPERTY(QColor gridColor READ gridColor WRITE setGridColor)

public:
    Layers(Scene *parent = 0);
    ~Layers();

#if QT_VERSION >= 0x050000
    QQmlListProperty<Layer> layers() const;
#else
    QDeclarativeListProperty<Layer> layers() const;
#endif

    void setDrawType(Quasi::DrawType drawType);
    Quasi::DrawType drawType() const;

    int tileHeight() const { return m_tileHeight; }
    void setTileHeight(const int &tileHeight);

    int tileWidth() const { return m_tileWidth; }
    void setTileWidth(const int &tileWidth);

    qreal xOffset() const { return m_xOffset; }
    void setXOffset(const qreal &xOffset);

    qreal yOffset() const { return m_yOffset; }
    void setYOffset(const qreal &yOffset);

    bool drawGrid() const { return m_drawGrid; }
    void setDrawGrid(bool draw);

    QColor gridColor() const { return m_gridColor; }
    void setGridColor(const QColor &color);

    void update(const int &delta);

signals:
    void xOffsetChanged();
    void yOffsetChanged();

public slots:
    void changeXOffset();
    void changeYOffset();

private:

#if QT_VERSION >= 0x050000
    static void append_layer(QQmlListProperty<Layer> *list, Layer *layer);
#else
    static void append_layer(QDeclarativeListProperty<Layer> *list, Layer *layer);
#endif

    int m_tileWidth;
    int m_tileHeight;
    int m_totalColumns;
    int m_totalRows;
    Quasi::DrawType m_drawType;
    Layer::LayerList m_layers;

    qreal m_xOffset;
    qreal m_yOffset;

    bool m_drawGrid;
    QColor m_gridColor;
};

#endif /* _LAYERS_H_ */
