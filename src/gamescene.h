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

#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include <QtCore/QList>
#include <QtCore/QVector>

#include "quasideclarativeitem.h"
#include "gameitem.h"
#include "gamelayers.h"

class QuasiGame;
class Viewport;

class GameScene : public QuasiDeclarativeItem
{
    Q_OBJECT

#if QT_VERSION >= 0x050000
    Q_PROPERTY(QQmlListProperty<GameItem> entities READ entities)
#else
    Q_PROPERTY(QDeclarativeListProperty<GameItem> entities READ entities)
#endif
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(Viewport *viewport READ viewport WRITE setViewport NOTIFY viewportChanged)
    Q_PROPERTY(QuasiGame *game READ game WRITE setGame)
    Q_PROPERTY(bool debug READ debug WRITE setDebug NOTIFY debugChanged)

public:
    GameScene(QuasiGame *parent = 0);

#if QT_VERSION >= 0x050000
    QQmlListProperty<GameItem> entities() const;
#else
    QDeclarativeListProperty<GameItem> entities() const;
#endif

    bool running() const;
    void setRunning(const bool &running);

    Viewport *viewport() const;
    void setViewport(Viewport *viewport);

    QuasiGame *game() const;
    void setGame(QuasiGame *game);

    GameLayers *gameLayers() const;

    bool debug() const;
    void setDebug(const bool &debug);

    Q_INVOKABLE QList<QObject *> collidedItems(GameItem *gameItem) const;

    virtual void update(const long &delta);

signals:
    void runningChanged();
    void viewportChanged();
    void debugChanged();

private:
#if QT_VERSION >= 0x050000
    static void append_gameItem(QQmlListProperty<GameItem> *list, GameItem *gameItem);
#else
    static void append_gameItem(QDeclarativeListProperty<GameItem> *list, GameItem *gameItem);
#endif
    void checkCollisions();
    bool checkCollision(GameItem *item, GameItem *otherItem) const;

protected:
    QList<GameItem *> m_entities;
    bool m_running;
    QVector<QVector<bool> > *m_collisions;
    Viewport *m_viewport;
    QuasiGame *m_game;
    GameLayers *m_gameLayers;
    bool m_debug;
};

#endif /* _GAMESCENE_H_ */
