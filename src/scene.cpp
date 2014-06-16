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
            updateEntities(item, delta);
    }
}

void Scene::update(const int &delta)
{
    if (!m_running) // TODO: stop Qt animations as well
        return;

    updateEntities(this, delta);
}

QObject *Scene::enterAnimation() const
{
    return m_enterAnimation;
}

void Scene::setEnterAnimation(QObject *animation)
{
    //TODO:
    // if is_running -> complete
    const QMetaObject *meta = animation->metaObject();
    do{
        if(QString("QQuickAbstractAnimation") == QString::fromLocal8Bit(meta->className())){
            m_enterAnimation = animation;
            break;
        }
    }
    while( (meta = meta->superClass()) != 0);
}

QObject *Scene::exitAnimation() const
{
    return m_exitAnimation;
}

void Scene::setExitAnimation(QObject *animation)
{
    //TODO:
    // if is_running -> complete
    const QMetaObject *meta = animation->metaObject();
    do{
        if(QString("QQuickAbstractAnimation") == QString::fromLocal8Bit(meta->className())){
            m_exitAnimation = animation;
            break;
        }
    }
    while( (meta = meta->superClass()) != 0);

    for(int i=0; i < animation->metaObject()->methodCount(); i++){
        qDebug() << animation->metaObject()->method(i).methodSignature();
    }
}

void Scene::callExitAnimation()
{
    if(!m_exitAnimation)
        return;
    qDebug() << __FUNCTION__;
    m_exitAnimation->metaObject()->method(
                m_exitAnimation->metaObject()->indexOfMethod("start()"))
            .invoke(m_exitAnimation, Qt::DirectConnection);

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
        else if (Box2DWorld *world = dynamic_cast<Box2DWorld *>(item))
            initializeEntities(item);
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
