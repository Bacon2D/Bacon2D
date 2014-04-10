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

#include "plugins.h"

#include "entity.h"
#include "scene.h"
#include "spriteanimation.h"
#include "sprite.h"
#include "imagelayer.h"
#include "game.h"
#include "behavior.h"
#include "scriptbehavior.h"
#include "shape.h"
#include "rectangle.h"
#include "fill.h"
#include "colorfill.h"
#include "triangle.h"
#include "polygon.h"
#include "polyline.h"
#include "circle.h"
#include "line.h"
#include "material.h"

void Plugins::registerTypes(const char *uri)
{
    Q_UNUSED(uri)

    qmlRegisterUncreatableType<Bacon2D>("Bacon2D", 1, 0, "Bacon2D", "Exporting Bacon2D enums to QML");
    qmlRegisterUncreatableType<Layer>("Bacon2D", 1, 0, "Layer", "Registering Layer as we use it on Layers");
    qmlRegisterUncreatableType<Behavior>("Bacon2D", 1, 0, "Bacon2DBehavior", "Don't use Bacon2DBehavior directly, use one specialized behavior");
    qmlRegisterUncreatableType<Shape>("Bacon2D", 1, 0, "Shape", "Don't use Shape directly, use one specialized shape");
    qmlRegisterUncreatableType<Fill>("Bacon2D", 1, 0, "Fill", "Don't use Fill directly, use one specialized fill");

    qmlRegisterType<Game>("Bacon2D", 1, 0, "Game");
    qmlRegisterType<Scene>("Bacon2D", 1, 0, "Scene");
    qmlRegisterType<Entity>("Bacon2D", 1, 0, "Entity");
    qmlRegisterType<Sprite>("Bacon2D", 1, 0, "Sprite");
    qmlRegisterType<SpriteAnimation>("Bacon2D", 1, 0, "SpriteAnimation");
    qmlRegisterType<ImageLayer>("Bacon2D", 1, 0, "ImageLayer");
    qmlRegisterType<ScriptBehavior>("Bacon2D", 1, 0, "ScriptBehavior");
    qmlRegisterType<Rectangle>("Bacon2D", 1, 0, "Box");
    qmlRegisterType<ColorFill>("Bacon2D", 1, 0, "ColorFill");
    qmlRegisterType<Triangle>("Bacon2D", 1, 0, "Triangle");
    qmlRegisterType<Polygon>("Bacon2D", 1, 0, "Polygon");
    qmlRegisterType<Polyline>("Bacon2D", 1, 0, "Polyline");
    qmlRegisterType<Circle>("Bacon2D", 1, 0, "Circle");
    qmlRegisterType<Line>("Bacon2D", 1, 0, "Line");
    qmlRegisterType<Material>("Bacon2D", 1, 0, "Material");
}
