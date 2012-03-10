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

#include <QDebug>
#include <QPainter>
#include <QDeclarativeProperty>

#include "layer.h"

//! Class constructor
Layer::Layer(QuasiDeclarativeItem *parent)
    : QuasiPaintedItem(parent)
      , m_drawType(Quasi::TiledDrawType)
      , m_factor(1.0)
      , m_type(Quasi::InfiniteType)
      , m_direction((Quasi::LayerDirection)-1) // Backward
      , m_areaToDraw(2.0)
      , m_columnOffset(0)
      , m_drawingMirrored(false)
      , m_shouldMirror(false)
      , m_tileWidth(32)
      , m_tileHeight(32)
      , m_latestPoint(0)
{
#if QT_VERSION >= 0x050000
    setZ(Quasi::InteractionLayerOrdering_01);
#else
    setZValue(Quasi::InteractionLayerOrdering_01);
#endif

    // this activates the item layered mode
    QDeclarativeProperty(this, "layer.enabled").write(true);
}

//! Class destructor
Layer::~Layer()
{
    m_pixmaps.clear();
    m_mirroredTiles.clear();
}

//! Stores the source path for the image
/*!
 * \param source the image path
 */
void Layer::setSource(const QString &source)
{
    if (m_source != source)
        m_source = source;
}

//! Gets the image source path
/*!
 * \return the source path for the image
 */
QString Layer::source() const
{
    return m_source;
}

//! Stores the layer type
/*!
 * \param drawType can be Tiled (default) or Plane
 */
void Layer::setDrawType(Quasi::DrawType drawType)
{
    if (m_drawType != drawType)
        m_drawType = drawType;
}

//! Gets the layer type
/*!
 * \return Tiled or Plane according the layer draw type
 */
Quasi::DrawType Layer::drawType() const
{
    return m_drawType;
}

void Layer::setDirection(const Quasi::LayerDirection &direction)
{
    if (direction != m_direction){
        if (direction == Quasi::BackwardDirection)
            m_direction = (Quasi::LayerDirection)-1; // insane black magic
        else
            m_direction = direction;

        emit directionChanged();
    }
}

//! Stores the layer update factor
/*!
 * \param factor the factor value
 */
void Layer::setFactor(qreal factor)
{
    if (m_factor != factor)
        m_factor = factor;
}

//! Gets the layer update factor
/*!
 * \return layer update factor
 */
qreal Layer::factor() const
{
    return m_factor;
}

//! Stores the layer z order
/*!
 * \param order the layer z order
 */
void Layer::setOrder(Quasi::Ordering order)
{
#if QT_VERSION >= 0x050000
    if (z() != order)
        setZ(order);
#else
    if (zValue() != order)
        setZValue(order);
#endif
}

//! Gets the layer z order
/*!
 * \return layer z order
 */
Quasi::Ordering Layer::order() const
{
#if QT_VERSION >= 0x050000
    return (Quasi::Ordering)z();
#else
    return (Quasi::Ordering)zValue();
#endif
}

void Layer::setLayerType(const Quasi::LayerType &type)
{
    if (type != m_type){
        m_type = type;

        emit layerTypeChanged();
    }
}


void Layer::setTileHeight(const int &value)
{
    if (m_drawType == Quasi::PlaneDrawType)
        return;

    if (value != m_tileHeight){
        m_tileHeight = value;

        if (m_tileWidth != 0 && m_tileHeight != 0)
            emit tilesChanged();
    }
}

void Layer::setTileWidth(const int &value)
{
    if (m_drawType == Quasi::PlaneDrawType)
        return;

    if (value != m_tileWidth){
        m_tileWidth = value;

        if (m_tileWidth != 0 && m_tileHeight != 0)
            emit tilesChanged();
    }
}

//! Adds a tile on the list
/*!
 * \param pix the pixmap to append on the list
 * \return the list actual size or -1 if the layer can not accept tiled pixmaps
 */
int Layer::addTile(const QPixmap &pix)
{
    m_pixmaps.append(pix);

    return m_pixmaps.size();
}

//! Gets a tile from the list
/*!
 * \param pos the tile position on the list
 * \return the tile pixmap of position pos on the list or null, if none
 */
QPixmap Layer::getTile(int pos) const
{
    return m_pixmaps.at(pos);
}

void Layer::setDrawGrid(bool draw)
{
    if (draw != m_drawGrid)
        m_drawGrid = draw;
}

void Layer::setGridColor(const QColor &color)
{
    if (color != m_gridColor)
        m_gridColor = color;
}

//! Gets the tiles pixmap list size
/*!
 * \return the tiles pixmap list size
 */
int Layer::count() const
{
    return m_pixmaps.size();
}

void Layer::generateOffsets()
{
    bool completed = false;
    int start = 0;
    int step = m_numColumns;
    int max = m_totalColumns;
    int count = 0;
    int maxCount = step * (int)m_areaToDraw;
    bool first = true;
    Offsets::OffsetsList firstPoint;

    while (!completed) {
        Offsets::OffsetsList offsetsList;

        int tamanho;
        int fim = 0;
        bool finish = false;

        while (count < maxCount) {
            fim = (start + step) % max;

            if (fim - start > 0) {
                tamanho = step;
                count += tamanho;

                // TODO check this comparison. Is it really needed?
                if (finish || count != maxCount) {
                    offsetsList.append(Offsets(start, tamanho));

                    if (!finish)
                        start = fim;
                    finish = false;
                } else {
                    offsetsList.append(Offsets(start, tamanho));
                }
            } else {
                int oldStart = start;
                tamanho = max - start;
                count += tamanho;

                offsetsList.append(Offsets(start, tamanho));

                tamanho = step - tamanho;
                start = 0;
                count += tamanho;

                if (tamanho != 0) {
                    offsetsList.append(Offsets(0, tamanho));
                }

                if (count <= maxCount / 2) {
                    start = tamanho;
                    finish = true;
                } else
                    start = oldStart;
            }
        }

        count = 0;

        if (offsetsList == firstPoint)
            completed = true;
        else
            m_offsets.append(offsetsList);

        if (first) {
            firstPoint = offsetsList;
            first = false;
        }
    }
}

