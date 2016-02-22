#ifndef TMXIMAGELAYER_H
#define TMXIMAGELAYER_H

#include "tmxlayer.h"
#include <QPixmap>

#include <libtiled/imagelayer.h>

class TMXImageLayer : public TMXLayer
{
    Q_OBJECT

public:
    explicit TMXImageLayer(Tiled::ImageLayer *imageLayer, QObject *parent = 0)
        : TMXLayer(imageLayer, parent) , m_imageLayer(imageLayer) {}

    explicit TMXImageLayer(const TMXLayer &layer, QObject *parent = 0)
        : TMXLayer(layer.layer()->asImageLayer(), parent) , m_imageLayer(layer.layer()->asImageLayer()) {}

    Tiled::ImageLayer *tiledImageLayer() const { return m_imageLayer; }
    void setTiledImageLayer(Tiled::ImageLayer *imageLayer) { m_imageLayer = imageLayer; }

    QPixmap image() const { return m_imageLayer->image(); }
private:
    Tiled::ImageLayer *m_imageLayer;
};

#endif // TMXIMAGELAYER_H
