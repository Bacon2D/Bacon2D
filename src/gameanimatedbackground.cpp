#include "gameanimatedbackground.h"

GameAnimatedBackground::GameAnimatedBackground(GameBaseBackground *parent)
    : GameBaseBackground(parent)
      , m_horizontalOffset(0)
      , m_columnOffset(0)
      , m_direction((Direction)-1) // Backward
      , m_type(Infinite)
      , m_drawingMirrored(false)
      , m_shouldMirror(false)
{
    connect(this, SIGNAL(horizontalOffsetChanged()), this, SLOT(update()));
}

GameAnimatedBackground::~GameAnimatedBackground()
{
}

void GameAnimatedBackground::setHorizontalOffset(const int offset)
{
    int temp = offset;
    if (temp < 0)
        temp *= -1;

    if (temp != m_horizontalOffset){
        m_horizontalOffset = temp;

        if (m_horizontalOffset >= boundingRect().width()){
            drawPixmap();
            m_horizontalOffset = 0;
        }

        emit horizontalOffsetChanged();
    }
}

void GameAnimatedBackground::setDirection(const Direction direction)
{
    if (direction != m_direction){
        if (direction == Backward)
            m_direction = (Direction)-1; // insane black magic
        else
            m_direction = direction;


        emit directionChanged();
    }
}

void GameAnimatedBackground::setType(const Type type)
{
    if (type != m_type){
        m_type = type;

        emit typeChanged();
    }
}

void GameAnimatedBackground::updateTiles()
{
    if ((boundingRect().width() == 0) || (boundingRect().height() == 0))
        return;

    // TODO create enums to define image aspect, auto tile, etc...
    QPixmap pix(source());
    if (pix.width() < boundingRect().width()){
        QPixmap temp(boundingRect().width(), boundingRect().height());
        QPainter p(&temp);
            p.drawTiledPixmap(boundingRect(), pix, QPoint(0,0));
        p.end();

        pix = temp;
    }

    QPixmap mirrored;
    if (m_type == Mirrored){
        QImage image = pix.toImage();

        mirrored = QPixmap::fromImage(image.mirrored(true, false));
    }

    // visible tiles
    m_numColumns = boundingRect().width() / m_tileWidth;
    m_numRows = boundingRect().height() / m_tileHeight;

    // total of columns and rows
    m_totalColumns = pix.width() / m_tileWidth;
    m_totalRows = pix.height() / m_tileHeight;

    m_tiles.clear();

    int i, j;
    for (i = 0; i < m_totalRows; i++){
        for (j = 0; j < m_totalColumns; j++){
            QPixmap temp(m_tileWidth, m_tileHeight);

            QPainter p(&temp);
                p.drawPixmap(0, 0, m_tileWidth, m_tileHeight,
                        pix, j * m_tileWidth, i * m_tileHeight, m_tileWidth, m_tileHeight);
            p.end();

            m_tiles.append(temp);

            if (m_type == Mirrored){
                QPainter p(&temp);
                    p.drawPixmap(0, 0, m_tileWidth, m_tileHeight,
                            mirrored, j * m_tileWidth, i * m_tileHeight, m_tileWidth, m_tileHeight);
                p.end();

                m_mirroredTiles.append(temp);
            }
        }
    }

    drawPixmap();
    update();
}

