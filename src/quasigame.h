#ifndef _QUASIGAME_H_
#define _QUASIGAME_H_

#include <QtCore/QTimer>
#include <QtCore/QTime>
#include <QtDeclarative>

class GameScene;

class QuasiGame : public QQuickItem
{
    Q_OBJECT

    enum { DEFAULT_FPS = 60 };

    Q_PROPERTY(GameScene *currentScene READ currentScene WRITE setCurrentScene NOTIFY currentSceneChanged)
    Q_PROPERTY(int fps READ fps WRITE setFps NOTIFY fpsChanged)

public:
    QuasiGame(QQuickItem *parent = 0);

    GameScene *currentScene() const;
    void setCurrentScene(GameScene *currentScene);

    int fps() const;
    void setFps(int fps);

public slots:
    void update();

signals:
    void update(long delta);
    void currentSceneChanged();
    void fpsChanged();

private:
    GameScene *m_currentScene;
    QTimer m_updateTimer;
    QTime m_gameTime;
    int m_fps;
};

#endif /* _QUASIGAME_H_ */
