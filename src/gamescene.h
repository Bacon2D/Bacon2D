#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include <QtCore/QList>
#include <QtCore/QVector>
#include <QtQuick/QQuickItem>

#include "gameitem.h"

class QuasiGame;
class Viewport;

class GameScene : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QDeclarativeListProperty<GameItem> gameItems READ gameItems)
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(Viewport *viewport READ viewport WRITE setViewport NOTIFY viewportChanged)
    Q_PROPERTY(QuasiGame *game READ game WRITE setGame)

public:
    GameScene(QuasiGame *parent = 0);

    QDeclarativeListProperty<GameItem> gameItems() const;

    bool running() const;
    void setRunning(const bool &running);

    Viewport *viewport() const;
    void setViewport(Viewport *viewport);

    QuasiGame *game() const;
    void setGame(QuasiGame *game);

    Q_INVOKABLE QList<QObject *> collidedItems(GameItem *gameItem) const;

public slots:
    void update(const long &delta);

signals:
    void runningChanged();
    void viewportChanged();

private:
    static void append_gameItem(QDeclarativeListProperty<GameItem> *list, GameItem *gameItem);
    void checkCollisions();
    bool checkCollision(GameItem *item, GameItem *otherItem) const;

protected:
    QList<GameItem *> m_gameItems;
    bool m_running;
    QVector<QVector<bool> > *m_collisions;
    Viewport *m_viewport;
    QuasiGame *m_game;
};

#endif /* _GAMESCENE_H_ */
