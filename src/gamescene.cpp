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
    if (!m_running) // TODO: stop Qt animations as well
        return;

    GameItem *item;

    foreach (item, m_gameItems)
        item->update(delta);
}

bool GameScene::running() const
{
    return m_running;
}

void GameScene::setRunning(bool running)
{
    m_running = running;

    emit runningChanged();
}
