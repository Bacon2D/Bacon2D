#ifndef TMXOBJECTGROUP
#define TMXOBJECTGROUP

#include "tmxmapobject.h"
#include "tmxlayer.h"

#include <libtiled/objectgroup.h>
#include <libtiled/mapobject.h>

#include <QtCore/QObject>

class TMXObjectGroup : public TMXLayer
{
    Q_OBJECT

public:
    explicit TMXObjectGroup(Tiled::ObjectGroup *tiledObjectGroup, QObject *parent = 0)
        : TMXLayer(tiledObjectGroup, parent), m_tiledObjectGroup(tiledObjectGroup) {}

    explicit TMXObjectGroup(const TMXLayer &layer, QObject *parent = 0)
        : TMXLayer(layer.layer()->asObjectGroup(), parent), m_tiledObjectGroup(layer.layer()->asObjectGroup()) {}

    Tiled::ObjectGroup *tiledObjectGroup() { return m_tiledObjectGroup; }
    void setTiledObjectGroup(Tiled::ObjectGroup *tiledObjectGroup) { m_tiledObjectGroup = tiledObjectGroup; }

    QList<TMXMapObject> objects() const {
        QList<TMXMapObject> allObjects;
        for(auto& object : m_tiledObjectGroup->objects())
            allObjects.append(TMXMapObject(object));

        return allObjects;
    }
private:
    Tiled::ObjectGroup *m_tiledObjectGroup;
};

#endif // TMXOBJECTGROUP