void Layer::updateTiles()
{
    if ((boundingRect().width() == 0) || (boundingRect().height() == 0))
        return;

    // TODO create enums to define image aspect, auto tile, etc...
    QPixmap pix(source()); // TODO

    if (m_drawType == Quasi::PlaneDrawType) {
        m_tileWidth = width();
        m_tileHeight = height();

        if (pix.width() % (int)width() != 0) {
            // XXX create some log system?
            qCritical() << QString("Quasi>>Image \'%1\' doesn't contains a proper size... CROPPING!").arg(source());

            int newWidth = pix.width() - (pix.width() % (int)width());
            pix = pix.copy(0, 0, newWidth, height());
        }
    }

    if (pix.width() < boundingRect().width()) {
        QPixmap temp(boundingRect().width(), boundingRect().height());
        QPainter p(&temp);
            p.drawTiledPixmap(boundingRect(), pix, QPoint(0,0));
        p.end();

        pix = temp;
    }

    QPixmap mirrored;
    if (m_type == Quasi::MirroredType){
        QImage image = pix.toImage();

        mirrored = QPixmap::fromImage(image.mirrored(true, false));
    }

    // visible tiles
    m_numColumns = boundingRect().width() / m_tileWidth;
    m_numRows = boundingRect().height() / m_tileHeight;

    // total of columns and rows
    m_totalColumns = pix.width() / m_tileWidth;
    m_totalRows = pix.height() / m_tileHeight;

    int i, j;
    for (i = 0; i < m_totalRows; i++) {
        for (j = 0; j < m_totalColumns; j++){
            QPixmap temp(m_tileWidth, m_tileHeight);

            QPainter p(&temp);
                p.setCompositionMode(QPainter::CompositionMode_Source);
                p.drawPixmap(0, 0, m_tileWidth, m_tileHeight,
                        pix, j * m_tileWidth, i * m_tileHeight, m_tileWidth, m_tileHeight);
            p.end();

            addTile(temp);

            if (m_type == Quasi::MirroredType) {
                QPainter p(&temp);
                    p.drawPixmap(0, 0, m_tileWidth, m_tileHeight,
                            mirrored, j * m_tileWidth, i * m_tileHeight, m_tileWidth, m_tileHeight);
                p.end();

                m_mirroredTiles.append(temp);
            }
        }
    }

    generateOffsets();
    drawPixmap();
}

QPixmap Layer::generatePartialPixmap(int startPoint, int size)
{
    QPixmap temp(m_tileWidth * size, boundingRect().height());

    QPainter p(&temp);
        int i, j;
        int index = 0;
        for (i = 0; i < m_numRows; i++) {
            for (j = 0; j < size; j++) {
                index = ((i * m_totalColumns) + (j + startPoint));

                // TODO improve comparison
                if (m_direction == Quasi::ForwardDirection) {
                    if (m_drawingMirrored)
                        p.drawPixmap(j * m_tileWidth, i * m_tileHeight, getTile(index));
                    else
                        p.drawPixmap(j * m_tileWidth, i * m_tileHeight, m_mirroredTiles.at(index));
                } else {
                    if (m_drawingMirrored)
                        p.drawPixmap(j * m_tileWidth, i * m_tileHeight, m_mirroredTiles.at(index));
                    else
                        p.drawPixmap(j * m_tileWidth, i * m_tileHeight, getTile(index));
                }
                // just draw a grid
                // XXX chech the possibility of drawn it only on a debug mode
                if (m_drawGrid) {
                    p.setPen(m_gridColor);
                    p.drawRect(j * m_tileWidth, i * m_tileHeight, m_tileWidth, m_tileHeight);
                }
            }
        }
    p.end();

    return temp;
}

void Layer::drawPixmap()
{
    if ((boundingRect().width() == 0) || (boundingRect().height() == 0))
        return;

    // TODO Forward
    if (m_currentImage)
        delete m_currentImage;

    m_currentImage = new QImage(boundingRect().width() * m_areaToDraw, boundingRect().height(), QImage::Format_ARGB32_Premultiplied);

    QPainter p(m_currentImage);
        int xPoint = 0;
        for (int i = 0; i < m_offsets[m_columnOffset].size(); i++) {
            Offsets offset = m_offsets[m_columnOffset].at(i);

            if (((m_type == Quasi::MirroredType) && (i != 0)
                    && (offset.point() - m_latestPoint < 0))
                    || m_shouldMirror) {
                m_drawingMirrored = !m_drawingMirrored;
                m_shouldMirror = false;
            }

            QPixmap pix = generatePartialPixmap(offset.point(), offset.size());
            p.drawPixmap(xPoint, 0, pix);

            xPoint += pix.width();
            m_latestPoint = offset.point();

            if ((m_type == Quasi::MirroredType)
                    && (i == m_offsets[m_columnOffset].size() - 1)
                    && (offset.size() < m_numColumns))
                m_shouldMirror = true;
        }

        if (m_direction == Quasi::ForwardDirection)
            m_columnOffset = (m_columnOffset - 1 < 0) ? m_offsets.size() - 1 : m_columnOffset - 1;
        else
            m_columnOffset = (m_columnOffset + 1) % m_offsets.size();
    p.end();
}
