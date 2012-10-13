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

#ifndef _BOX2DDEBUGDRAW_H_
#define _BOX2DDEBUGDRAW_H_

#include "quasipainteditem.h"

#include <Box2D/Box2D.h>

#include <QtCore/QtGlobal>

class QPainter;
class Scene;

class Box2DDebugDraw : public QuasiPaintedItem, public b2Draw
{
    Q_OBJECT

public:
    Box2DDebugDraw(Scene *parent = 0);

#if QT_VERSION >= 0x050000
    void paint(QPainter *painter);
#else
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
#endif

    void DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color);
    void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color);
    void DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color);
    void DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color);
    void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color);
    void DrawTransform(const b2Transform &xf);

    void step();

private:
    void draw();

private:
    QPainter *m_painter;
    Scene *m_scene;
};

#endif /* _BOX2DDEBUGDRAW_H_ */
