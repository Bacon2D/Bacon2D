#include "gamescene.h"

void GameScene::append_gameItem(QDeclarativeListProperty<GameItem> *list, GameItem *gameItem)
{
    GameScene *scene = qobject_cast<GameScene *>(list->object);
    if (scene) {
        gameItem->setParentItem(scene);
        scene->m_gameItems.append(gameItem);
    }
}

GameScene::GameScene(QQuickItem *parent)
    : QQuickItem(parent)
{
}

QDeclarativeListProperty<GameItem> GameScene::gameItems()
{
    return QDeclarativeListProperty<GameItem>(this, 0, &GameScene::append_gameItem);
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
