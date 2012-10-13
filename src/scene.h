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
#include "quasideclarativeitem.h"

#include <QtCore/QtGlobal>

#if QT_VERSION >= 0x050000
#include <QtQml/QQmlComponent>
#else
#include <QtDeclarative/QDeclarativeComponent>
#endif

class Game;
class b2World;
class Fixture;
class Box2DContact;
class Box2DDebugDraw;

class Scene : public QuasiDeclarativeItem
{
    Q_OBJECT

    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(Game *game READ game WRITE setGame)
    Q_PROPERTY(bool debug READ debug WRITE setDebug NOTIFY debugChanged)
    Q_PROPERTY(QPointF gravity READ gravity WRITE setGravity)
    Q_PROPERTY(qreal physicsTimeStep READ physicsTimeStep WRITE setPhysicsTimestep NOTIFY physicsTimeStepChanged)
    Q_PROPERTY(int physicsVelocityIterations READ physicsVelocityIterations WRITE setPhysicsVelocityIterations NOTIFY physicsVelocityIterationsChanged)
    Q_PROPERTY(int physicsPositionIterations READ physicsPositionIterations WRITE setPhysicsPositionIterations NOTIFY physicsPositionIterationsChanged)

public:
    Scene(Game *parent = 0);
    ~Scene();

    bool running() const;
    void setRunning(const bool &running);

    Game *game() const;
    void setGame(Game *game);

    bool debug() const;
    void setDebug(const bool &debug);

    virtual void update(const int &delta);

    b2World *world() const;

    void setGravity(const QPointF &gravity);
    QPointF gravity() const;

    qreal physicsTimeStep() const;
    void setPhysicsTimestep(const qreal &physicsTimeStep);

    int physicsVelocityIterations() const;
    void setPhysicsVelocityIterations(const int &physicsVelocityIterations);

    int physicsPositionIterations() const;
    void setPhysicsPositionIterations(const int &physicsPositionIterations);

    void onPostSolve(Box2DContact *contact);
    void onPreSolve(Box2DContact *contact);
    void onBeginContact(Box2DContact *contact);
    void onEndContact(Box2DContact *contact);

signals:
    void runningChanged();
    void debugChanged();
    void contactPostSolve(Box2DContact *contact);
    void contactPreSolve(Box2DContact *contact);
    void contactBegin(Box2DContact *contact);
    void contactEnd(Box2DContact *contact);
    void physicsTimeStepChanged();
    void physicsVelocityIterationsChanged();
    void physicsPositionIterationsChanged();

protected slots:
    void onDebugChanged();

protected:
    virtual void componentComplete();
#if QT_VERSION >= 0x050000
    virtual void itemChange(ItemChange change, const ItemChangeData &data);
#else
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);
#endif

protected:
    bool m_running;
    Game *m_game;
    bool m_debug;
    QSharedPointer<b2World> m_world;
    QPointF m_gravity;
    Box2DDebugDraw *m_debugDraw;
    qreal m_physicsTimeStep;
    int m_physicsVelocityIterations;
    int m_physicsPositionIterations;
};

#endif /* _SCENE_H_ */
