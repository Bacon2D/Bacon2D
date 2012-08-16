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

#if QT_VERSION >= 0x050000
#include <QtQuick/QQuickCanvas>
#else
#include <QtGui/QApplication>
#endif

#include <QtGui/QCursor>

Game::Game(QuasiDeclarativeItem *parent)
    : QuasiDeclarativeItem(parent)
    , m_currentScene(0)
    , m_fps(60)
    , m_viewport(0)
    , m_timerId(0)
{
    m_gameTime.start();
    m_timerId = startTimer(1000 / m_fps);
}

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

int Game::fps() const
{
    return m_fps;
}

void Game::setFps(const int &fps)
{
    if (m_fps == fps)
        return;

    m_fps = fps;

    emit fpsChanged();
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

QPointF Game::mouse()
{
#if QT_VERSION >= 0x050000
    return canvas()->mapFromGlobal(QCursor::pos());
#else
    m_mousePos = QCursor::pos();
    QWidget *widget = QApplication::widgetAt(m_mousePos);

    if (widget)
        return widget->mapFromGlobal(m_mousePos);
    else
        return m_mousePos;
#endif
}

#if QT_VERSION < 0x050000
// this function is needed on Qt4 to fix viewport's width and height
void Game::componentComplete()
{
    if (m_viewport && m_currentScene) {
        m_viewport->setWidth(width());
        m_viewport->setHeight(height());
        m_viewport->setContentWidth(m_currentScene->width());
        m_viewport->setContentHeight(m_currentScene->height());
        m_viewport->updateMaxOffsets();
    }

    QDeclarativeItem::componentComplete();
}
#endif
