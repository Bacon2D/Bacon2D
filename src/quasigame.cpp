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
    , m_timerId(0)
{
    m_gameTime.start();
    m_timerId = startTimer(1000 / m_fps);
}

GameScene *QuasiGame::currentScene() const {
    return m_currentScene;
}

void QuasiGame::setCurrentScene(GameScene *currentScene) {
    if (m_currentScene != currentScene) {
        if (m_currentScene) {
            if (m_viewport) {
                m_viewport->setVisible(false);
                m_viewport = 0;
            }

            m_currentScene->setRunning(false);
            m_currentScene->setVisible(false);
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
            } else {
                m_currentScene->setParentItem(this);
            }

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

void QuasiGame::timerEvent(QTimerEvent *event)
{
    update();
}

void QuasiGame::update()
{
    long elapsedTime = m_gameTime.restart();
    if (m_currentScene)
        m_currentScene->update(elapsedTime);
    if (m_viewport)
        m_viewport->update(elapsedTime);
}

QPointF QuasiGame::mouse() const
{
    return m_currentScene->mapFromItem(this, canvas()->mapFromGlobal(QCursor::pos()));
}
