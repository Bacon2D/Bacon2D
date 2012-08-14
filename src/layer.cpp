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

#include "layer.h"

#include <QtCore/QDebug>
#include <QtGui/QPainter>
#if QT_VERSION >= 0x050000
#include <QtQml/QQmlProperty>
#endif

//! Class constructor
Layer::Layer(QuasiDeclarativeItem *parent)
    : QuasiPaintedItem(parent)
    , m_isAnimated(false)
    , m_horizontalStep(1.0)
    , m_type(Quasi::InfiniteType)
{
#if QT_VERSION >= 0x050000
    // this activates the item layered mode
    QQmlProperty(this, "layer.enabled").write(true);
#endif
}

//! Class destructor
Layer::~Layer()
{
}

void Layer::setAnimated(bool animated)
{
    if (m_isAnimated == animated)
        return;

    m_isAnimated = animated;

    emit animatedChanged();
}

void Layer::setHorizontalStep(const qreal &step)
{
    if (m_horizontalStep == step)
        return;

    if ((step > 0 && m_horizontalStep < 0) || (step < 0 && m_horizontalStep > 0))
        emit horizontalDirectionChanged();

    m_horizontalStep = step;

    emit horizontalStepChanged();
}

void Layer::setLayerType(const Quasi::LayerType &type)
{
    if (type == m_type)
        return;

    m_type = type;

    emit layerTypeChanged();
}
