#include "quasigameplugins.h"

#include "quasigame.h"
#include "gamescene.h"
#include "gameitem.h"
#include "gamesprite.h"
#include "spriteanimation.h"
#include "spriteanimationitem.h"
#include "spriteitem.h"

void QuasiGamePlugins::registerTypes(const char *uri)
{
    qmlRegisterType<QuasiGame>("QuasiGame", 1, 0, "QuasiGame");
    qmlRegisterType<GameScene>("QuasiGame", 1, 0, "GameScene");
    qmlRegisterType<GameItem>("QuasiGame", 1, 0, "GameItem");
    qmlRegisterType<GameSprite>("QuasiGame", 1, 0, "GameSprite");
    qmlRegisterType<SpriteAnimation>("QuasiGame", 1, 0, "SpriteAnimation");
    qmlRegisterType<SpriteItem>("QuasiGame", 1, 0, "SpriteItem");
    qmlRegisterType<SpriteAnimationItem>("QuasiGame", 1, 0, "SpriteAnimationItem");
}

Q_EXPORT_PLUGIN2(QuasiGame, QuasiGamePlugins);
