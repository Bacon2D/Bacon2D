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

#include "imagelayer.h"

#include <QtCore/QDebug>

ImageLayer::ImageLayer(Layer *parent)
    : Layer((QuasiDeclarativeItem *)parent)
    , m_currentImage(0)
    , m_tileWidth(32)
    , m_tileHeight(32)
    , m_drawType(Quasi::TiledDrawType)
    , m_areaToDraw(2.0)
    , m_columnOffset(0)
    , m_latestPoint(0)
    , m_globalXPos(0.0)
    , m_localXPos(0.0)
    , m_localYPos(0.0)
    , m_initialized(false)
{
    connect(this, SIGNAL(horizontalDirectionChanged()),
            this, SLOT(onHorizontalDirectionChanged()));
}

ImageLayer::~ImageLayer()
{
    m_pixmaps.clear();
}

//! Stores the source path for the image
/*!
 * \param source the image path
 */
void ImageLayer::setSource(const QString &source)
{
    if (m_source == source)
        return;

    m_source = source;

    emit sourceChanged();
}

//! Gets the image source path
/*!
 * \return the source path for the image
 */
QString ImageLayer::source() const
{
    return m_source;
}

//! Stores the layer type
/*!
 * \param drawType can be Tiled (default) or Plane
 */
void ImageLayer::setDrawType(Quasi::DrawType drawType)
{
    if (m_drawType != drawType)
        m_drawType = drawType;
}

//! Gets the layer type
/*!
 * \return Tiled or Plane according the layer draw type
 */
Quasi::DrawType ImageLayer::drawType() const
{
    return m_drawType;
}

void ImageLayer::setTileHeight(const int &value)
{
    if (value == m_tileHeight)
        return;

    m_tileHeight = value;

    emit tilesChanged();
}

void ImageLayer::setTileWidth(const int &value)
{
    if (value == m_tileWidth)
        return;

    m_tileWidth = value;

    emit tilesChanged();
}

//! Adds a tile on the list
/*!
 * \param pix the pixmap to append on the list
 * \return the list actual size or -1 if the layer can not accept tiled pixmaps
 */
int ImageLayer::addTile(const QPixmap &pixmap)
{
    m_pixmaps.append(pixmap);

    return m_pixmaps.size();
}

//! Gets a tile from the list
/*!
 * \param pos the tile position on the list
 * \return the tile pixmap of position pos on the list or null, if none
 */
QPixmap ImageLayer::getTile(int pos) const
{
    return m_pixmaps.at(pos);
}

void ImageLayer::setDrawGrid(bool draw)
{
    if (draw == m_drawGrid)
        return;

    m_drawGrid = draw;
}

void ImageLayer::setGridColor(const QColor &color)
{
    if (color == m_gridColor)
        return;

    m_gridColor = color;
}

//! Gets the tiles pixmap list size
/*!
 * \return the tiles pixmap list size
 */
int ImageLayer::count() const
{
    return m_pixmaps.size();
}

