#ifndef TMXOBJECTLAYER_H
#define TMXOBJECTLAYER_H

#include "tmxlayer.h"
#include "tmxmapobject.h"

#include <libtiled/objectgroup.h>

class TMXObjectLayer : public TMXLayer
{
    Q_OBJECT

public:
    explicit TMXObjectLayer(Tiled::ObjectGroup *objLayer, QObject *parent = 0)
        : TMXLayer(objLayer, parent), m_objectLayer(objLayer) {}

    Tiled::ObjectGroup *tiledObjectLayer() const { return m_objectLayer; }
    void setTiledObjectLayer(Tiled::ObjectGroup *objLayer) { m_objectLayer = objLayer; }

    const QList<TMXMapObject*> &objects() const { return m_objects; }
    void addObject(TMXMapObject *object) { m_objects.append(object); }

private:
    Tiled::ObjectGroup *m_objectLayer;
    QList<TMXMapObject*> m_objects;
};

#endif // TMXOBJECTLAYER_H
