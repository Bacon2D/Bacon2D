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
#include "layers.h"
#include "quasideclarativeitem.h"

#include <QtCore/QList>
#include <QtCore/QVector>

class Game;
class Viewport;

class Scene : public QuasiDeclarativeItem
{
    Q_OBJECT

#if QT_VERSION >= 0x050000
    Q_PROPERTY(QQmlListProperty<Entity> entities READ entities)
#else
    Q_PROPERTY(QDeclarativeListProperty<Entity> entities READ entities)
#endif
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(Viewport *viewport READ viewport WRITE setViewport NOTIFY viewportChanged)
    Q_PROPERTY(Game *game READ game WRITE setGame)
    Q_PROPERTY(bool debug READ debug WRITE setDebug NOTIFY debugChanged)

public:
    Scene(Game *parent = 0);

#if QT_VERSION >= 0x050000
    QQmlListProperty<Entity> entities() const;
#else
    QDeclarativeListProperty<Entity> entities() const;
#endif

    bool running() const;
    void setRunning(const bool &running);

    Viewport *viewport() const;
    void setViewport(Viewport *viewport);

    Game *game() const;
    void setGame(Game *game);

    Layers *gameLayers() const;

    bool debug() const;
    void setDebug(const bool &debug);

    Q_INVOKABLE QList<QObject *> collidedItems(Entity *gameItem) const;

    virtual void update(const long &delta);

signals:
    void runningChanged();
    void viewportChanged();
    void debugChanged();

private:
#if QT_VERSION >= 0x050000
    static void append_gameItem(QQmlListProperty<Entity> *list, Entity *gameItem);
#else
    static void append_gameItem(QDeclarativeListProperty<Entity> *list, Entity *gameItem);
#endif
    void checkCollisions();
    bool checkCollision(Entity *item, Entity *otherItem) const;

protected:
    QList<Entity *> m_entities;
    bool m_running;
    QVector<QVector<bool> > *m_collisions;
    Viewport *m_viewport;
    Game *m_game;
    Layers *m_gameLayers;
    bool m_debug;
};

#endif /* _SCENE_H_ */
