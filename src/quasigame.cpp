#include "quasigame.h"
#include "gamescene.h"

QuasiGame::QuasiGame(QQuickItem *parent)
    : QQuickItem(parent),
      m_currentScene(0)
{
}

GameScene *QuasiGame::currentScene() const {
    return m_currentScene;
}

void QuasiGame::setCurrentScene(GameScene *currentScene) {
    if (m_currentScene)
        disconnect(SIGNAL(update(long)));

    m_currentScene = currentScene;

    if (m_currentScene)
        connect(this, SIGNAL(update(long)), m_currentScene, SLOT(update(long)));

    emit currentSceneChanged();
}
