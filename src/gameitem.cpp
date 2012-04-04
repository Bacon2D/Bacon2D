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

#include "enums.h"
#include "gamescene.h"
#include "quasigame.h"

#if QT_VERSION >= 0x050000
#include <QtQml/QQmlExpression>
#else
#include <QtDeclarative/QDeclarativeExpression>
#endif

GameItem::GameItem(GameScene *parent)
    : QuasiDeclarativeItem(parent)
    , m_expression(0)
    , m_updateInterval(0)
    , m_collided(false)
    , m_scene(0)
{
#if QT_VERSION >= 0x050000
    setZ(Quasi::EntityOrdering_01);
#else
    setZValue(Quasi::EntityOrdering_01);
#endif
}

void GameItem::update(const long &delta)
{
    if ((m_updateInterval && m_updateTime.elapsed() >= m_updateInterval)
        || !m_updateInterval) {
        m_updateTime.restart();
        if (m_expression)
            m_expression->evaluate();
    }

#if QT_VERSION >= 0x050000
    QQuickItem *child;
#else
    QGraphicsItem *child;
#endif
    foreach (child, childItems())
        if (GameItem *item = dynamic_cast<GameItem *>(child)) {
            item->update(delta);
        }
}

#if QT_VERSION >= 0x050000
QQmlScriptString GameItem::updateScript() const
#else
QDeclarativeScriptString GameItem::updateScript() const
#endif
{
    return m_updateScript;
}

#if QT_VERSION >= 0x050000
void GameItem::setUpdateScript(const QQmlScriptString &updateScript)
#else
void GameItem::setUpdateScript(const QDeclarativeScriptString &updateScript)
#endif
{
    if (m_updateScript.script() != updateScript.script()) {
        m_updateScript = updateScript;

        if (m_expression)
            delete m_expression;

#if QT_VERSION >= 0x050000
        m_expression = new QQmlExpression(m_updateScript.context(), m_updateScript.scopeObject(), m_updateScript.script());
#else
        m_expression = new QDeclarativeExpression(m_updateScript.context(), m_updateScript.scopeObject(), m_updateScript.script());
#endif

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
#if QT_VERSION >= 0x050000
    return (Quasi::Ordering)z();
#else
    return (Quasi::Ordering)zValue();
#endif
}

void GameItem::setOrder(Quasi::Ordering order)
{
#if QT_VERSION >= 0x050000
    if (z() != order)
        setZ(order);
#else
    if (zValue() != order)
        setZValue(order);
#endif
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
