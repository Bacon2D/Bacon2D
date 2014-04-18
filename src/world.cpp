/**
 * Copyright (C) 2014 by Ken VanDine
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
 * @author Ken VanDine <ken@vandine.org>
 */

#include "world.h"

#include "enums.h"

World::World(Scene *parent)
    : Box2DWorld(parent)
    , m_scene(0)
{
}

World::~World()
{
}

Scene *World::scene() const
{
    return m_scene;
}

void World::setScene(Scene *scene)
{
    m_scene = scene;
}
