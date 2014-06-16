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

#ifndef _SCENE_H_
#define _SCENE_H_

#include "entity.h"

#include <QtCore/QtGlobal>

#include <QtQml/QQmlComponent>
#include <QtQml/QQmlScriptString>

class Game;
class Viewport;

class Scene : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(Viewport *viewport READ viewport WRITE setViewport NOTIFY viewportChanged)
    Q_PROPERTY(Game *game READ game WRITE setGame)
    Q_PROPERTY(bool debug READ debug WRITE setDebug NOTIFY debugChanged)
    Q_PROPERTY(QObject *enterAnimation READ enterAnimation WRITE setEnterAnimation NOTIFY enterAnimationChanged)
    Q_PROPERTY(QObject *exitAnimation READ exitAnimation WRITE setExitAnimation NOTIFY exitAnimationChanged)

public:
    Scene(Game *parent = 0);
    ~Scene();

    bool running() const;
    void setRunning(const bool &running);

    Viewport *viewport() const;
    void setViewport(Viewport *viewport);

    Game *game() const;
    void setGame(Game *game);

    bool debug() const;
    void setDebug(const bool &debug);

    virtual void update(const int &delta);

    QObject *enterAnimation() const;
    void setEnterAnimation(QObject *animation);

    QObject *exitAnimation() const;
    void setExitAnimation(QObject *animation);

    Q_INVOKABLE void callExitAnimation();

signals:
    void runningChanged();
    void viewportChanged();
    void debugChanged();
    void enterAnimationChanged();
    void exitAnimationChanged();


protected slots:
    void onDebugChanged();

protected:
    virtual void componentComplete();
    virtual void itemChange(ItemChange change, const ItemChangeData &data);
    void updateEntities(QQuickItem *parent, const int &delta);
    void initializeEntities(QQuickItem *parent);

protected:
    bool m_running;
    Viewport *m_viewport;
    Game *m_game;
    bool m_debug;

    QObject *m_enterAnimation;
    QObject *m_exitAnimation;
};



#endif /* _SCENE_H_ */
