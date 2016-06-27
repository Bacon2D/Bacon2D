/**
 * The MIT License (MIT)
 *
 * Copyright (C) 2012 by INdT
 * Copyright (C) 2014 Bacon2D Project
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
 * @author Rodrigo Goncalves de Oliveira <rodrigo.goncalves@openbossa.org>
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

#ifndef _LAYER_H_
#define _LAYER_H_

#include "behavior.h"
#include "game.h"
#include "entity.h"
#include "scene.h"

#include <QtCore/QtGlobal>

class QQuickItem;

//! A layer class
class Layer: public Entity
{
    Q_OBJECT

    Q_PROPERTY(Layer::LayerType layerType READ layerType WRITE setLayerType NOTIFY layerTypeChanged)

    Q_ENUMS (
        LayerType
    )

public:
    Layer(QQuickItem *parent = 0);
    virtual ~Layer();

    virtual void update(const int &delta);

    enum LayerType {
        Infinite,
        Mirrored
    };

    Layer::LayerType layerType() const { return m_type; }
    void setLayerType(const Layer::LayerType &type);

signals:
    void layerTypeChanged();

protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);
    void updateEntities(const int &delta);

    bool m_isAnimated;
    qreal m_horizontalStep;
    Layer::LayerType m_type;
};

#endif /* _LAYER */
