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

#ifndef _GAME_H_
#define _GAME_H_

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
    Q_PROPERTY(int stackLevel READ stackLevel NOTIFY stackLevelChanged)

public:
    Game(QQuickItem *parent = 0);

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

protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);
    void timerEvent(QTimerEvent *event);
    void update();

signals:
    void currentSceneChanged();
    void upsChanged();
    void gameNameChanged();
    void stackLevelChanged();

private:

    QTime m_gameTime;
    int m_ups;
    int m_timerId;

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
};

#endif /* _GAME_H_ */
