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

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "box2dbody.h"

#include <QtCore/QtGlobal>
#include <QtCore/QTime>
#include <QtQuick/QQuickItem>

class Game;
class Scene;
class Behavior;

class Entity : public Box2DBody
{
    Q_OBJECT

    Q_PROPERTY(int updateInterval READ updateInterval WRITE setUpdateInterval NOTIFY updateIntervalChanged)
    Q_PROPERTY(Game *game READ game)
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

    void initialize(Box2DWorld *world);

signals:
    void updateIntervalChanged();
    void behaviorChanged();

private:
    int m_updateInterval;
    QTime m_updateTime;
    Scene *m_scene;
    Behavior *m_behavior;
};

#endif /* _ENTITY_H_ */
