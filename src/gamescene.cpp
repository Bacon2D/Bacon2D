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
    , m_running(true)
    , m_collisions(0)
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

    checkCollisions();

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
    if (m_running != running) {
        m_running = running;

        emit runningChanged();
    }
}

void GameScene::checkCollisions()
{
    int itemCount = m_gameItems.count();

    if (!m_collisions) {
        m_collisions = new QVector<QVector<bool> >(itemCount);
    }

    GameItem *item, *otherItem;

    foreach (item, m_gameItems)
        item->setCollided(false);

    for (int i = 0; i < itemCount; ++i) {
        item = m_gameItems.at(i);
        for (int j = 0; j < itemCount; ++j) {
            if (i == j)
                continue;

            otherItem = m_gameItems.at(j);

            bool collided = checkCollision(item, otherItem);

            item->setCollided(item->collided() ? true : collided);
            otherItem->setCollided(otherItem->collided() ? true : collided);

            (*m_collisions)[i][j] = collided;
            (*m_collisions)[j][i] = collided;
        }
    }
}

bool GameScene::checkCollision(GameItem *item, GameItem *otherItem)
{
    QRectF itemRect = item->boundingRect();
    QRectF otherItemRect = otherItem->boundingRect();

    itemRect.moveTo(item->x(), item->y());
    otherItemRect.moveTo(otherItem->x(), otherItem->y());

    return itemRect.intersects(otherItemRect)
           || itemRect.contains(otherItemRect)
           || otherItemRect.contains(itemRect);
}

QList<QObject *> GameScene::collidedItems(GameItem *gameItem)
{
    QList<QObject *> collidedItemsList;

    if (m_collisions) {
        int index = m_gameItems.indexOf(gameItem);

        if (index != -1) {
            for (int i=0; i < m_gameItems.size(); ++i) {
                if (i != index && (*m_collisions)[index][i]) {
                    collidedItemsList.append(m_gameItems.at(i));
                }
            }
        }
    }

    return collidedItemsList;
}
