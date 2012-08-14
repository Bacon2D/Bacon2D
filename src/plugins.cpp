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

#include "box2ddistancejointitem.h"
#include "box2dmousejointitem.h"
#include "box2dcontact.h"
#include "entity.h"
#include "scene.h"
#include "spriteanimation.h"
#include "sprite.h"
#include "imagelayer.h"
#include "game.h"
#include "viewport.h"
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
#include "fixture.h"
#include "material.h"

void Plugins::registerTypes(const char *uri)
{
    Q_UNUSED(uri)

    qmlRegisterUncreatableType<Quasi>("QuasiGame", 1, 0, "Quasi", "Exporting Quasi enums to QML");
    qmlRegisterUncreatableType<Layer>("QuasiGame", 1, 0, "Layer", "Registering Layer as we use it on QuasiLayers");
    qmlRegisterUncreatableType<Box2DContact>("QuasiGame", 1, 0, "Contact", "This type is used to control scene's (pre)contact event");
    qmlRegisterUncreatableType<Behavior>("QuasiGame", 1, 0, "QuasiBehavior", "Don't use QuasiBehavior directly, use one specialized behavior");
    qmlRegisterUncreatableType<Shape>("QuasiGame", 1, 0, "QuasiShape", "Don't use QuasiShape directly, use one specialized shape");
    qmlRegisterUncreatableType<Fill>("QuasiGame", 1, 0, "QuasiFill", "Don't use QuasiFill directly, use one specialized fill");

    qmlRegisterType<Game>("QuasiGame", 1, 0, "QuasiGame");
    qmlRegisterType<Scene>("QuasiGame", 1, 0, "QuasiScene");
    qmlRegisterType<Entity>("QuasiGame", 1, 0, "QuasiEntity");
    qmlRegisterType<Sprite>("QuasiGame", 1, 0, "QuasiSprite");
    qmlRegisterType<SpriteAnimation>("QuasiGame", 1, 0, "QuasiSpriteAnimation");
    qmlRegisterType<Box2DDistanceJointItem>("QuasiGame", 1, 0, "QuasiDistanceJoint");
    qmlRegisterType<Box2DMouseJointItem>("QuasiGame", 1, 0, "QuasiMouseJoint");
    qmlRegisterType<ImageLayer>("QuasiGame", 1, 0, "QuasiImageLayer");
    qmlRegisterType<Viewport>("QuasiGame", 1, 0, "QuasiViewport");
    qmlRegisterType<ScriptBehavior>("QuasiGame", 1, 0, "QuasiScriptBehavior");
    qmlRegisterType<Rectangle>("QuasiGame", 1, 0, "QuasiRectangle");
    qmlRegisterType<ColorFill>("QuasiGame", 1, 0, "QuasiColorFill");
    qmlRegisterType<Triangle>("QuasiGame", 1, 0, "QuasiTriangle");
    qmlRegisterType<Polygon>("QuasiGame", 1, 0, "QuasiPolygon");
    qmlRegisterType<Polyline>("QuasiGame", 1, 0, "QuasiPolyline");
    qmlRegisterType<Circle>("QuasiGame", 1, 0, "QuasiCircle");
    qmlRegisterType<Line>("QuasiGame", 1, 0, "QuasiLine");
    qmlRegisterType<Material>("QuasiGame", 1, 0, "QuasiMaterial");
    qmlRegisterType<Fixture>("QuasiGame", 1, 0, "QuasiFixture");
}

Q_EXPORT_PLUGIN2(QuasiGame, Plugins);
