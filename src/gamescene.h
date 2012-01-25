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

    QDeclarativeListProperty<GameItem> gameItems() const;

    bool running() const;
    void setRunning(const bool &running);

    Q_INVOKABLE QList<QObject *> collidedItems(GameItem *gameItem) const;

public slots:
    void update(const long &delta);

signals:
    void runningChanged();

private:
    static void append_gameItem(QDeclarativeListProperty<GameItem> *list, GameItem *gameItem);
    void checkCollisions();
    bool checkCollision(GameItem *item, GameItem *otherItem) const;

protected:
    QList<GameItem *> m_gameItems;
    bool m_running;
    QVector<QVector<bool> > *m_collisions;
};

#endif /* _GAMESCENE_H_ */
