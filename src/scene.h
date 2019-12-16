/**
 * The MIT License (MIT)
 *
 * Copyright (C) 2012 by INdT
 * Copyright (C) 2014 Bacon2D Project
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @author Rodrigo Goncalves de Oliveira <rodrigo.goncalves@openbossa.org>
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

#ifndef SCENE_H
#define SCENE_H

#include "entity.h"
#include "box2dcontact.h"
#include "box2dworld.h"
#include "box2ddebugdraw.h"

#include <QtGlobal>

#include <QQmlComponent>
#include <QQuickItem>

class Game;
class Viewport;

class Scene : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running NOTIFY runningChanged)
    Q_PROPERTY(Viewport *viewport READ viewport WRITE setViewport NOTIFY viewportChanged)
    Q_PROPERTY(Game *game READ game CONSTANT)
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
    explicit Scene(QQuickItem *parent = nullptr);
    virtual ~Scene() override = default;

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

    void componentComplete() override;
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
    void onWorldChanged();
protected:
    bool m_running;
    Viewport *m_viewport;
    Game *m_game;
    Box2DWorld *m_world;
    Box2DDebugDraw *m_debugDraw;
    bool m_physics;
    bool m_debug;

    QObject *m_enterAnimation;
    QObject *m_exitAnimation;

    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;
    void itemChange(ItemChange change, const ItemChangeData &data) override;
    void updateEntities(QQuickItem *parent, const int &delta);
    void initializeEntities(QQuickItem *parent);
    void createWorld();
};

#endif // SCENE_H
