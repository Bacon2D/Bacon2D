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

#include "layer.h"

#include <QtQml/QQmlProperty>

/*!
  \qmltype Layer
  \inqmlmodule Bacon2D
  \brief Is the base component providing common properties and functionality
   needed by other Layer types.  See \l ImageLayer.
*/
Layer::Layer(QQuickItem *parent)
    : QQuickItem(parent)
    , m_isAnimated(false)
    , m_horizontalStep(1.0)
    , m_type(Layer::Infinite)
{
    // this activates the item layered mode
    QQmlProperty(this, "layer.enabled").write(true);
}

//! Class destructor
Layer::~Layer()
{
}

/*!
  \qmlproperty bool Layer::animated
  \brief This property represents the current state of the Layer's animation.
*/
void Layer::setAnimated(bool animated)
{
    if (m_isAnimated == animated)
        return;

    m_isAnimated = animated;

    emit animatedChanged();
}

/*!
  \qmlproperty qreal Layer::horizontalStep
  \brief This property holds the distance to move horizontally in each 
   step of the animation
*/
void Layer::setHorizontalStep(const qreal &step)
{
    if (m_horizontalStep == step)
        return;

    if ((step > 0 && m_horizontalStep < 0) || (step < 0 && m_horizontalStep > 0))
        emit horizontalDirectionChanged();

    m_horizontalStep = step;

    emit horizontalStepChanged();
}

/*!
  \qmlproperty enumeration Layer::layerType
  \table
  \header
    \li {2, 1} \e {Layer::LayerType} is an enumeration:
  \header
    \li Type
    \li Description
  \row
    \li Layer.Infinite (default)
    \li Infinite Layer
  \row
    \li Layer.Mirrored
    \li Mirrored Layer
  \endtable
*/
void Layer::setLayerType(const Layer::LayerType &type)
{
    if (type == m_type)
        return;

    m_type = type;

    emit layerTypeChanged();
}

void Layer::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
}
