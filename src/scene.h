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

#ifndef _SCENE_H_
#define _SCENE_H_

#include "entity.h"
#include "box2dcontact.h"
#include "box2dworld.h"
#include "box2ddebugdraw.h"

#include <QtCore/QtGlobal>

#include <QtQml/QQmlComponent>
#include <QtQuick/QQuickItem>

class Game;
class Viewport;

class Scene : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(Viewport *viewport READ viewport WRITE setViewport NOTIFY viewportChanged)
    Q_PROPERTY(Game *game READ game WRITE setGame)
    Q_PROPERTY(Box2DWorld *world READ world NOTIFY worldChanged)
    Q_PROPERTY(bool physics READ physics WRITE setPhysics NOTIFY physicsChanged)
    Q_PROPERTY(bool debug READ debug WRITE setDebug NOTIFY debugChanged)
    /* These are wrapped around Box2DWorld */
    Q_PROPERTY(float timeStep READ timeStep WRITE setTimeStep NOTIFY timeStepChanged)
    Q_PROPERTY(int velocityIterations READ velocityIterations WRITE setVelocityIterations NOTIFY velocityIterationsChanged)
    Q_PROPERTY(int positionIterations READ positionIterations WRITE setPositionIterations NOTIFY positionIterationsChanged)
    Q_PROPERTY(QPointF gravity READ gravity WRITE setGravity NOTIFY gravityChanged)
    Q_PROPERTY(bool autoClearForces READ autoClearForces WRITE setAutoClearForces NOTIFY autoClearForcesChanged)
    Q_PROPERTY(Box2DProfile *profile READ profile NOTIFY stepped)
    Q_PROPERTY(float pixelsPerMeter READ pixelsPerMeter WRITE setPixelsPerMeter NOTIFY pixelsPerMeterChanged)
    /* End Box2DWorld wrapped properties */
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

    Box2DWorld *world() const;

    bool physics() const;
    void setPhysics(const bool &physics);

    bool debug() const;
    void setDebug(const bool &debug);

    virtual void update(const int &delta);

    /* These are wrapped around Box2DWorld */
    float timeStep() const;
    void setTimeStep(float timeStep);

    int velocityIterations() const;
    void setVelocityIterations(int iterations);

    int positionIterations() const;
    void setPositionIterations(int iterations);

    QPointF gravity() const;
    void setGravity(const QPointF &gravity);

    bool autoClearForces() const;
    void setAutoClearForces(bool autoClearForces);

    Box2DProfile *profile() const;

    float pixelsPerMeter() const;
    void setPixelsPerMeter(float pixelsPerMeter);

    Q_INVOKABLE void step();
    Q_INVOKABLE void clearForces();
    Q_INVOKABLE void rayCast(Box2DRayCast *rayCast,
                             const QPointF &point1,
                             const QPointF &point2);

    /* End wrapped Box2DWorld  */

    QObject *enterAnimation() const;
    void setEnterAnimation(QObject *animation);

    QObject *exitAnimation() const;
    void setExitAnimation(QObject *animation);
signals:
    void runningChanged();
    void viewportChanged();
    void worldChanged();
    void debugChanged();
    void physicsChanged();

    /* These are wrapped around Box2DWorld */
    void initialized();
    void preSolve(Box2DContact * contact);
    void postSolve(Box2DContact * contact);
    void timeStepChanged();
    void velocityIterationsChanged();
    void positionIterationsChanged();
    void gravityChanged();
    void autoClearForcesChanged();
    void stepped();
    void pixelsPerMeterChanged();
    /* End wrapped Box2DWorld  */

    void enterAnimationChanged();
    void exitAnimationChanged();

protected slots:
    void onDebugChanged();
    void onWorldChanged();

protected:
    virtual void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);
    virtual void componentComplete();
    virtual void itemChange(ItemChange change, const ItemChangeData &data);
    void updateEntities(QQuickItem *parent, const int &delta);
    void initializeEntities(QQuickItem *parent);
    void createWorld();

    bool m_running;
    Viewport *m_viewport;
    Game *m_game;
    Box2DWorld *m_world;
    Box2DDebugDraw *m_debugDraw;
    bool m_physics;
    bool m_debug;

    QObject *m_enterAnimation;
    QObject *m_exitAnimation;
};



#endif /* _SCENE_H_ */
