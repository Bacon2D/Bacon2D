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

#include <QtCore/QtGlobal>
#include <QtCore/QList>
#include <QtCore/QVector>

#if QT_VERSION >= 0x050000
#include <QtQml/QQmlComponent>
#else
#include <QtDeclarative/QDeclarativeComponent>
#endif

class Game;
class Viewport;

class Scene : public QuasiDeclarativeItem
{
    Q_OBJECT

    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(Viewport *viewport READ viewport WRITE setViewport NOTIFY viewportChanged)
    Q_PROPERTY(Game *game READ game WRITE setGame)
    Q_PROPERTY(bool debug READ debug WRITE setDebug NOTIFY debugChanged)

public:
    Scene(Game *parent = 0);

    bool running() const;
    void setRunning(const bool &running);

    Viewport *viewport() const;
    void setViewport(Viewport *viewport);

    Game *game() const;
    void setGame(Game *game);

    Layers *gameLayers() const;

    bool debug() const;
    void setDebug(const bool &debug);

    virtual void update(const int &delta);

    virtual void componentComplete();

signals:
    void runningChanged();
    void viewportChanged();
    void debugChanged();

protected:
#if QT_VERSION >= 0x050000
    virtual void itemChange(ItemChange change, const ItemChangeData &data);
#else
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);
#endif

    bool m_running;
    Viewport *m_viewport;
    Game *m_game;
    Layers *m_gameLayers;
    bool m_debug;
};

#endif /* _SCENE_H_ */
