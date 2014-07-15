/**
 * Copyright (C) 2012 by INdT
 * Copyright (C) 2014 Bacon2D Project
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
    , m_ups(30)
    , m_timerId(0)
    , m_enterScene(0)
    , m_exitScene(0)
{
    m_sceneStack.clear();
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
    if(m_sceneStack.isEmpty())
        return NULL;
    return m_sceneStack.top();
}

void Game::setCurrentScene(Scene *currentScene)
{
    if(!currentScene)
        return;
    if(m_sceneStack.size() > 0 && currentScene == m_sceneStack.top())
        return;

    if(m_sceneStack.isEmpty()){
        pushScene(currentScene);
        return;
    }

    int stackLevel = m_sceneStack.size();

    //we need to check the the currentScene is already on the stack
    //and remove it to put on top
    if(m_sceneStack.contains(currentScene)){
        int index = m_sceneStack.indexOf(currentScene);
        m_sceneStack.remove(index);
        //fix Scene Z in case of pushing a scene in the middle of
        //the stack to the top
        for(int i = index ; i< stackLevel -1; i++){
            m_sceneStack.at(i)->setZ(i);
        }
    }

    m_exitScene = m_sceneStack.pop();

    m_sceneStack.push(currentScene);
    currentScene->setZ(m_sceneStack.size());

    if(stackLevel != m_sceneStack.size())
        emit stackLevelChanged();

    if(currentScene->viewport()){
        currentScene->viewport()->setZ(m_sceneStack.size());
    }
    deactivateScene(m_exitScene);

    attachScene(currentScene);

    triggerExitAnimation(m_exitScene);
    if(!triggerEnterAnimation(currentScene)){
        activateScene(currentScene);
        if(m_exitScene)
            m_exitScene->setVisible(false);
        m_exitScene = NULL;
    }
}

/*!
  \qmlproperty int Game::stackLevel
  \brief Indicates how many Scenes are stacked in the scene stack
*/
int Game::stackLevel() const
{
    return m_sceneStack.size();
}

/*!
    \qmlmethod void Game::pushScene(Scene *scene)

    Suspends the execution of the running scene, while add a new Scene to the Scene stack.
    If the Scene has the enterAnimation property set, the push will be animated. \warning Pushing
    scenes already on stack will remove it from the current position and place it on top of the stack.

\sa popScene
*/
void Game::pushScene(Scene *scene)
{
    if(!scene)
        return;
    if(m_sceneStack.size() > 0 && scene == m_sceneStack.top())
        return;

    int stackLevel = m_sceneStack.size();

    //we need to check the the currentScene is already on the stack
    //and remove it to put on top
    if(m_sceneStack.contains(scene)){
        int index = m_sceneStack.indexOf(scene);
        m_sceneStack.remove(index);
        //fix Scene Z in case of pushing a scene in the middle of
        //the stack to the top
        for(int i = index ; i< stackLevel -1; i++){
            m_sceneStack.at(i)->setZ(i);
            if(m_sceneStack.at(i)->viewport()){
                m_sceneStack.at(i)->viewport()->setZ(i);
            }
        }
    }

    Scene *topScene = NULL;

    if(!m_sceneStack.isEmpty()){
        topScene = m_sceneStack.top();
        deactivateScene(topScene);
        m_exitScene = topScene;
    }

    m_sceneStack.push(scene);
    if(stackLevel != m_sceneStack.size())
        emit stackLevelChanged();

    scene->setZ(m_sceneStack.size());
    if(scene->viewport()){
        scene->viewport()->setZ(m_sceneStack.size());
    }
    attachScene(scene);
    if(!triggerEnterAnimation(scene)){
        activateScene(scene);
        if(topScene)
            topScene->setVisible(false);
    }
}

/*!
    \qmlmethod Scene* Game::popScene()
    \brief Suspends and remove the top Scene from the scene stack.
    Suspends and remove the current Scene from stack. If exitAnimation property
the exit will be animated. When there is no scene on stack, it will do nothing.

\sa pushScene
*/
Scene* Game::popScene()
{
    if(m_sceneStack.isEmpty())
        return NULL;

    Scene *topScene = m_sceneStack.pop();

    emit stackLevelChanged();

    if(topScene){
        deactivateScene(topScene);

        if(!m_sceneStack.isEmpty()){
            attachScene(m_sceneStack.top());
        }
        if(!triggerExitAnimation(topScene)){
            if(!m_sceneStack.isEmpty()){
                activateScene(m_sceneStack.top());
            }else{
                emit currentSceneChanged();
            }
            topScene->setVisible(false);
        }
    }
    return topScene;
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
    if(m_sceneStack.isEmpty())
        return;

    Scene *currentScene = m_sceneStack.top();
    long elapsedTime = m_gameTime.restart();

    if (currentScene && currentScene->running())
        currentScene->update(elapsedTime);

    if (currentScene->viewport() && currentScene->running())
        currentScene->viewport()->update(elapsedTime);
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
    if(m_sceneStack.isEmpty())
        return;

    Scene *currentScene = m_sceneStack.top();
    Viewport *viewport = currentScene->viewport();

    if (viewport && currentScene) {
        viewport->setWidth(width());
        viewport->setHeight(height());
        viewport->setContentWidth(currentScene->width());
        viewport->setContentHeight(currentScene->height());
        viewport->updateMaxOffsets();
    }

    QQuickItem::geometryChanged(newGeometry, oldGeometry);
}

