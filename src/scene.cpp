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
#include "layer.h"
#include "box2dworld.h"

#include <QtCore/QtGlobal>
#include <QtQml/QQmlEngine>

Scene::Scene(Game *parent)
    : QQuickItem(parent)
    , m_running(true)
    , m_game(parent)
    , m_debug(false)
{
    setVisible(false);

    connect(this, SIGNAL(debugChanged()), SLOT(onDebugChanged()));
}

Scene::~Scene()
{
}

void Scene::updateEntities(QQuickItem *parent, const int &delta)
{
    QQuickItem *item;
    foreach (item, parent->childItems()) {
        if (Entity *entity = qobject_cast<Entity *>(item))
            entity->update(delta);
        else if (Layer *layer = qobject_cast<Layer *>(item))
            layer->update();
        else if (Box2DWorld *world = dynamic_cast<Box2DWorld *>(item)) {
            if (!world->isRunning())
                world->step();
            updateEntities(item, delta);
        }
    }
}

void Scene::update(const int &delta)
{
    if (!m_running) // TODO: stop Qt animations as well
        return;

    updateEntities(this, delta);
}

bool Scene::running() const
{
    return m_running;
}

void Scene::setRunning(const bool &running)
{
    if (m_running == running)
        return;

    m_running = running;

    emit runningChanged();
}

Game *Scene::game() const
{
    return m_game;
}

void Scene::setGame(Game *game)
{
    m_game = game;
}

bool Scene::debug() const
{
    return m_debug;
}

void Scene::setDebug(const bool &debug)
{
    if (m_debug == debug)
        return;

    m_debug = debug;

    emit debugChanged();
}

void Scene::initializeEntities(QQuickItem *parent)
{
    QQuickItem *item;
    foreach (item, parent->childItems()) {
        if (Entity *entity = dynamic_cast<Entity *>(item))
            entity->setScene(this);
        else if (Box2DWorld *world = dynamic_cast<Box2DWorld *>(item)) {
            world->setRunning(false);
            initializeEntities(item);
        }
    }
}

void Scene::componentComplete()
{
    QQuickItem::componentComplete();
    initializeEntities(this);
}

void Scene::itemChange(ItemChange change, const ItemChangeData &data)
{
    if (isComponentComplete() && change == ItemChildAddedChange) {
        QQuickItem *child = data.item;
        if (Entity *entity = dynamic_cast<Entity *>(child))
            entity->setScene(this);
        initializeEntities(child);
    }

    QQuickItem::itemChange(change, data);
}

void Scene::onDebugChanged()
{
}
