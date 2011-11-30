#ifndef _QUASIGAMEPLUGINS_H_
#define _QUASIGAMEPLUGINS_H_

#include <QtDeclarative/QDeclarativeExtensionPlugin>

#include "quasigame.h"
#include "gamescene.h"
#include "gameitem.h"

class GameItemPlugin : public  QDeclarativeExtensionPlugin
{
    Q_OBJECT

public:
    void registerTypes(const char *uri)
    {
        qmlRegisterType<QuasiGame>(uri, 1, 0, "QuasiGame");
        qmlRegisterType<GameScene>(uri, 1, 0, "GameScene");
        qmlRegisterType<GameItem>(uri, 1, 0, "GameItem");
    }
};

Q_EXPORT_PLUGIN2(qmlgameitemplugin, GameItemPlugin);

#endif /* _QUASIGAMEPLUGINS_H_ */

