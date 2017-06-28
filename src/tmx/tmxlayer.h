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

#ifndef TMXLAYER_H
#define TMXLAYER_H

#include "tmxobject.h"

#include <libtiled/layer.h>

class TMXMap;
class TMXObjectLayer;
class TMXTileLayer;
class TMXImageLayer;

class TMXLayer : public TMXObject
{
    Q_OBJECT

public:
    explicit TMXLayer(Tiled::Layer *layer, QObject *parent = 0)
        : TMXObject(layer, parent), m_layer(layer) {}

    TMXLayer &operator=(const TMXLayer &other) { setLayer(other.layer()); return *this; }

    bool isNull() const { return m_layer == nullptr; }

    Tiled::Layer *layer() const { return  m_layer; }
    void setLayer(Tiled::Layer *layer) { m_layer = layer; }

    QString name() const { return m_layer->name(); }
    void setName(const QString &name) { m_layer->setName(name); }

    float opacity() const { return m_layer->opacity(); }
    void setOpacity(float opacity) { m_layer->setOpacity(opacity); }

    bool isVisible() const { return m_layer->isVisible(); }
    void setVisible(bool visible) { m_layer->setVisible(visible); }

    TMXMap *map() const { return m_map; }
    void setMap(TMXMap *map) { m_map = map; }

    int x() const { return m_layer->x(); }
    void setX(int x) { m_layer->setX(x); }

    int y() const { return m_layer->y(); }
    void setY(int y) { m_layer->setY(y); }

    QPoint position() const { return m_layer->position(); }
    void setPosition(QPoint pos) { m_layer->setPosition(pos); }
    void setPosition(int x, int y) { m_layer->setPosition(x, y); }

    int width() const { return lWidth; }
    int height() const { return lHeight; }

    QRect bounds() const { return QRect(m_layer->x(), m_layer->y(), lWidth, lHeight); }

    QSize size() const { return QSize(lWidth, lHeight); }
    void setSize(const QSize &size) { lWidth = size.width(); lHeight = size.height(); }

    bool isTileLayer() const { return m_layer->isTileLayer(); }
    bool isImageLayer() const { return m_layer->isImageLayer(); }
    bool isObjectLayer() const { return m_layer->isObjectGroup(); }

    QPoint positionAt(const QPoint &pos) const { return pos; }
private:
    Tiled::Layer *m_layer;
    TMXMap *m_map;
    int lWidth;
    int lHeight;
};

#endif // TMXLAYER_H
