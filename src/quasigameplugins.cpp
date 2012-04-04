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

#include "quasigameplugins.h"

#include "quasigame.h"
#include "gamescene.h"
#include "gameitem.h"
#include "spriteanimationitem.h"
#include "spriteitem.h"
#include "box2dscene.h"
#include "box2ditem.h"
#include "box2ddistancejointitem.h"
#include "box2dmousejointitem.h"
#include "gamelayers.h"
#include "staticlayer.h"
#include "animatedlayer.h"
#include "viewport.h"

void QuasiGamePlugins::registerTypes(const char *uri)
{
    qmlRegisterUncreatableType<Quasi>("QuasiGame", 1, 0, "Quasi", "Exporting Quasi enums to QML");

    qmlRegisterType<QuasiGame>("QuasiGame", 1, 0, "QuasiGame");
    qmlRegisterType<GameScene>("QuasiGame", 1, 0, "QuasiScene");
    qmlRegisterType<GameItem>("QuasiGame", 1, 0, "QuasiEntity");
    qmlRegisterType<SpriteItem>("QuasiGame", 1, 0, "QuasiSprite");
    qmlRegisterType<SpriteAnimationItem>("QuasiGame", 1, 0, "QuasiAnimation");
    qmlRegisterType<Box2DScene>("QuasiGame", 1, 0, "QuasiPhysicsScene");
    qmlRegisterType<Box2DItem>("QuasiGame", 1, 0, "QuasiBody");
    qmlRegisterType<Box2DDistanceJointItem>("QuasiGame", 1, 0, "QuasiDistanceJoint");
    qmlRegisterType<Box2DMouseJointItem>("QuasiGame", 1, 0, "QuasiMouseJoint");
    qmlRegisterType<GameLayers>("QuasiGame", 1, 0, "QuasiLayers");
    qmlRegisterType<Layer>("QuasiGame", 1, 0, "Layer"); // this is neede for any sort of Layers
    qmlRegisterType<StaticLayer>("QuasiGame", 1, 0, "QuasiStaticLayer");
    qmlRegisterType<AnimatedLayer>("QuasiGame", 1, 0, "QuasiAnimatedLayer");
    qmlRegisterType<Viewport>("QuasiGame", 1, 0, "QuasiViewport");
}

Q_EXPORT_PLUGIN2(QuasiGame, QuasiGamePlugins);
