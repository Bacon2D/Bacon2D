#ifndef _QUASIGAME_H_
#define _QUASIGAME_H_

#include <QtCore/QTime>
#include <QtQuick/QQuickItem>

class GameScene;
class Viewport;

class QuasiGame : public QQuickItem
{
    Q_OBJECT

    enum { DEFAULT_FPS = 60 };

    Q_PROPERTY(GameScene *currentScene READ currentScene WRITE setCurrentScene NOTIFY currentSceneChanged)
    Q_PROPERTY(int fps READ fps WRITE setFps NOTIFY fpsChanged)
    Q_PROPERTY(QPointF mouse READ mouse)

public:
    QuasiGame(QQuickItem *parent = 0);

    GameScene *currentScene() const;
    void setCurrentScene(GameScene *currentScene);

    int fps() const;
    void setFps(const int &fps);

    QPointF mouse() const;

protected:
    void timerEvent(QTimerEvent *event);
    void update();

signals:
    void currentSceneChanged();
    void fpsChanged();

private:
    GameScene *m_currentScene;
    QTime m_gameTime;
    int m_fps;
    Viewport *m_viewport;
    int m_timerId;
};

#endif /* _QUASIGAME_H_ */
