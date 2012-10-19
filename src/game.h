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

#ifndef _GAME_H_
#define _GAME_H_

#include "quasideclarativeitem.h"

#include <QtCore/QTime>
#include <QtCore/QtGlobal>

class Scene;

class Game : public QuasiDeclarativeItem
{
    Q_OBJECT

    Q_PROPERTY(Scene *currentScene READ currentScene WRITE setCurrentScene NOTIFY currentSceneChanged)
    Q_PROPERTY(int fps READ fps WRITE setFps NOTIFY fpsChanged)
    Q_PROPERTY(QPointF mouse READ mouse)

public:
    Game(QuasiDeclarativeItem *parent = 0);

    Scene *currentScene() const;
    void setCurrentScene(Scene *currentScene);

    int fps() const;
    void setFps(const int &fps);

    QPointF mouse();

protected:
    void timerEvent(QTimerEvent *event);
    void update();

signals:
    void currentSceneChanged();
    void fpsChanged();

private:
    Scene *m_currentScene;
    QTime m_gameTime;
    int m_fps;
    int m_timerId;
#if QT_VERSION < 0x050000
    QPoint m_mousePos;
#endif
};

#endif /* _GAME_H_ */
