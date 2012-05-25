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

#include "material.h"

Material::Material(QObject *parent)
    : QObject(parent)
    , m_density(0)
    , m_friction(0)
    , m_restitution(0)
{
}

float Material::density() const
{
    return m_density;
}

void Material::setDensity(const float &density)
{
    if (m_density == density)
        return;

    m_density = density;

    emit densityChanged(density);
}

float Material::friction() const
{
    return m_friction;
}

void Material::setFriction(const float &friction)
{
    if (m_friction == friction)
        return;

    m_friction = friction;

    emit frictionChanged(friction);
}

float Material::restitution() const
{
    return m_restitution;
}

void Material::setRestitution(const float &restitution)
{
    if (m_restitution == restitution)
        return;

    m_restitution = restitution;

    emit restitutionChanged(restitution);
}
