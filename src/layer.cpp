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

#include "layer.h"

#include <QtQml/QQmlProperty>


/*!
  \qmltype Layer
  \inqmlmodule Bacon2D
  \brief Is the base component providing common properties and functionality
   needed by other Layer types.  See \l ImageLayer.
*/
Layer::Layer(QQuickItem *parent)
    : Entity(parent)
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

void Layer::update(const int &delta)
{
    if ((m_updateInterval && m_updateTime.elapsed() >= m_updateInterval)
        || !m_updateInterval) {
        m_updateTime.restart();
        if (m_behavior) {
            m_behavior->setDelta(delta);
            m_behavior->setTarget(this);
            m_behavior->update(delta);
        }
    }

    updateEntities(delta);
}

void Layer::updateEntities(const int &delta)
{
    Entity *item;
    foreach (item, findChildren<Entity*>(QString(),Qt::FindDirectChildrenOnly)) {
        item->update(delta);
    }
}
