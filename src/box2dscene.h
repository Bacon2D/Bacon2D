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

#ifndef _BOX2DSCENE_H_
#define _BOX2DSCENE_H_

#include "gamescene.h"

class b2World;
class QuasiGame;
class Box2DDebugDrawItem;

class Box2DScene : public GameScene
{
    Q_OBJECT

public:
    Box2DScene(QuasiGame *parent = 0);

    b2World *world() const;

    void setGravity(const QPointF &gravity);
    QPointF gravity() const;

    void componentComplete();

    void update(const long &delta);

protected slots:
    void onDebugChanged();

private:
    b2World *m_world;
    QPointF m_gravity;
    Box2DDebugDrawItem *m_debugDraw;
};

#endif /* _BOX2DSCENE_H_ */
