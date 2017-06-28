/**
 * The MIT License (MIT)
 *
 * Copyright (C) 2017 Bacon2D Project
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

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

