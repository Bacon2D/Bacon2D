#include "quasigameplugins.h"

#include "quasigame.h"
#include "gamescene.h"
#include "gameitem.h"
#include "gamesprite.h"
#include "spriteanimation.h"
#include "spriteanimationitem.h"
#include "spriteitem.h"
#include "box2dscene.h"
#include "box2ditem.h"
#include "box2ddistancejointitem.h"
#include "box2dmousejointitem.h"
#include "gamestaticbackground.h"
#include "gameanimatedbackground.h"
#include "viewport.h"

void QuasiGamePlugins::registerTypes(const char *uri)
{
    qmlRegisterType<QuasiGame>("QuasiGame", 1, 0, "QuasiGame");
    qmlRegisterType<GameScene>("QuasiGame", 1, 0, "GameScene");
    qmlRegisterType<GameItem>("QuasiGame", 1, 0, "GameItem");
    qmlRegisterType<GameSprite>("QuasiGame", 1, 0, "GameSprite");
    qmlRegisterType<SpriteAnimation>("QuasiGame", 1, 0, "SpriteAnimation");
    qmlRegisterType<SpriteItem>("QuasiGame", 1, 0, "SpriteItem");
    qmlRegisterType<SpriteAnimationItem>("QuasiGame", 1, 0, "SpriteAnimationItem");
    qmlRegisterType<Box2DScene>("QuasiGame", 1, 0, "Box2DScene");
    qmlRegisterType<Box2DItem>("QuasiGame", 1, 0, "Box2DItem");
    qmlRegisterType<Box2DDistanceJointItem>("QuasiGame", 1, 0, "Box2DDistanceJointItem");
    qmlRegisterType<Box2DMouseJointItem>("QuasiGame", 1, 0, "Box2DMouseJointItem");
    qmlRegisterType<GameStaticBackground>("QuasiGame", 1, 0, "GameStaticBackground"); // Use StaticBackground on QML
    qmlRegisterType<GameAnimatedBackground>("QuasiGame", 1, 0, "GameAnimatedBackground"); // Use AnimatedBackground on QML
    qmlRegisterType<GameBaseBackground>("QuasiGame", 1, 0, "GameBaseBackground");
    qmlRegisterType<GameAnimatedBackground>("QuasiGame", 1, 0, "GameAnimatedBackground");
    qmlRegisterType<Viewport>("QuasiGame", 1, 0, "Viewport");
}

Q_EXPORT_PLUGIN2(QuasiGame, QuasiGamePlugins);
