#ifndef SPRITESHEETGRID_H
#define SPRITESHEETGRID_H

#include <QObject>
#include <QPixmap>
#include <QPixmapCache>
#include <QQmlParserStatus>
#include <QUrl>

#include "enums.h"

class SpriteSheetGrid : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QSize sourceSize READ sourceSize WRITE setSourceSize NOTIFY sourceSizeChanged)
    Q_PROPERTY(qreal width READ width NOTIFY widthChanged)
    Q_PROPERTY(qreal height READ height NOTIFY heightChanged)
    Q_PROPERTY(qreal implicitWidth READ implicitWidth NOTIFY implicitWidthChanged)
    Q_PROPERTY(qreal implicitHeight READ implicitHeight NOTIFY implicitHeightChanged)
    Q_PROPERTY(int horizontalFrameCount READ horizontalFrameCount WRITE setHorizontalFrameCount NOTIFY horizontalFrameCountChanged)
    Q_PROPERTY(int verticalFrameCount READ verticalFrameCount WRITE setVerticalFrameCount NOTIFY verticalFrameCountChanged)
    Q_PROPERTY(qreal frameWidth READ frameWidth WRITE setFrameWidth NOTIFY frameWidthChanged)
    Q_PROPERTY(qreal frameHeight READ frameHeight WRITE setFrameHeight NOTIFY frameHeightChanged)
    Q_PROPERTY(Bacon2D::FillMode fillMode READ fillMode WRITE setFillMode NOTIFY fillModeChanged)
public:
    explicit SpriteSheetGrid(QObject *parent = nullptr);

    QUrl source() const;
    void setSource(const QUrl &source);

    QSize sourceSize() const;
    void setSourceSize(const QSize &sourceSize);

    QPixmap pixmap() const;
    QPixmapCache::Key key() const;

    qreal width() const;
    qreal height() const;

    qreal implicitWidth() const;
    qreal implicitHeight() const;

    int horizontalFrameCount() const;
    void setHorizontalFrameCount(int horizontalFrameCount);

    int verticalFrameCount() const;
    void setVerticalFrameCount(int verticalFrameCount);

    qreal frameWidth() const;
    void setFrameWidth(qreal frameWidth);

    qreal frameHeight() const;
    void setFrameHeight(qreal frameHeight);

    Bacon2D::FillMode fillMode() const;
    void setFillMode(Bacon2D::FillMode fillMode);

    void classBegin() override;
    void componentComplete() override;

signals:
    void sourceChanged();
    void sourceSizeChanged();
    void widthChanged();
    void heightChanged();
    void implicitWidthChanged();
    void implicitHeightChanged();
    void horizontalFrameCountChanged();
    void verticalFrameCountChanged();
    void frameWidthChanged();
    void frameHeightChanged();
    void fillModeChanged();

private:
    QPixmap m_pixmap;
    QPixmapCache::Key m_key;
    QUrl m_source;
    QSize m_sourceSize;
    qreal m_width;
    qreal m_height;
    qreal m_implicitWidth;
    qreal m_implicitHeight;
    int m_horizontalFrameCount;
    int m_verticalFrameCount;
    qreal m_frameWidth;
    qreal m_frameHeight;
    Bacon2D::FillMode m_fillMode;

    void setWidth(qreal width);
    void setHeight(qreal height);
    void setImplicitWidth(qreal implicitWidth);
    void setImplicitHeight(qreal implicitHeight);

    void savePixmap();
};

#endif // SPRITESHEETGRID_H
