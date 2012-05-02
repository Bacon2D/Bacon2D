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

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "enums.h"
#include "quasideclarativeitem.h"

#include <QtCore/QtGlobal>
#include <QtCore/QTime>

class Game;
class Scene;
class Behavior;

class Entity : public QuasiDeclarativeItem
{
    Q_OBJECT

    Q_PROPERTY(int updateInterval READ updateInterval WRITE setUpdateInterval NOTIFY updateIntervalChanged)
    Q_PROPERTY(bool collided READ collided WRITE setCollided NOTIFY collidedChanged)
    Q_PROPERTY(Quasi::Ordering order READ order WRITE setOrder)
    Q_PROPERTY(Game *game READ game)
    Q_PROPERTY(Behavior *behavior READ behavior WRITE setBehavior NOTIFY behaviorChanged)

public:
    Entity(Scene *parent = 0);

    int updateInterval() const;
    void setUpdateInterval(const int &updateInterval);

    bool collided() const;
    void setCollided(const bool &collided);

    Quasi::Ordering order() const;
    void setOrder(Quasi::Ordering order);

    Q_INVOKABLE QList<QObject *> collidedItems() const;

    Scene *scene() const;
    void setScene(Scene *scene);

    Game *game() const;

    Behavior *behavior() const;
    void setBehavior(Behavior *behavior);

    virtual void update(const long &delta);

signals:
    void updateIntervalChanged();
    void collidedChanged();
    void behaviorChanged();

private:
    int m_updateInterval;
    QTime m_updateTime;
    bool m_collided;
    Scene *m_scene;
    Behavior *m_behavior;
};

#endif /* _ENTITY_H_ */
