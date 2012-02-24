#include <QPainter>

#include "layer.h"
#include <QDebug>

//! Class constructor
Layer::Layer(QQuickItem *parent)
    : QQuickPaintedItem(parent)
      , m_drawType(Quasi::TiledDrawType)
      , m_factor(1.0)
      , m_type(Quasi::InfiniteType)
      , m_areaToDraw(2.0)
      , m_columnOffset(0)
      , m_drawingMirrored(false)
      , m_shouldMirror(false)
      , m_tileWidth(32)
      , m_tileHeight(32)
{
    setZ(Quasi::InteractionLayerOrdering_01);
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

//! Stores the layer update factor
/*!
 * \param factor the factor value
 */
void Layer::setFactor(float factor)
{
    if (m_factor != factor)
        m_factor = factor;
}

//! Gets the layer update factor
/*!
 * \return layer update factor
 */
float Layer::factor() const
{
    return m_factor;
}

//! Stores the layer z order
/*!
 * \param order the layer z order
 */
void Layer::setOrder(Quasi::Ordering order)
{
    if (z() != order)
        setZ(order);
}

//! Gets the layer z order
/*!
 * \return layer z order
 */
Quasi::Ordering Layer::order() const
{
    return (Quasi::Ordering)z();
}

void Layer::setType(const Quasi::LayerType &type)
{
    if (type != m_type){
        m_type = type;

        emit typeChanged();
    }
}


void Layer::setTileHeight(const int &value)
{
    if (value != m_tileHeight){
        m_tileHeight = value;

        // TODO
        if (m_tileWidth != 0 && m_tileHeight != 0) {
        //if (m_tileWidth != 0 && m_tileHeight != 0 && m_source != QString()){
            //updateTiles();
            emit tilesChanged();
        }
    }
}

void Layer::setTileWidth(const int &value)
{
    if (value != m_tileWidth){
        m_tileWidth = value;

        // TODO
        if (m_tileWidth != 0 && m_tileHeight != 0) {
        //if (m_tileWidth != 0 && m_tileHeight != 0 && m_source != QString()){
            //updateTiles();
            emit tilesChanged();
        }
    }
}

//! Adds a tile on the list
/*!
 * \param pix the pixmap to append on the list
 * \return the list actual size or -1 if the layer can not accept tiled pixmaps
 * \sa setPixmap()
 */
int Layer::addTile(const QPixmap &pix)
{
    if (m_drawType == Quasi::TiledDrawType){
        m_pixmaps.append(pix);

        return m_pixmaps.size();
    }

    return -1;
}

//! Gets a tile from the list
/*!
 * \param pos the tile position on the list
 * \return the tile pixmap of position pos on the list or null, if none
 * \sa getPixmap()
 */
QPixmap Layer::getTile(int pos) const
{
    return m_pixmaps.at(pos);
}

//! Stores a pixmap on the list (this will the only pixmap on the list)
/*!
 * \param pix the pixmao to store on the list
 * \return 1 if ok, -1 if the layer accept only tiled pixmaps
 * \sa addTile()
 */
int Layer::setPixmap(const QPixmap &pix)
{
    if (m_drawType != Quasi::TiledDrawType){
        m_pixmaps.insert(0, pix);

        return 1;
    }

    return -1;
}

//! Gets the pixmap stored on the list
/*!
 * \return the stored pixmap (full lenght), or null if none
 * \sa getTile()
 */
QPixmap Layer::getPixmap() const
{
    return m_pixmaps.at(0);
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

void Layer::updateTiles()
{
    if ((boundingRect().width() == 0) || (boundingRect().height() == 0))
        return;

    // TODO create enums to define image aspect, auto tile, etc...
    QPixmap pix(source()); // TODO

    // XXX not tiled
    if (m_drawType != Quasi::TiledDrawType) {
        setPixmap(pix);
    } else {
        if (pix.width() < boundingRect().width()){
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
    }

    drawPixmap();
    update();
}

void Layer::drawPixmap()
{
    if ((boundingRect().width() == 0) || (boundingRect().height() == 0))
        return;

    // TODO caching
    // TODO Forward
    if (m_currentPixmap)
        delete m_currentPixmap;

    // XXX not tiled
    if (m_drawType != Quasi::TiledDrawType) {
        m_currentPixmap = new QPixmap(getPixmap());

        return;
    }

    m_currentPixmap = new QPixmap(boundingRect().width() * m_areaToDraw, boundingRect().height());

    QPainter p(m_currentPixmap);
        bool completed = false;
        int i = 0, j = 0, index = 0;
        int startJ = 0;
        int maxJ = (m_numColumns * m_areaToDraw) - m_columnOffset;
        int counter = 0;
        int adder = 0;
        int currentOffset = m_columnOffset;

        bool halfDraw = false;
        int colsToDraw = m_numColumns * m_areaToDraw;

        do {
            if (adder > 0) {
                maxJ = adder;
                adder = 0;
                currentOffset = 0;
                startJ = j;

                if (m_type == Quasi::MirroredType)
                    m_drawingMirrored = !m_drawingMirrored;

                m_shouldMirror = true;
            } else if (currentOffset + colsToDraw >= m_totalColumns) {
                maxJ = m_totalColumns - currentOffset;
                adder = colsToDraw - maxJ;
                startJ = j = halfDraw ? currentOffset : 0;
            } else {
                maxJ = m_totalColumns - currentOffset;
                startJ = j = halfDraw ? currentOffset : 0;
            }

            if (counter >= colsToDraw * m_numRows) { // well done
                completed = true;

                m_columnOffset += m_numColumns;
                if (m_columnOffset >= m_totalColumns)
                    m_columnOffset = m_columnOffset - m_totalColumns;
                else if (m_type == Quasi::MirroredType && m_shouldMirror)
                    m_drawingMirrored = !m_drawingMirrored;

                m_shouldMirror = false;
            } else {
                for (i = 0; i < m_numRows; i++) {
                    for (j = startJ; j < maxJ + startJ; j++) {
                        index = ((i * m_totalColumns) + (j - startJ) + currentOffset) % count();

                        if (m_drawingMirrored) {
                            p.drawPixmap(j * m_tileWidth, i * m_tileHeight, m_mirroredTiles.at(index));
                        } else {
                            p.drawPixmap(j * m_tileWidth, i * m_tileHeight, getTile(index));
                        }

                        // just draw a grid
                        if (m_drawGrid) {
                            p.setPen(m_gridColor);
                            p.drawRect(j * m_tileWidth, i * m_tileHeight, m_tileWidth, m_tileHeight);
                        }

                        counter++;
                    }
                }
            }
        } while (!completed);
    p.end();
}
