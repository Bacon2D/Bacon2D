/**
 * Copyright (C) 2012 by INdT
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

#include "enums.h"
#include "entity.h"
#include "quasipainteditem.h"

#include <QtCore/QList>
#include <QtCore/QString>

class Offsets {
public:
    typedef QList<Offsets> OffsetsList;

    Offsets() { m_point = m_size = 0; }
    Offsets(int point, int size)
    {
        m_point = point;
        m_size = size;
    }
    ~Offsets() {}

    int point() const { return m_point; }
    void setPoint(int point)
    {
        if (point != m_point)
            m_point = point;
    }

    int size() const { return m_size; }
    void setSize(int size)
    {
        if (size != m_size)
            m_size = size;
    }
    bool operator==(const Offsets &other) const {
        return ((this->point() == other.point())
                && (this->size() == other.size()));
    }

private:
    int m_point;
    int m_size;
};

//! A layer class
class Layer: public QuasiPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(bool animated READ isAnimated WRITE setAnimated NOTIFY animatedChanged)
    Q_PROPERTY(qreal horizontalStep READ horizontalStep WRITE setHorizontalStep NOTIFY horizontalStepChanged)
    Q_PROPERTY(Quasi::LayerType layerType READ layerType WRITE setLayerType NOTIFY layerTypeChanged)

public:
    Layer(QuasiDeclarativeItem *parent = 0);
    virtual ~Layer();

    bool isAnimated() const { return m_isAnimated; }
    void setAnimated(bool animated);

    qreal horizontalStep() const { return m_horizontalStep; }
    void setHorizontalStep(const qreal &step);

    Quasi::LayerType layerType() const { return m_type; };
    void setLayerType(const Quasi::LayerType &type);

signals:
    void animatedChanged();
    void horizontalStepChanged();
    void horizontalDirectionChanged();
    void layerTypeChanged();

protected:
    bool m_isAnimated;
    qreal m_horizontalStep;
    Quasi::LayerType m_type;
};

#endif /* _LAYER */
