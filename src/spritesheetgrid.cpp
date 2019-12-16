#include "spritesheetgrid.h"
#include <QPixmapCache>
#include <QUrl>
#include <QDebug>

SpriteSheetGrid::SpriteSheetGrid(QObject *parent) :
    QObject(parent),
    m_width(0.0),
    m_height(0.0),
    m_implicitWidth(0.0),
    m_implicitHeight(0.0),
    m_horizontalFrameCount(1),
    m_verticalFrameCount(1),
    m_frameWidth(0.0),
    m_frameHeight(0.0),
    m_fillMode(Bacon2D::Stretch)
{

}

QUrl SpriteSheetGrid::source() const
{
    return m_source;
}

void SpriteSheetGrid::setSource(const QUrl &source)
{
    if (m_source == source)
        return;

    m_source = source;
    QString sourceAsString;
    if (m_source.url().startsWith("qrc:/"))
        sourceAsString = m_source.url().replace(QString("qrc:/"), QString(":/"));
    else
        sourceAsString = m_source.toLocalFile();

    m_pixmap.load(sourceAsString);
    setWidth(m_pixmap.width());
    setHeight(m_pixmap.height());
    savePixmap();

    emit sourceChanged();
}

QSize SpriteSheetGrid::sourceSize() const
{
    return m_sourceSize;
}

void SpriteSheetGrid::setSourceSize(const QSize &sourceSize)
{
    if (m_sourceSize == sourceSize)
        return;

    m_sourceSize = sourceSize;

    if (m_width <= 0.0)
        setWidth(m_sourceSize.width());
    if (m_height <= 0.0)
        setHeight(m_sourceSize.height());

    emit sourceSizeChanged();
}

QPixmap SpriteSheetGrid::pixmap() const
{
    return m_pixmap;
}

QPixmapCache::Key SpriteSheetGrid::key() const
{
    return m_key;
}

qreal SpriteSheetGrid::width() const
{
    return m_width;
}

qreal SpriteSheetGrid::height() const
{
    return m_height;
}

qreal SpriteSheetGrid::implicitWidth() const
{
    return m_implicitWidth;
}

qreal SpriteSheetGrid::implicitHeight() const
{
    return m_implicitHeight;
}

int SpriteSheetGrid::horizontalFrameCount() const
{
    return m_horizontalFrameCount;
}

void SpriteSheetGrid::setHorizontalFrameCount(int horizontalFrameCount)
{
    if (m_horizontalFrameCount == horizontalFrameCount)
        return;

    m_horizontalFrameCount = horizontalFrameCount;
    emit horizontalFrameCountChanged();
}

int SpriteSheetGrid::verticalFrameCount() const
{
    return m_verticalFrameCount;
}

void SpriteSheetGrid::setVerticalFrameCount(int verticalFrameCount)
{
    if (m_verticalFrameCount == verticalFrameCount)
        return;

    m_verticalFrameCount = verticalFrameCount;
    emit verticalFrameCountChanged();
}

qreal SpriteSheetGrid::frameWidth() const
{
    return m_frameWidth;
}

void SpriteSheetGrid::setFrameWidth(qreal frameWidth)
{
    if (m_frameWidth == frameWidth)
        return;

    m_frameWidth = frameWidth;
    emit frameWidthChanged();
}

qreal SpriteSheetGrid::frameHeight() const
{
    return m_frameHeight;
}

void SpriteSheetGrid::setFrameHeight(qreal frameHeight)
{
    if (m_frameHeight == frameHeight)
        return;

    m_frameHeight = frameHeight;
    emit frameHeightChanged();
}

Bacon2D::FillMode SpriteSheetGrid::fillMode() const
{
    return m_fillMode;
}

void SpriteSheetGrid::setFillMode(Bacon2D::FillMode fillMode)
{
    if (m_fillMode == fillMode)
        return;

    m_fillMode = fillMode;
    emit fillModeChanged();
}

void SpriteSheetGrid::classBegin()
{

}

void SpriteSheetGrid::componentComplete()
{
    savePixmap();

    m_width = m_pixmap.width();
    m_height = m_pixmap.height();

    if (m_frameWidth <= 0.0 && m_horizontalFrameCount > 0)
        m_frameWidth = m_width / m_horizontalFrameCount;

    if (m_frameHeight <= 0.0 && m_verticalFrameCount > 0)
        m_frameHeight = m_height / m_verticalFrameCount;
}

void SpriteSheetGrid::setWidth(qreal width)
{
    if (m_width == width)
        return;

    m_width = width;
    emit widthChanged();
}

void SpriteSheetGrid::setHeight(qreal height)
{
    if (m_height == height)
        return;

    m_height = height;
    emit heightChanged();
}

void SpriteSheetGrid::setImplicitWidth(qreal implicitWidth)
{
    if (m_implicitWidth == implicitWidth)
        return;

    m_implicitWidth = implicitWidth;
    emit implicitWidthChanged();
}

void SpriteSheetGrid::setImplicitHeight(qreal implicitHeight)
{
    if (m_implicitHeight == implicitHeight)
        return;

    m_implicitHeight = implicitHeight;
    emit implicitHeightChanged();
}

void SpriteSheetGrid::savePixmap()
{
    if (!m_source.isEmpty()) {
        if (QPixmapCache::find(m_source.toString().toUtf8().toHex(), &m_pixmap)) {
            m_implicitWidth = m_pixmap.width();
            m_implicitHeight = m_pixmap.height();
            m_width = m_implicitWidth;
            m_height = m_implicitHeight;
        } else {
            QPixmapCache::insert(m_source.toString().toUtf8().toHex(), m_pixmap);
        }
    }
}
