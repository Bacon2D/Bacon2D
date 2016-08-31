#ifndef TMXTILESET
#define TMXTILESET

#include "tmxobject.h"
#include "tmxtile.h"

#include <libtiled/tileset.h>

class TMXMap;

class TMXTileset: public TMXObject
{
    Q_OBJECT

public:
    explicit TMXTileset(Tiled::Tileset *tileset, QObject *parent = 0)
        : TMXObject(tileset, parent), m_tileset(tileset) {}

    TMXTileset &operator=(const TMXTileset &other) { setTileset(other.tileset()); return *this; }

    Tiled::Tileset *tileset() const { return m_tileset; }
    void setTileset(Tiled::Tileset *tileset) { m_tileset = tileset; }

    int tileWidth() const { return m_tileset->tileWidth(); }
    int tileHeight() const { return m_tileset->tileHeight(); }

    int imageWidth() const { return m_tileset->imageWidth(); }
    int imageHeight() const { return m_tileset->imageHeight(); }

    QString imageSource() const { return m_tileset->imageSource(); }

    TMXTile tileAt(int id) const { return TMXTile(m_tileset->tileAt(id)); }

    const QList<TMXTile> &tiles() const {
        QList<TMXTile> allTiles;
        foreach(Tiled::Tile *tile, m_tileset->tiles())
            allTiles.append(TMXTile(tile));

        return allTiles;
    }

    QString name() const { return m_tileset->name(); }
    void setName(const QString &name) { m_tileset->setName(name); }

    QString fileName() const { return m_tileset->fileName(); }
    void setFileName(const QString &fileName) { m_tileset->setFileName(fileName); }

    int tileCount() const { return m_tileset->tileCount(); }
    int columnCount() const { return m_tileset->columnCount(); }

    bool loadFromImage(const QImage &image, const QString &fileName) { return m_tileset->loadFromImage(image, fileName); }
    bool loadFromImage(const QString &fileName) { return m_tileset->loadFromImage(fileName); }
private:
    Tiled::Tileset *m_tileset;
    TMXMap *m_map;
};

#endif // TMXTILESET

