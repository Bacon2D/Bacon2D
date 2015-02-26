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

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <QtCore/QtGlobal>
#include <QtCore/QTime>
#include <QtQuick/QQuickItem>

class Game;
class Scene;
class Behavior;

class Entity : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(int updateInterval READ updateInterval WRITE setUpdateInterval NOTIFY updateIntervalChanged)
    Q_PROPERTY(Game *game READ game)
    Q_PROPERTY(Scene *scene READ scene NOTIFY sceneChanged)
    Q_PROPERTY(Behavior *behavior READ behavior WRITE setBehavior NOTIFY behaviorChanged)

public:
    Entity(Scene *parent = 0);
    ~Entity();

    int updateInterval() const;
    void setUpdateInterval(const int &updateInterval);

    Scene *scene() const;
    void setScene(Scene *scene);

    Game *game() const;

    Behavior *behavior() const;
    void setBehavior(Behavior *behavior);

    virtual void update(const int &delta);

signals:
    void updateIntervalChanged();
    void behaviorChanged();
    void sceneChanged();

protected:
    virtual void componentComplete();
    virtual void itemChange(ItemChange change, const ItemChangeData &data);
    void initializeEntities(QQuickItem *parent);

private:
    int m_updateInterval;
    QTime m_updateTime;
    Scene *m_scene;
    Behavior *m_behavior;
};

#endif /* _ENTITY_H_ */
