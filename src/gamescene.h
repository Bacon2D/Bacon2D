#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include <QtCore/QList>
#include <QtCore/QVector>
#include <QtQuick/QQuickItem>

#include "gameitem.h"

class GameScene : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QDeclarativeListProperty<GameItem> gameItems READ gameItems)
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)

public:
    GameScene(QQuickItem *parent = 0);

    QDeclarativeListProperty<GameItem> gameItems();

    bool running() const;
    void setRunning(bool running);

    Q_INVOKABLE QList<QObject *> collidedItems(GameItem *gameItem);

public slots:
    void update(long delta);

signals:
    void runningChanged();
    void gameItemAdded(GameItem *gameItem);

private:
    static void append_gameItem(QDeclarativeListProperty<GameItem> *list, GameItem *gameItem);
    void checkCollisions();
    bool checkCollision(GameItem *item, GameItem *otherItem);

protected:
    QList<GameItem *> m_gameItems;
    bool m_running;
    QVector<QVector<bool> > *m_collisions;
};

#endif /* _GAMESCENE_H_ */
