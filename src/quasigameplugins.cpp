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
