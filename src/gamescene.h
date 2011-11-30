#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include <QtCore/QList>
#include <QtDeclarative>

#include "gameitem.h"

class GameScene : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QDeclarativeListProperty<GameItem> gameItems READ gameItems)

public:
    GameScene(QQuickItem *parent = 0);

    QDeclarativeListProperty<GameItem> gameItems();

public slots:
    void update(long delta);

private:
    QList<GameItem *> m_gameItems;
};

#endif /* _GAMESCENE_H_ */
