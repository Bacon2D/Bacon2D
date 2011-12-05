#include "quasigameplugins.h"

void QuasiGamePlugins::registerTypes(const char *uri)
{
    qmlRegisterType<QuasiGame>("QuasiGame", 1, 0, "QuasiGame");
    qmlRegisterType<GameScene>("QuasiGame", 1, 0, "GameScene");
    qmlRegisterType<GameItem>("QuasiGame", 1, 0, "GameItem");
}

Q_EXPORT_PLUGIN2(QuasiGame, QuasiGamePlugins);
