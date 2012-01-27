#include "quasigame.h"

#include <QQuickCanvas>
#include <QCursor>

#include "gamescene.h"
#include "viewport.h"

QuasiGame::QuasiGame(QQuickItem *parent)
    : QQuickItem(parent)
    , m_currentScene(0)
    , m_fps(DEFAULT_FPS)
    , m_viewport(0)
{
    connect(&m_updateTimer, SIGNAL(timeout()), this, SLOT(onUpdate()));
    m_gameTime.start();
    m_updateTimer.start(1000 / m_fps);
}

GameScene *QuasiGame::currentScene() const {
    return m_currentScene;
}

void QuasiGame::setCurrentScene(GameScene *currentScene) {
    if (m_currentScene != currentScene) {
        if (m_currentScene) {
            if (m_viewport) {
                m_viewport->setVisible(false);
                m_viewport->disconnect(SIGNAL(update(const long &)));
                m_viewport = 0;
            }

            m_currentScene->setRunning(false);
            m_currentScene->setVisible(false);
            m_currentScene->disconnect(SIGNAL(update(const long &)));
        }

        m_currentScene = currentScene;

        if (m_currentScene) {
            m_currentScene->setGame(this);

            if ((m_viewport = m_currentScene->viewport())) {
                m_viewport->setParentItem(this);
                m_viewport->setScene(m_currentScene);
                m_viewport->setWidth(width());
                m_viewport->setHeight(height());
                m_viewport->setContentWidth(m_currentScene->width());
                m_viewport->setContentHeight(m_currentScene->height());
                m_viewport->updateMaxOffsets();
                m_viewport->setVisible(true);

                m_currentScene->setParentItem(m_viewport);

                connect(this, SIGNAL(update(const long &)), m_viewport, SLOT(update(const long &)));
            } else {
                m_currentScene->setParentItem(this);
            }

            connect(this, SIGNAL(update(const long &)), m_currentScene, SLOT(update(const long &)));
            m_currentScene->setVisible(true);
            m_currentScene->setRunning(true);
        }

        emit currentSceneChanged();
    }
}

int QuasiGame::fps() const
{
    return m_fps;
}

void QuasiGame::setFps(const int &fps)
{
    if (m_fps != fps) {
        m_fps = fps;

        emit fpsChanged();
    }
}

void QuasiGame::onUpdate()
{
    long elapsedTime = m_gameTime.restart();
    emit update(elapsedTime);
}

QPointF QuasiGame::mouse() const
{
    return m_currentScene->mapFromItem(this, canvas()->mapFromGlobal(QCursor::pos()));
}