void GameAnimatedBackground::drawPixmap()
{
    // TODO caching
    // TODO try to change some divisions/multiplications by a const variable
    // TODO Forward
    if (m_currentPixmap)
        delete m_currentPixmap;

    // use cached image, if exists
    /*int temp = m_columnOffset + m_numColumns;
    if (temp >= m_totalColumns)
        temp -= m_totalColumns;*/ // TODO

    //if (QPixmapCache::find(QString("IMAGEM_%1").arg(m_columnOffset), m_currentPixmap)){
    //    qDebug() << QString("CACHED %1").arg(m_columnOffset);
    /*QString str = QString("IMAGEM_%1").arg(temp);
    qDebug() << "temp:" << temp << "str:" << str;
    if (QPixmapCache::find(str, m_currentPixmap)){
    //if (QPixmapCache::find(QString("IMAGEM_%1").arg(temp), m_currentPixmap)){
        qDebug() << QString("CACHED %1").arg(temp);

        m_columnOffset = m_columnOffset + m_numColumns;
        if (m_columnOffset >= m_totalColumns)
            m_columnOffset -= m_totalColumns;
        return;
    }*/

    m_currentPixmap = new QPixmap(2 * boundingRect().width(), boundingRect().height());

    QPainter p(m_currentPixmap);
        bool completed = false;
        int i = 0, j = 0, index = 0;
        int startJ = 0;
        //int maxJ = (m_numColumns) - m_columnOffset;
        int maxJ = (m_numColumns*2) - m_columnOffset;
        int counter = 0;
        int adder = 0;
        int currentOffset = m_columnOffset;

        bool halfDraw = false;
        int colsToDraw = 2*m_numColumns;

        do {
            if (adder > 0){
                maxJ = adder;
                adder = 0;
                currentOffset = 0;
                startJ = j;

                if (m_type == Mirrored)
                    m_drawingMirrored = !m_drawingMirrored;

                m_shouldMirror = true;
            } else if (currentOffset + colsToDraw >= m_totalColumns){
                maxJ = m_totalColumns - currentOffset;
                adder = colsToDraw - maxJ;
                startJ = j = halfDraw ? currentOffset : 0;
            } else{
                maxJ = m_totalColumns - currentOffset;
                startJ = j = halfDraw ? currentOffset : 0;
            }

            if (counter >= colsToDraw * m_numRows){ // well done
                completed = true;

                m_columnOffset += m_numColumns;
                if (m_columnOffset >= m_totalColumns)
                    m_columnOffset = m_columnOffset - m_totalColumns;
                else if (m_type == Mirrored && m_shouldMirror)
                    m_drawingMirrored = !m_drawingMirrored;

                m_shouldMirror = false;
            } else {
                for (i = 0; i < m_numRows; i++){
                    for (j = startJ; j < maxJ + startJ; j++){
                        index = ((i * m_totalColumns) + (j - startJ) + currentOffset) % m_tiles.size();

                        if (m_drawingMirrored){
                            p.drawPixmap(j * m_tileWidth, i * m_tileHeight, m_mirroredTiles.at(index));
                        } else{
                            p.drawPixmap(j * m_tileWidth, i * m_tileHeight, m_tiles.at(index));
                        }

                        // just draw a grid
                        if (m_drawGrid){
                            p.setPen(m_gridColor);
                            p.drawRect(j * m_tileWidth, i * m_tileHeight, m_tileWidth, m_tileHeight);
                        }

                        counter++;
                    }
                }
            }
        } while (!completed);
    p.end();

    //m_currentPixmap = temp;

        /*QString str2 = QString("IMAGEM_%1").arg(m_columnOffset);
    QPixmapCache::insert(str2, *m_currentPixmap);
    //QPixmapCache::insert(QString("IMAGEM_%1").arg(m_columnOffset), *m_currentPixmap);
    qDebug() << QString("CREATED %1").arg(m_columnOffset) << "str2:" << str2 << "\n--";
    //m_currentPixmap->save(QString("/tmp/HUA-%1.png").arg(m_columnOffset));
    //m_currentPixmap->save("/tmp/" + str2 + ".png");*/
    /*if (m_type == Mirrored && m_drawingMirrored)
        m_currentPixmap->save(QString("/tmp/HUA-%1-m.png").arg(m_columnOffset));
    else
        m_currentPixmap->save(QString("/tmp/HUA-%1.png").arg(m_columnOffset));*/
}

void GameAnimatedBackground::paint(QPainter *painter)
{
    painter->drawPixmap(m_horizontalOffset * m_direction, 0, *m_currentPixmap);
}