void ImageLayer::generateOffsets()
{
    bool completed = false;
    int start = 0;
    int step = m_numColumns;
    int max = m_totalColumns;
    int count = 0;
    int maxCount = step * (int) m_areaToDraw;
    bool first = true;
    Offsets::OffsetsList firstPoint;

    while (!completed) {
        Offsets::OffsetsList offsetsList;

        int size;
        int end = 0;
        bool finished = false;

        while (count < maxCount) {
            end = (start + step) % max;

            if (end - start > 0) {
                size = step;
                count += size;

                // TODO check this comparison. Is it really needed?
                if (finished || count != maxCount) {
                    offsetsList.append(Offsets(start, size));

                    if (!finished)
                        start = end;
                    finished = false;
                } else {
                    offsetsList.append(Offsets(start, size));
                }
            } else {
                int oldStart = start;
                size = max - start;
                count += size;

                offsetsList.append(Offsets(start, size));

                size = step - size;
                start = 0;
                count += size;

                if (size != 0) {
                    offsetsList.append(Offsets(0, size));
                }

                if (count <= maxCount / 2) {
                    start = size;
                    finished = true;
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

void ImageLayer::updateTiles()
{
    if ((boundingRect().width() == 0) || (boundingRect().height() == 0))
        return;

    // TODO create enums to define image aspect, auto tile, etc...
    QPixmap pixmap(source()); // TODO

    if (m_drawType == Quasi::PlaneDrawType) {
        m_tileWidth = width();
        m_tileHeight = height();

        if (pixmap.width() % (int)width() != 0) {
            // XXX create some log system?
            qCritical() << QString("Quasi>>Image \'%1\' doesn't contains a proper size... CROPPING!").arg(source());

            int newWidth = pixmap.width() - (pixmap.width() % (int)width());
            pixmap = pixmap.copy(0, 0, newWidth, height());
        }
    }

    if (pixmap.width() < boundingRect().width()) {
        QPixmap temp(boundingRect().width(), boundingRect().height());
        QPainter p(&temp);
            p.drawTiledPixmap(boundingRect(), pixmap, QPoint(0,0));
        p.end();

        pixmap = temp;
    }

    if (m_type == Quasi::MirroredType) {
        QPixmap temp(pixmap.width() * 2, pixmap.height());

        QPainter p(&temp);
            p.drawPixmap(0, 0, pixmap.width(), pixmap.height(), pixmap);
            p.drawPixmap(pixmap.width(), 0, pixmap.width(), pixmap.height(),
                         pixmap.transformed(QTransform().scale(-1, 1), Qt::FastTransformation));
        p.end();

        pixmap = temp;
    }

    // visible tiles
    m_numColumns = boundingRect().width() / m_tileWidth;
    m_numRows = boundingRect().height() / m_tileHeight;

    // total of columns and rows
    m_totalColumns = pixmap.width() / m_tileWidth;
    m_totalRows = pixmap.height() / m_tileHeight;

    int i, j;
    for (i = 0; i < m_totalRows; i++) {
        for (j = 0; j < m_totalColumns; j++) {
            QPixmap temp(m_tileWidth, m_tileHeight);

            QPainter p(&temp);
                p.setCompositionMode(QPainter::CompositionMode_Source);
                p.drawPixmap(0, 0, m_tileWidth, m_tileHeight,
                             pixmap, j * m_tileWidth, i * m_tileHeight, m_tileWidth, m_tileHeight);
            p.end();

            addTile(temp);
        }
    }

    generateOffsets();
    drawPixmap();
}

QPixmap ImageLayer::generatePartialPixmap(int startPoint, int size)
{
    QPixmap temp(m_tileWidth * size, boundingRect().height());

    QPainter p(&temp);
        int i, j;
        int index = 0;
        for (i = 0; i < m_numRows; i++) {
            for (j = 0; j < size; j++) {
                index = ((i * m_totalColumns) + (j + startPoint));

                p.drawPixmap(j * m_tileWidth, i * m_tileHeight, getTile(index));

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

void ImageLayer::drawPixmap()
{
    if ((boundingRect().width() == 0) || (boundingRect().height() == 0))
        return;

    if (m_currentImage)
        delete m_currentImage;

    m_currentImage = new QImage(boundingRect().width() * m_areaToDraw,
                                boundingRect().height(), QImage::Format_ARGB32_Premultiplied);

    QPainter p(m_currentImage);
        int xPoint = 0;
        for (int i = 0; i < m_offsets[m_columnOffset].size(); i++) {
            Offsets offset = m_offsets[m_columnOffset].at(i);

            QPixmap pixmap = generatePartialPixmap(offset.point(), offset.size());
            p.drawPixmap(xPoint, 0, pixmap);

            xPoint += pixmap.width();
            m_latestPoint = offset.point();
        }

        if (m_horizontalStep > 0)
            m_columnOffset = (m_columnOffset - 1 < 0) ? m_offsets.size() - 1 : m_columnOffset - 1;
        else
            m_columnOffset = (m_columnOffset + 1) % m_offsets.size();
    p.end();
}

// move to a X value
void ImageLayer::moveX(const qreal &x)
{
    qreal newValue = x;
    qreal delta = m_globalXPos + newValue;

    m_globalXPos = newValue * -1;
    m_localXPos -= delta;

    if (m_localXPos <= -width()) {
        drawPixmap();
        m_localXPos = width() + m_localXPos;
    } else if (m_localXPos >= 0) {
        if (m_globalXPos != 0) {
            drawPixmap();
            m_localXPos = -width() + m_localXPos;
        } else
            m_localXPos = 0;
    }
}

void ImageLayer::moveY(const qreal &y)
{
    Q_UNUSED(y);

    // TBD
}

void ImageLayer::updateHorizontalStep()
{
    m_currentHorizontalStep += m_horizontalStep;

    if (m_currentHorizontalStep <= -width()) {
        drawPixmap();
        m_currentHorizontalStep = 0;
    } else if (m_currentHorizontalStep >= 0) {
        drawPixmap();
        m_currentHorizontalStep = -width();
    }
}

void ImageLayer::onHorizontalDirectionChanged()
{
    if (m_offsets.count() != 0)
        m_columnOffset = (m_columnOffset + 2) % m_offsets.size();
}

#if QT_VERSION >= 0x050000
void ImageLayer::paint(QPainter *painter)
{
#else
void ImageLayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
#endif

    if (!m_currentImage)
        return;

    if (m_isAnimated)
        updateHorizontalStep();

    painter->drawImage(m_currentHorizontalStep, 0, *m_currentImage);
}

void ImageLayer::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    if (newGeometry.isEmpty() || m_initialized)
        return;

    updateTiles();

    m_initialized = true;

    Layer::geometryChanged(newGeometry, oldGeometry);
}
