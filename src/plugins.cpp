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
#include "box2dcontact.h"

void Plugins::registerTypes(const char *uri)
{
    Q_UNUSED(uri)

    qmlRegisterUncreatableType<Bacon2D>("Bacon2D", 1, 0, "Bacon2D", "Exporting Bacon2D enums to QML");
    qmlRegisterUncreatableType<Layer>("Bacon2D", 1, 0, "Layer", "Registering Layer as we use it on Layers");
    qmlRegisterUncreatableType<Behavior>("Bacon2D", 1, 0, "Bacon2DBehavior", "Don't use Bacon2DBehavior directly, use one specialized behavior");

    qmlRegisterType<Game>("Bacon2D", 1, 0, "Game");
    qmlRegisterType<Scene>("Bacon2D", 1, 0, "Scene");
    qmlRegisterType<Entity>("Bacon2D", 1, 0, "Entity");
    qmlRegisterType<Sprite>("Bacon2D", 1, 0, "Sprite");
    qmlRegisterType<SpriteAnimation>("Bacon2D", 1, 0, "SpriteAnimation");
    qmlRegisterType<ImageLayer>("Bacon2D", 1, 0, "ImageLayer");
    qmlRegisterType<ScriptBehavior>("Bacon2D", 1, 0, "ScriptBehavior");

    qmlRegisterType<Box2DWorld>("Bacon2D", 1, 0, "World");
    qmlRegisterType<Box2DBody>("Bacon2D", 1, 0, "Body");
    qmlRegisterUncreatableType<Box2DFixture>("Bacon2D", 1,0, "Fixture",
                                             QStringLiteral("Base type for Box, Circle etc."));
    qmlRegisterType<Box2DBox>("Bacon2D", 1, 0, "Box");
    qmlRegisterType<Box2DCircle>("Bacon2D", 1, 0, "Circle");
    qmlRegisterType<Box2DPolygon>("Bacon2D", 1, 0, "Polygon");
    qmlRegisterType<Box2DChain>("Bacon2D", 1, 0, "Chain");
    qmlRegisterType<Box2DEdge>("Bacon2D", 1, 0, "Edge");
    qmlRegisterType<Box2DDebugDraw>("Bacon2D", 1, 0, "DebugDraw");
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

    qmlRegisterUncreatableType<Box2DContact>("Bacon2D", 1,0, "Contact",QStringLiteral("Contact class"));
}
