#include "gamescene.h"

GameScene::GameScene(QQuickItem *parent)
    : QQuickItem(parent)
{
}

QDeclarativeListProperty<GameItem> GameScene::gameItems()
{
    return QDeclarativeListProperty<GameItem>(this, m_gameItems);
}

void GameScene::update(long delta)
{
}
