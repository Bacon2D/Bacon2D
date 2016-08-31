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

    int width() const { return m_layer->width(); }
    int height() const { return m_layer->height(); }

    QRect bounds() const { return m_layer->bounds(); }

    QSize size() const { return m_layer->size(); }
    void setSize(const QSize &size) { m_layer->setSize(size); }

    bool isTileLayer() const { return m_layer->isTileLayer(); }
    bool isImageLayer() const { return m_layer->isImageLayer(); }
    bool isObjectLayer() const { return m_layer->isObjectGroup(); }

    QPoint positionAt(const QPoint &pos) const { return pos; }
private:
    Tiled::Layer *m_layer;
    TMXMap *m_map;
};

#endif // TMXLAYER_H
