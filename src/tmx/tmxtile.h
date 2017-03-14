#ifndef TMXTILE
#define TMXTILE

#include "tmxobject.h"

#include <libtiled/tile.h>

class TMXMap;

class TMXTile: public TMXObject
{
    Q_OBJECT

public:
    explicit TMXTile(Tiled::Tile *tile, QObject *parent = 0)
        : TMXObject(tile, parent), m_tile(tile) {}

    TMXTile &operator=(const TMXTile &other) { setTile(other.tile()); return *this; }

    Tiled::Tile *tile() const { return m_tile; }
    void setTile(Tiled::Tile *tile) { m_tile = tile; }

    const QPixmap &image() const { return m_tile->image(); }
    void setImage(const QPixmap &image) { m_tile->setImage(image); }

    QString imageSource() const { return m_tile->imageSource(); }
    void setImageSource(const QString &imageSource) { m_tile->setImageSource(imageSource); }

    int width() const { return m_tile->width(); }
    int height() const { return m_tile->height(); }
    QSize size() const { return m_tile->size(); }

    QPoint offset() const {return m_tile->offset(); }

    int id() const { return m_tile->id(); }
private:
    Tiled::Tile *m_tile;
    TMXMap *m_map;
};

#endif // TMXTILE

