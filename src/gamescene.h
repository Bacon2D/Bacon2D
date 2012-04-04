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
#include <QtQuick/QQuickItem>

#include "gameitem.h"

class QuasiGame;
class Viewport;

class GameScene : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QDeclarativeListProperty<GameItem> entities READ entities)
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(Viewport *viewport READ viewport WRITE setViewport NOTIFY viewportChanged)
    Q_PROPERTY(QuasiGame *game READ game WRITE setGame)
    Q_PROPERTY(bool debug READ debug WRITE setDebug NOTIFY debugChanged)

public:
    GameScene(QuasiGame *parent = 0);

    QDeclarativeListProperty<GameItem> entities() const;

    bool running() const;
    void setRunning(const bool &running);

    Viewport *viewport() const;
    void setViewport(Viewport *viewport);

    QuasiGame *game() const;
    void setGame(QuasiGame *game);

    bool debug() const;
    void setDebug(const bool &debug);

    Q_INVOKABLE QList<QObject *> collidedItems(GameItem *gameItem) const;

    virtual void update(const long &delta);

signals:
    void runningChanged();
    void viewportChanged();
    void debugChanged();

private:
    static void append_gameItem(QDeclarativeListProperty<GameItem> *list, GameItem *gameItem);
    void checkCollisions();
    bool checkCollision(GameItem *item, GameItem *otherItem) const;

protected:
    QList<GameItem *> m_entities;
    bool m_running;
    QVector<QVector<bool> > *m_collisions;
    Viewport *m_viewport;
    QuasiGame *m_game;
    bool m_debug;
};

#endif /* _GAMESCENE_H_ */
