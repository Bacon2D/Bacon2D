/**
 * Copyright (C) 2012 by INdT
 * Copyright (C) 2014 Bacon2D Project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * @author Rodrigo Goncalves de Oliveira <rodrigo.goncalves@openbossa.org>
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

#ifndef _LAYER_H_
#define _LAYER_H_

#include "entity.h"

#include <QtQuick/QQuickItem>

//! A layer class
class Layer: public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(bool animated READ isAnimated WRITE setAnimated NOTIFY animatedChanged)
    Q_PROPERTY(qreal horizontalStep READ horizontalStep WRITE setHorizontalStep NOTIFY horizontalStepChanged)
    Q_PROPERTY(Layer::LayerType layerType READ layerType WRITE setLayerType NOTIFY layerTypeChanged)

    Q_ENUMS (
        LayerType
    )

public:
    Layer(QQuickItem *parent = 0);
    virtual ~Layer();

    bool isAnimated() const { return m_isAnimated; }
    void setAnimated(bool animated);

    qreal horizontalStep() const { return m_horizontalStep; }
    void setHorizontalStep(const qreal &step);

    enum LayerType {
        Infinite,
        Mirrored
    };

    Layer::LayerType layerType() const { return m_type; };
    void setLayerType(const Layer::LayerType &type);

signals:
    void animatedChanged();
    void horizontalStepChanged();
    void horizontalDirectionChanged();
    void layerTypeChanged();

protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

    bool m_isAnimated;
    qreal m_horizontalStep;
    Layer::LayerType m_type;
};

#endif /* _LAYER */
