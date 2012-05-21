/**
 * Copyright (C) 2012 by INdT
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * @author Rodrigo Goncalves de Oliveira <rodrigo.goncalves@openbossa.org>
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

#include "scene.h"

#include "game.h"
#include "layers.h"

#include <QtCore/QtGlobal>

#if QT_VERSION >= 0x050000
#include <QtQml/QQmlEngine>
#else
#include <QtDeclarative/QDeclarativeEngine>
#endif

#if QT_VERSION >= 0x050000
void Scene::append_gameItem(QQmlListProperty<Entity> *list, Entity *gameItem)
#else
void Scene::append_gameItem(QDeclarativeListProperty<Entity> *list, Entity *gameItem)
#endif
{
    Scene *scene = qobject_cast<Scene *>(list->object);
    if (scene) {
        gameItem->setScene(scene);
        gameItem->setParentItem(scene);
        scene->m_entities.append(gameItem);

        Layers *gameLayers = qobject_cast<Layers *>(gameItem);
        if (gameLayers)
            scene->m_gameLayers = gameLayers;
    }
}

Scene::Scene(Game *parent)
    : QuasiDeclarativeItem(parent)
    , m_running(false)
    , m_collisions(0)
    , m_viewport(0)
    , m_game(0)
    , m_debug(false)
{
    setVisible(false);
}

#if QT_VERSION >= 0x050000
QQmlListProperty<Entity> Scene::entities() const
{
    return QQmlListProperty<Entity>(const_cast<Scene *>(this), 0, &Scene::append_gameItem);
}
#else
QDeclarativeListProperty<Entity> Scene::entities() const
{
    return QDeclarativeListProperty<Entity>(const_cast<Scene *>(this), 0, &Scene::append_gameItem);
}
#endif

void Scene::update(const int &delta)
{
    if (!m_running) // TODO: stop Qt animations as well
        return;

    checkCollisions();

#if QT_VERSION >= 0x050000
    QQuickItem *item;
#else
    QGraphicsItem *item;
#endif
    foreach (item, childItems()) {
        if (Entity *entity = dynamic_cast<Entity *>(item))
            entity->update(delta);
    }
}

bool Scene::running() const
{
    return m_running;
}

void Scene::setRunning(const bool &running)
{
    if (m_running != running) {
        m_running = running;

        emit runningChanged();
    }
}

void Scene::checkCollisions()
{
    int itemCount = m_entities.count();

    if (!m_collisions || (m_collisions->count() != itemCount)) {
        if (m_collisions)
            delete [] m_collisions;
        m_collisions = new QVector<QVector<bool> >(itemCount, QVector<bool>(itemCount));
    }

    Entity *item, *otherItem;

    foreach (item, m_entities)
        item->setCollided(false);

    for (int i = 0; i < itemCount; ++i) {
        item = m_entities.at(i);
        for (int j = 0; j < itemCount; ++j) {
            if (i == j)
                continue;

            otherItem = m_entities.at(j);

            bool collided = checkCollision(item, otherItem);

            item->setCollided(item->collided() ? true : collided);
            otherItem->setCollided(otherItem->collided() ? true : collided);

            (*m_collisions)[i][j] = collided;
            (*m_collisions)[j][i] = collided;
        }
    }
}

bool Scene::checkCollision(Entity *item, Entity *otherItem) const
{
    QRectF itemRect = item->boundingRect();
    QRectF otherItemRect = otherItem->boundingRect();

    itemRect.moveTo(item->x(), item->y());
    otherItemRect.moveTo(otherItem->x(), otherItem->y());

    return itemRect.intersects(otherItemRect)
           || itemRect.contains(otherItemRect)
           || otherItemRect.contains(itemRect);
}

QList<QObject *> Scene::collidedItems(Entity *gameItem) const
{
    QList<QObject *> collidedItemsList;

    if (m_collisions) {
        int index = m_entities.indexOf(gameItem);

        if (index != -1) {
            for (int i=0; i < m_entities.size(); ++i) {
                if (i != index && (*m_collisions)[index][i]) {
                    collidedItemsList.append(m_entities.at(i));
                }
            }
        }
    }

    return collidedItemsList;
}

Viewport *Scene::viewport() const
{
    return m_viewport;
}

void Scene::setViewport(Viewport *viewport)
{
    if (m_viewport != viewport) {
        m_viewport = viewport;

        emit viewportChanged();
    }
}

Game *Scene::game() const
{
    return m_game;
}

void Scene::setGame(Game *game)
{
    m_game = game;
}

Layers *Scene::gameLayers() const
{
    return m_gameLayers;
}

bool Scene::debug() const
{
    return m_debug;
}

void Scene::setDebug(const bool &debug)
{
    if (m_debug != debug) {
        m_debug = debug;

        emit debugChanged();
    }
}

#if QT_VERSION >= 0x050000
QObject *Scene::createEntity(QQmlComponent *component)
{
    QQmlContext *context = QQmlEngine::contextForObject(this);
#else
QObject *Scene::createEntity(QDeclarativeComponent *component)
{
    QDeclarativeContext *context = QDeclarativeEngine::contextForObject(this);
#endif

    QObject *object = component->beginCreate(context);
    object->setParent(this);

    if (Entity *entity = dynamic_cast<Entity *>(object))
        entity->setParentItem(this);

    component->completeCreate();

    return object;
}