void Game::attachScene(Scene *scene)
{
    if(!scene)
        return;

    scene->setGame(this);

    Viewport *viewport = scene->viewport();
    if (viewport) {
        viewport->setParent(this);
        viewport->setParentItem(this);
        viewport->setScene(scene);
        scene->setParentItem(viewport);
        viewport->setWidth(width());
        viewport->setHeight(height());
        viewport->setContentWidth(scene->width());
        viewport->setContentHeight(scene->height());
        viewport->updateMaxOffsets();
        viewport->setVisible(true);
    } else {
        scene->setParentItem(this);
    }
    scene->setVisible(true);
    scene->setRunning(false);
    scene->setEnabled(false);
    scene->setFocus(false, Qt::OtherFocusReason);


}

void Game::activateScene(Scene *scene)
{
    if(!scene){
        return;
    }
    scene->setRunning(true);
    scene->setEnabled(true);
    scene->setFocus(true, Qt::OtherFocusReason);
    emit currentSceneChanged();
}

void Game::deactivateScene(Scene *scene)
{
    if(!scene) return;

    scene->setRunning(false);
    scene->setEnabled(false);
    scene->setFocus(false, Qt::OtherFocusReason);
}

bool Game::triggerEnterAnimation(Scene *scene)
{
    QObject *enterAnimation = scene->enterAnimation();

    if(!enterAnimation)
        return false;

    m_enterScene = scene;
    const QMetaObject *meta = enterAnimation->metaObject();

    int propIndex = meta->indexOfProperty("running");

    QMetaMethod enterSignal = meta->property(propIndex).notifySignal();

    connect(enterAnimation, enterSignal,
            this, getMetaMethod(this, "handleEnterAnimationRunningChanged(bool)"));

    getMetaMethod(enterAnimation, "start()")
            .invoke(enterAnimation, Qt::AutoConnection);
    return true;
}

void Game::handleEnterAnimationRunningChanged(bool running)
{
    if(running)
        return;

    disconnect(sender(), 0, this, SLOT(handleEnterAnimationRunningChanged(bool)));

   activateScene(m_enterScene);
   m_enterScene = NULL;

   if(m_exitScene)
       m_exitScene->setVisible(false);
}

bool Game::triggerExitAnimation(Scene *scene)
{
    QObject *exitAnimation = scene->exitAnimation();

    if(!exitAnimation)
        return false;

    m_exitScene = scene;
    const QMetaObject *meta = exitAnimation->metaObject();

    int propIndex = meta->indexOfProperty("running");

    QMetaMethod signal  = meta->property(propIndex).notifySignal();

    connect(exitAnimation, signal,
            this, getMetaMethod(this, "handleExitAnimationRunningChanged(bool)"));

    getMetaMethod(exitAnimation, "start()").invoke(exitAnimation, Qt::AutoConnection);

    return true;
}

void Game::handleExitAnimationRunningChanged(bool running)
{
   if(running)
       return;
   disconnect(sender(), 0, this, SLOT(handleExitAnimationRunningChanged(bool)));

   if(m_exitScene){
       if(m_exitScene->viewport()){
           m_exitScene->viewport()->setVisible(false);
       }
       m_exitScene->setVisible(false);
   }
   m_exitScene = NULL;

   if(!m_sceneStack.isEmpty()){
       if(!m_sceneStack.top()->running()){
            activateScene(m_sceneStack.top());
       }
   }else{
        emit currentSceneChanged();
   }
}

QMetaMethod Game::getMetaMethod(QObject *object, QString methodSignature) const
{
    int methodIndex = object->metaObject()->indexOfMethod(QMetaObject::normalizedSignature(methodSignature.toLocal8Bit()));

    if(!object || methodIndex == -1)
        return QMetaMethod();

    return object->metaObject()->method(methodIndex);
}

