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

#include "entity.h"

/*!
  \qmltype Layer
  \inqmlmodule Bacon2D
  \brief Is the base component providing common properties and functionality
   needed by other Layer types.  See \l ImageLayer.
*/
Layer::Layer(QQuickItem *parent)
    : QQuickItem(parent)
    , m_type(Layer::Infinite)
    , m_updateInterval(0)
    , m_behavior(0)
    , m_scene(0)
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

Behavior *Layer::behavior() const
{
    return m_behavior;
}

void Layer::setBehavior(Behavior *behavior)
{
    if (m_behavior == behavior)
        return;

    m_behavior = behavior;

    emit behaviorChanged();
}

Scene *Layer::scene() const
{
    return m_scene;
}

void Layer::setScene(Scene *scene)
{
    if (m_scene == scene)
        return;

    m_scene = scene;

    emit sceneChanged();
}

Game *Layer::game() const
{
    if (m_scene)
        return m_scene->game();

    return 0;
}

int Layer::updateInterval() const
{
    return m_updateInterval;
}

void Layer::setUpdateInterval(const int &updateInterval)
{
    if (m_updateInterval == updateInterval)
        return;

    m_updateInterval = updateInterval;

    emit updateIntervalChanged();

    m_updateTime.restart();
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
    QQuickItem *item;
    foreach (item, childItems()) {
        if (Entity *entity = qobject_cast<Entity *>(item))
            entity->update(delta);
    }
}
