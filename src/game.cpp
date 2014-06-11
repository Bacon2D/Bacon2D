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

#include "game.h"
#include "scene.h"
#include "viewport.h"

#include <QtQuick/QQuickWindow>
#include <QtGui/QCursor>

/*!
  \qmltype Game
  \inqmlmodule Bacon2D
  \inherits Item
  \brief The root element containing one or more Scene.

  The Game component is the root game component which
  contains one or more Scene components.  Only one
  Scene will be set as currentScene.
  
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
           width: 300
           height: 300
       }
   }
   \endqml
*/
Game::Game(QQuickItem *parent)
    : QQuickItem(parent)
    , m_currentScene(0)
    , m_ups(30)
    , m_timerId(0)
{
    m_gameTime.start();
    m_timerId = startTimer(1000 / m_ups);
}

/*!
  \qmlproperty string Game::gameName
  \brief Name of the game, required if using Settings
*/
QString Game::gameName()
{
    return QCoreApplication::applicationName();
}

void Game::setGameName(const QString& gameName)
{
    // applicationName is needed for QSettings to create path to file
    QCoreApplication::setApplicationName(gameName);
    // Set the organizationName to match the applicationName, it's redundant 
    // but creates path that plays well accross platforms
    QCoreApplication::setOrganizationName(gameName);
    Q_EMIT gameNameChanged();
}

/*!
  \qmlproperty Scene Game::currentScene
  \brief The current Scene
*/
Scene *Game::currentScene() const
{
    return m_currentScene;
}

void Game::setCurrentScene(Scene *currentScene)
{
    if (m_currentScene == currentScene)
        return;

    if (m_currentScene) {
        if (m_viewport) {
            m_viewport->setVisible(false);
            m_viewport = 0;
        }

        m_currentScene->setRunning(false);
        m_currentScene->setVisible(false);
    }

    m_currentScene = currentScene;

    if (m_currentScene) {
        m_currentScene->setGame(this);

        if ((m_viewport = m_currentScene->viewport())) {
            m_viewport->setParent(this);
            m_viewport->setParentItem(this);
            m_viewport->setScene(m_currentScene);
            m_viewport->setWidth(width());
            m_viewport->setHeight(height());
            m_viewport->setContentWidth(m_currentScene->width());
            m_viewport->setContentHeight(m_currentScene->height());
            m_viewport->updateMaxOffsets();
            m_viewport->setVisible(true);

            m_currentScene->setParentItem(m_viewport);
        } else {
            m_currentScene->setParent(this);
            m_currentScene->setParentItem(this);
        }

        m_currentScene->setRunning(true);
        m_currentScene->setVisible(true);
    }

    emit currentSceneChanged();
}

/*!
  \qmlproperty int Game::ups
  \brief This property holds the number of times update is called per second.
    
    Updates per second can be used to control the speed of the game 
    loop.  The default is 30.
 */
int Game::ups() const
{
    return m_ups;
}

void Game::setUps(const int &ups)
{
    if (m_ups == ups)
        return;

    m_ups = ups;

    killTimer(m_timerId);
    m_gameTime.restart();
    m_timerId = startTimer(1000 / m_ups);

    emit upsChanged();
}

void Game::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)

    update();
}

void Game::update()
{
    long elapsedTime = m_gameTime.restart();
    if (m_currentScene)
        m_currentScene->update(elapsedTime);
    if (m_viewport)
        m_viewport->update(elapsedTime);
}

/*!
  \qmlproperty QPointF Game::mouse
  \brief The point in the plane of the mouse pointer
*/
QPointF Game::mouse()
{
    return window()->mapFromGlobal(QCursor::pos());
}

void Game::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    if (newGeometry.isEmpty() || !isComponentComplete() || (newGeometry == oldGeometry))
        return;

    if (m_viewport && m_currentScene) {
        m_viewport->setWidth(width());
        m_viewport->setHeight(height());
        m_viewport->setContentWidth(m_currentScene->width());
        m_viewport->setContentHeight(m_currentScene->height());
        m_viewport->updateMaxOffsets();
    }

    QQuickItem::geometryChanged(newGeometry, oldGeometry);
}
