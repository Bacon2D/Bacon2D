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

#include "plugins.h"

#include "entity.h"
#include "enums.h"
#include "scene.h"
#include "spriteanimation.h"
#include "sprite.h"
#include "bacon2dimagelayer.h"
#include "game.h"
#include "viewport.h"
#include "behavior.h"
#include "scriptbehavior.h"
#include "settings.h"

#include "box2dworld.h"
#include "box2dbody.h"
#include "box2ddebugdraw.h"
#include "box2dfixture.h"
#include "box2djoint.h"
#include "box2ddistancejoint.h"
#include "box2dprismaticjoint.h"
#include "box2drevolutejoint.h"
#include "box2dmotorjoint.h"
#include "box2dweldjoint.h"
#include "box2dpulleyjoint.h"
#include "box2dfrictionjoint.h"
#include "box2dwheeljoint.h"
#include "box2dmousejoint.h"
#include "box2dgearjoint.h"
#include "box2dropejoint.h"
#include "box2draycast.h"
#include "box2dcontact.h"
#include "scrollbehavior.h"

#include "tiledscene.h"
#include "tiledlayer.h"
#include "tiledobject.h"

void Plugins::registerTypes(const char *uri)
{
    Q_UNUSED(uri)

    qmlRegisterType<Bacon2DLayer>("Bacon2D", 1, 0, "Layer");
    qmlRegisterUncreatableType<Behavior>("Bacon2D", 1, 0, "Bacon2DBehavior", "Don't use Bacon2DBehavior directly, use one specialized behavior");
    qmlRegisterUncreatableType<Bacon2D>("Bacon2D", 1, 0, "Bacon2D", "Not creatable as an object, use only to access enums");

    qmlRegisterType<Game>("Bacon2D", 1, 0, "Game");
    qmlRegisterType<Scene>("Bacon2D", 1, 0, "Scene");
    qmlRegisterType<Entity>("Bacon2D", 1, 0, "Entity");
    qmlRegisterType<Sprite>("Bacon2D", 1, 0, "Sprite");
    qmlRegisterType<SpriteAnimation>("Bacon2D", 1, 0, "SpriteAnimation");
    qmlRegisterType<Bacon2DImageLayer>("Bacon2D", 1, 0, "ImageLayer");
    qmlRegisterType<Viewport>("Bacon2D", 1, 0, "Viewport");
    qmlRegisterType<ScriptBehavior>("Bacon2D", 1, 0, "ScriptBehavior");
    qmlRegisterType<Settings>("Bacon2D", 1, 0, "Settings");
    qmlRegisterType<ScrollBehavior>("Bacon2D", 1, 0, "ScrollBehavior");



    // For TiledScene
    qmlRegisterType<TiledScene>("Bacon2D", 1, 0, "TiledScene");
    qmlRegisterType<TiledLayer>("Bacon2D", 1, 0, "TiledLayer");
    qmlRegisterType<TiledObject>("Bacon2D", 1, 0, "TiledObject");
    qmlRegisterType<CollisionItem>("Bacon2D", 1, 0, "CollisionItem");


    qmlRegisterUncreatableType<Box2DWorld>("Bacon2D", 1, 0, "World",
                                           QStringLiteral("World created by Scene if physics is enabled"));
    qmlRegisterUncreatableType<Box2DBody>("Bacon2D", 1, 0, "Body",
                                          QStringLiteral("Body is the base class for Entity"));
    qmlRegisterUncreatableType<Box2DFixture>("Bacon2D", 1, 0, "Fixture",
                                             QStringLiteral("Base type for Box, Circle etc."));
    qmlRegisterType<Box2DBody>("Bacon2D", 1, 0, "Body");
    qmlRegisterType<Box2DBox>("Bacon2D", 1, 0, "Box");
    qmlRegisterType<Box2DCircle>("Bacon2D", 1, 0, "Circle");
    qmlRegisterType<Box2DPolygon>("Bacon2D", 1, 0, "Polygon");
    qmlRegisterType<Box2DChain>("Bacon2D", 1, 0, "Chain");
    qmlRegisterType<Box2DEdge>("Bacon2D", 1, 0, "Edge");
    qmlRegisterUncreatableType<Box2DDebugDraw>("Bacon2D", 1, 0, "DebugDraw",
                                               QStringLiteral("DebugDraw created by Scene if physics and debug is enabled"));
    qmlRegisterUncreatableType<Box2DJoint>("Bacon2D", 1, 0, "Joint",
                                           QStringLiteral("Base type for DistanceJoint, RevoluteJoint etc."));
    qmlRegisterType<Box2DDistanceJoint>("Bacon2D", 1, 0, "DistanceJoint");
    qmlRegisterType<Box2DPrismaticJoint>("Bacon2D", 1, 0, "PrismaticJoint");
    qmlRegisterType<Box2DRevoluteJoint>("Bacon2D", 1, 0, "RevoluteJoint");
    qmlRegisterType<Box2DMotorJoint>("Bacon2D", 1, 0, "MotorJoint");
    qmlRegisterType<Box2DWeldJoint>("Bacon2D", 1, 0, "WeldJoint");
    qmlRegisterType<Box2DPulleyJoint>("Bacon2D", 1, 0, "PulleyJoint");
    qmlRegisterType<Box2DFrictionJoint>("Bacon2D", 1, 0, "FrictionJoint");
    qmlRegisterType<Box2DWheelJoint>("Bacon2D", 1, 0, "WheelJoint");
    qmlRegisterType<Box2DMouseJoint>("Bacon2D", 1, 0, "MouseJoint");
    qmlRegisterType<Box2DGearJoint>("Bacon2D", 1, 0, "GearJoint");
    qmlRegisterType<Box2DRopeJoint>("Bacon2D", 1, 0, "RopeJoint");
    qmlRegisterType<Box2DRayCast>("Bacon2D", 1, 0, "RayCast");

    qmlRegisterUncreatableType<Box2DContact>("Bacon2D", 1, 0, "Contact", QStringLiteral("Contact class"));
}
