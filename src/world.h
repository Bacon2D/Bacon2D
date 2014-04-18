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

#ifndef _WORLD_H_
#define _WORLD_H_

#include "enums.h"
#include "scene.h"

#include "box2dworld.h"

class World : public Box2DWorld
{
    Q_OBJECT

public:
    World(Scene *parent = 0);
    ~World();

    Scene *scene() const;
    void setScene(Scene *scene);

private:
    Scene *m_scene;
};

#endif /* _WORLD_H_ */
