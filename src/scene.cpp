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
#include "viewport.h"
#include "box2dworld.h"

#include <QtCore/QtGlobal>
#include <QtQml/QQmlEngine>

/*!
  \qmltype Scene
  \inqmlmodule Bacon2D
  \inherits Item
  \brief The root view in the Game.

  The Scene component is the root view for the \l Game.

  The size of the Scene can be larger than the size of the \l Game, accessible 
  using a \l Viewport.  The \l Viewport provides xOffset and yOffset properties
  which can be used to control movement of the Viewport.

  Example usage:
  \qml
   import QtQuick 2.0
   import Bacon2D 1.0

   Game {
       id: game
       width: 800
       height: 600

       Scene {
           id: scene
           width: 1200
           height: 800
           physics: true
           viewport: Viewport {
               yOffset: player.y - 100
           }
           Entity {
               id: player
           }
       }
   }
   \endqml
*/
Scene::Scene(Game *parent)
    : QQuickItem(parent)
    , m_running(true)
    , m_viewport(0)
    , m_game(parent)
    , m_world(0)
    , m_physics(false)
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
        else if (Box2DWorld *world = dynamic_cast<Box2DWorld *>(item))
            updateEntities(world, delta);
    }
}

void Scene::update(const int &delta)
{
    if (!m_running) // TODO: stop Qt animations as well
        return;

    updateEntities(this, delta);
}

/*!
 * \qmlproperty bool Scene::running
 * \brief The current running state of Scene
 */
bool Scene::running() const
{
    return m_running;
}

void Scene::setRunning(const bool &running)
{
    if (m_running == running)
        return;

    m_running = running;
    if (m_physics && m_world)
        m_world->setRunning(m_running);

    emit runningChanged();
}

/*!
 * \qmlproperty Viewport Scene::viewport
 * \brief Holds the a reference to the Viewport for the current Scene.
 */
Viewport *Scene::viewport() const
{
    return m_viewport;
}

void Scene::setViewport(Viewport *viewport)
{
    if (m_viewport == viewport)
        return;

    m_viewport = viewport;

    emit viewportChanged();
}

/*!
 * \qmlproperty Game Scene::game
 * \brief Holds the a reference to the Game that contains the Scene.
 */
Game *Scene::game() const
{
    return m_game;
}

void Scene::setGame(Game *game)
{
    m_game = game;
}

/*!
 * \qmlproperty World Scene::world
 * \brief Holds the a reference to the World attached to the Scene.
 */
Box2DWorld *Scene::world() const
{
    return m_world;
}

void Scene::createWorld()
{
    if (m_physics && !m_world) {
        m_world = new Box2DWorld(this);
        m_world->setParentItem(this);
        m_world->componentComplete();
        m_world->setRunning(m_running);
        emit worldChanged();
    }
}

/*!
 * \qmlproperty bool Scene::physics
 * \brief This property determines if the Scene contains a Box2D physics world
 */
bool Scene::physics() const
{
    return m_physics;
}

void Scene::setPhysics(const bool &physics)
{
    if (m_physics == physics)
        return;

    m_physics = physics;

    if (m_physics && !m_world) {
        createWorld();
    }
}

/*!
 * \qmlproperty bool Scene::debug
 * \brief Debug mode
 */
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
        if (m_physics && m_world) {
            if (Box2DBody *body = dynamic_cast<Box2DBody *>(item)) {
                body->setParent(m_world);
                body->initialize(m_world);
            }
        }
        initializeEntities(item);
    }
}

void Scene::componentComplete()
{
    QQuickItem::componentComplete();
    initializeEntities(this);
    if (m_world)
        m_world->componentComplete();
}

void Scene::itemChange(ItemChange change, const ItemChangeData &data)
{
    if (isComponentComplete() && change == ItemChildAddedChange) {
        QQuickItem *child = data.item;
        if (Entity *entity = dynamic_cast<Entity *>(child))
            entity->setScene(this);
        if (m_physics && m_world) {
            if (Box2DBody *body = dynamic_cast<Box2DBody *>(child)) {
                body->setParent(m_world);
                body->initialize(m_world);
            }
        }
        initializeEntities(child);
    }

    QQuickItem::itemChange(change, data);
}

void Scene::onDebugChanged()
{
}
