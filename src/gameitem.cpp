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

#include "gameitem.h"

#include <QDeclarativeExpression>

#include "enums.h"
#include "quasigame.h"
#include "gamescene.h"

GameItem::GameItem(GameScene *parent)
    : QQuickItem((QQuickItem *)parent)
    , m_expression(0)
    , m_updateInterval(0)
    , m_collided(false)
    , m_scene(0)
{
    setZ(Quasi::EntityOrdering_01);
}

void GameItem::update(const long &delta)
{
    if ((m_updateInterval && m_updateTime.elapsed() >= m_updateInterval)
        || !m_updateInterval) {
        m_updateTime.restart();
        if (m_expression)
            m_expression->evaluate();
    }

    foreach (QQuickItem *child, childItems())
        if (GameItem *item = dynamic_cast<GameItem *>(child)) {
            item->update(delta);
        }
}

QDeclarativeScriptString GameItem::updateScript() const
{
    return m_updateScript;
}

void GameItem::setUpdateScript(const QDeclarativeScriptString &updateScript)
{
    if (m_updateScript.script() != updateScript.script()) {
        m_updateScript = updateScript;

        if (m_expression)
            delete m_expression;

        m_expression = new QDeclarativeExpression(m_updateScript.context(), m_updateScript.scopeObject(), m_updateScript.script());

        emit updateScriptChanged();
    }
}

int GameItem::updateInterval() const
{
    return m_updateInterval;
}

void GameItem::setUpdateInterval(const int &updateInterval)
{
    if (m_updateInterval != updateInterval) {
        m_updateInterval = updateInterval;

        emit updateScriptChanged();
    }
}

bool GameItem::collided() const
{
    return m_collided;
}

void GameItem::setCollided(const bool &collided)
{
    if (m_collided != collided) {
        m_collided = collided;

        emit collidedChanged();
    }
}

Quasi::Ordering GameItem::order() const
{
    return (Quasi::Ordering)z();
}

void GameItem::setOrder(Quasi::Ordering order)
{
    if (z() != order)
        setZ(order);
}

QList<QObject *> GameItem::collidedItems() const
{
    GameScene *scene = qobject_cast<GameScene *>(parent());

    return scene->collidedItems(const_cast<GameItem *>(this));
}

GameScene *GameItem::scene() const
{
    return m_scene;
}

void GameItem::setScene(GameScene *scene)
{
    m_scene = scene;
}

QuasiGame *GameItem::game() const
{
    if (m_scene)
        return m_scene->game();
    return 0;
}
