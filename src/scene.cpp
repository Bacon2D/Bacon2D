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

Scene::Scene(Game *parent)
    : QuasiDeclarativeItem(parent)
    , m_running(false)
    , m_viewport(0)
    , m_game(0)
    , m_debug(false)
{
    setVisible(false);
}

void Scene::update(const int &delta)
{
    if (!m_running) // TODO: stop Qt animations as well
        return;

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

void Scene::componentComplete()
{
    QuasiDeclarativeItem::componentComplete();

#if QT_VERSION >= 0x050000
    QQuickItem *item;
#else
    QGraphicsItem *item;
#endif
    foreach (item, childItems()) {
        if (Entity *entity = dynamic_cast<Entity *>(item)) {
            entity->setParent(this);
            entity->setParentItem(this);
            entity->setScene(this);

            if (Layers *gameLayers = qobject_cast<Layers *>(entity))
                m_gameLayers = gameLayers;
        }
    }
}

#if QT_VERSION >= 0x050000
void Scene::itemChange(ItemChange change, const ItemChangeData &data)
#else
QVariant Scene::itemChange(GraphicsItemChange change, const QVariant &value)
#endif
{
    if (isComponentComplete() && change == ItemChildAddedChange) {
#if QT_VERSION >= 0x050000
        QQuickItem *child = data.item;
#else
        QGraphicsItem *child = value.value<QGraphicsItem *>();
#endif
        if (Entity *entity = dynamic_cast<Entity *>(child))
            entity->setScene(this);
    }

#if QT_VERSION >= 0x050000
    QuasiDeclarativeItem::itemChange(change, data);
#else
    return QuasiDeclarativeItem::itemChange(change, value);
#endif
}
