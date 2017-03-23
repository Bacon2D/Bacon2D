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
