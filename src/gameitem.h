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

#ifndef _GAMEITEM_H_
#define _GAMEITEM_H_

#include "enums.h"
#include "quasideclarativeitem.h"

#include <QtCore/QtGlobal>
#include <QtCore/QTime>

#if QT_VERSION >= 0x050000
#include <QtQml/QQmlScriptString>
class QQmlExpression;
#else
#include <QtDeclarative/QDeclarativeScriptString>
class QDeclarativeExpression;
#endif

class QuasiGame;
class GameScene;

class GameItem : public QuasiDeclarativeItem
{
    Q_OBJECT

#if QT_VERSION >= 0x050000
    Q_PROPERTY(QQmlScriptString updateScript READ updateScript WRITE setUpdateScript NOTIFY updateScriptChanged)
#else
    Q_PROPERTY(QDeclarativeScriptString updateScript READ updateScript WRITE setUpdateScript NOTIFY updateScriptChanged)
#endif
    Q_PROPERTY(int updateInterval READ updateInterval WRITE setUpdateInterval NOTIFY updateIntervalChanged)
    Q_PROPERTY(bool collided READ collided WRITE setCollided NOTIFY collidedChanged)
    Q_PROPERTY(Quasi::Ordering order READ order WRITE setOrder)
    Q_PROPERTY(QuasiGame *game READ game)

public:
    GameItem(GameScene *parent = 0);

#if QT_VERSION >= 0x050000
    QQmlScriptString updateScript() const;
    void setUpdateScript(const QQmlScriptString &updateScript);
#else
    QDeclarativeScriptString updateScript() const;
    void setUpdateScript(const QDeclarativeScriptString &updateScript);
#endif

    int updateInterval() const;
    void setUpdateInterval(const int &updateInterval);

    bool collided() const;
    void setCollided(const bool &collided);

    Quasi::Ordering order() const;
    void setOrder(Quasi::Ordering order);

    Q_INVOKABLE QList<QObject *> collidedItems() const;

    GameScene *scene() const;
    void setScene(GameScene *scene);

    QuasiGame *game() const;

    virtual void update(const long &delta);

signals:
    void updateScriptChanged();
    void updateIntervalChanged();
    void collidedChanged();

private:
#if QT_VERSION >= 0x050000
    QQmlScriptString m_updateScript;
    QQmlExpression *m_expression;
#else
    QDeclarativeScriptString m_updateScript;
    QDeclarativeExpression *m_expression;
#endif
    int m_updateInterval;
    QTime m_updateTime;
    bool m_collided;
    GameScene *m_scene;
};

#endif /* _GAMEITEM_H_ */
