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
#include "scene.h"

#include <QtQuick/QQuickItem>
#include <QtCore/QtGlobal>
#include <QtCore/QTime>

//! A layer class
class Bacon2DLayer: public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(Bacon2DLayer::LayerType layerType READ layerType WRITE setLayerType NOTIFY layerTypeChanged)
    Q_PROPERTY(Behavior *behavior READ behavior WRITE setBehavior NOTIFY behaviorChanged)
    Q_PROPERTY(Game *game READ game)
    Q_PROPERTY(Scene *scene READ scene WRITE setScene NOTIFY sceneChanged)
    Q_PROPERTY(int updateInterval READ updateInterval WRITE setUpdateInterval NOTIFY updateIntervalChanged)

    Q_ENUMS (
        LayerType
    )

public:
    Bacon2DLayer(QQuickItem *parent = 0);
    virtual ~Bacon2DLayer();

    virtual void update(const int &delta);

    Behavior *behavior() const;
    void setBehavior(Behavior *behavior);

    Game *game() const;

    Scene *scene() const;
    void setScene(Scene *scene);

    int updateInterval() const;
    void setUpdateInterval(const int &updateInterval);

    enum LayerType {
        Infinite,
        Mirrored
    };

    Bacon2DLayer::LayerType layerType() const { return m_type; };
    void setLayerType(const Bacon2DLayer::LayerType &type);

signals:
    void layerTypeChanged();
    void updateIntervalChanged();
    void behaviorChanged();
    void sceneChanged();

protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);
    void updateEntities(const int &delta);

    bool m_isAnimated;
    qreal m_horizontalStep;
    Bacon2DLayer::LayerType m_type;
    QTime m_updateTime;
    int m_updateInterval;
    Behavior *m_behavior;
    Scene *m_scene;
};

#endif /* _LAYER */
