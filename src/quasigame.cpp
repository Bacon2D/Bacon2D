#include "quasigame.h"
#include "gamescene.h"

QuasiGame::QuasiGame(QQuickItem *parent)
    : QQuickItem(parent),
      m_currentScene(0),
      m_fps(DEFAULT_FPS)
{
    connect(&m_updateTimer, SIGNAL(timeout()), this, SLOT(onUpdate()));
    m_gameTime.start();
    m_updateTimer.start(1000 / m_fps);
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

int QuasiGame::fps() const
{
    return m_fps;
}

void QuasiGame::setFps(int fps)
{
    m_fps = fps;

    emit fpsChanged();
}

void QuasiGame::onUpdate()
{
    long elapsedTime = m_gameTime.restart();
    emit update(elapsedTime);
}
