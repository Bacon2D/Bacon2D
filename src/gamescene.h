#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include <QtCore/QList>
#include <QtDeclarative>

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

public slots:
    void update(long delta);

signals:
    void runningChanged();

private:
    static void append_gameItem(QDeclarativeListProperty<GameItem> *list, GameItem *gameItem);

    QList<GameItem *> m_gameItems;
    bool m_running;
};

#endif /* _GAMESCENE_H_ */
