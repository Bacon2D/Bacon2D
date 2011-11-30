#ifndef _QUASIGAME_H_
#define _QUASIGAME_H_

#include <QtDeclarative>

class GameScene;

class QuasiGame : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(GameScene *currentScene READ currentScene WRITE setCurrentScene NOTIFY currentSceneChanged)

public:
    QuasiGame(QQuickItem *parent = 0);

    GameScene *currentScene() const;
    void setCurrentScene(GameScene *currentScene);

signals:
    void update(long delta);
    void currentSceneChanged();

private:
    GameScene *m_currentScene;
};

#endif /* _QUASIGAME_H_ */
