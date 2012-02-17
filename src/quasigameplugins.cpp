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
#include "gamestaticbackground.h"
#include "gameanimatedbackground.h"
#include "viewport.h"

void QuasiGamePlugins::registerTypes(const char *uri)
{
    qmlRegisterType<QuasiGame>("QuasiGame", 1, 0, "QuasiGame");
    qmlRegisterType<GameScene>("QuasiGame", 1, 0, "QuasiScene");
    qmlRegisterType<GameItem>("QuasiGame", 1, 0, "QuasiEntity");
    qmlRegisterType<SpriteItem>("QuasiGame", 1, 0, "QuasiSprite");
    qmlRegisterType<SpriteAnimationItem>("QuasiGame", 1, 0, "QuasiAnimation");
    qmlRegisterType<Box2DScene>("QuasiGame", 1, 0, "QuasiPhysicsScene");
    qmlRegisterType<Box2DItem>("QuasiGame", 1, 0, "QuasiBody");
    qmlRegisterType<Box2DDistanceJointItem>("QuasiGame", 1, 0, "QuasiDistanceJoint");
    qmlRegisterType<Box2DMouseJointItem>("QuasiGame", 1, 0, "QuasiMouseJoint");
    qmlRegisterType<GameStaticBackground>("QuasiGame", 1, 0, "GameStaticBackground"); // Use StaticBackground on QML
    qmlRegisterType<GameAnimatedBackground>("QuasiGame", 1, 0, "GameAnimatedBackground"); // Use AnimatedBackground on QML
    qmlRegisterType<GameBaseBackground>("QuasiGame", 1, 0, "GameBaseBackground");
    qmlRegisterType<GameAnimatedBackground>("QuasiGame", 1, 0, "GameAnimatedBackground");
    qmlRegisterType<Viewport>("QuasiGame", 1, 0, "QuasiViewport");
}

Q_EXPORT_PLUGIN2(QuasiGame, QuasiGamePlugins);
