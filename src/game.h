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

#ifndef _GAME_H_
#define _GAME_H_

#include "enums.h"

#include <QtQuick/QQuickItem>
#include <QtCore/QTime>
#include <QtCore/QtGlobal>
#include <QtCore/QStack>

class Scene;
class Viewport;

/*!
  \class Game
 */
class Game : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(Scene *currentScene READ currentScene WRITE setCurrentScene NOTIFY currentSceneChanged)
    Q_PROPERTY(int ups READ ups WRITE setUps NOTIFY upsChanged)
    Q_PROPERTY(QPointF mouse READ mouse)
    Q_PROPERTY(QString gameName READ gameName WRITE setGameName NOTIFY gameNameChanged)
    Q_PROPERTY(Bacon2D::State gameState READ gameState WRITE setGameState NOTIFY gameStateChanged)
    Q_PROPERTY(int stackLevel READ stackLevel NOTIFY stackLevelChanged)

public:
    Game(QQuickItem *parent = 0);
    virtual ~Game();

    Scene *currentScene() const;
    void setCurrentScene(Scene *currentScene);

    int stackLevel() const;
    Q_INVOKABLE void pushScene(Scene* scene);
    Q_INVOKABLE Scene* popScene();

    int ups() const;
    void setUps(const int &ups);

    QPointF mouse();

    QString gameName();
    void setGameName(const QString& gameName);

    Bacon2D::State gameState() const { return m_state; };
    void setGameState(const Bacon2D::State &state);

protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);
    void timerEvent(QTimerEvent *event);
    void update();

signals:
    void currentSceneChanged();
    void upsChanged();
    void gameNameChanged();
    void gameStateChanged();
    void stackLevelChanged();

private:

    QTime m_gameTime;
    int m_ups;
    int m_timerId;
    Bacon2D::State m_state;

    //for handling scene transition
    Scene *m_enterScene;
    Scene *m_exitScene;
    QStack<Scene*> m_sceneStack;

    QMetaMethod getMetaMethod(QObject *object, QString methodSignature) const;

    void attachScene(Scene *scene);
    void activateScene(Scene *scene);
    void deactivateScene(Scene *scene);
    bool triggerExitAnimation(Scene *scene);
    bool triggerEnterAnimation(Scene *scene);

private slots:
    void handleEnterAnimationRunningChanged(bool running);
    void handleExitAnimationRunningChanged(bool running);
    void onApplicationStateChanged(Qt::ApplicationState state);
};

#endif /* _GAME_H_ */
