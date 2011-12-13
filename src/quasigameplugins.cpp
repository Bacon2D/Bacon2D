#include "quasigameplugins.h"

#include "quasigame.h"
#include "gamescene.h"
#include "gameitem.h"
#include "gamesprite.h"

void QuasiGamePlugins::registerTypes(const char *uri)
{
    qmlRegisterType<QuasiGame>("QuasiGame", 1, 0, "QuasiGame");
    qmlRegisterType<GameScene>("QuasiGame", 1, 0, "GameScene");
    qmlRegisterType<GameItem>("QuasiGame", 1, 0, "GameItem");
    qmlRegisterType<GameSprite>("QuasiGame", 1, 0, "GameSprite");
}

Q_EXPORT_PLUGIN2(QuasiGame, QuasiGamePlugins);
