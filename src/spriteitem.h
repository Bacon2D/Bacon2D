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

#ifndef _SPRITEITEM_H_
#define _SPRITEITEM_H_

#include <QHash>
#include <QStateMachine>

#include "gameitem.h"

class GameScene;
class SpriteAnimationItem;

class SpriteItem : public GameItem
{
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<SpriteAnimationItem> animations READ animations)
    Q_PROPERTY(QString animation READ animation WRITE setAnimation NOTIFY animationChanged)

public:
    SpriteItem(GameScene *parent = 0);

    QQmlListProperty<SpriteAnimationItem> animations() const;

    QString animation() const;
    void setAnimation(const QString &animation, const bool &force = false);

public slots:
    void initializeAnimation();

signals:
    void animationChanged();

private:
    void initializeMachine();

private:
    static void append_animation(QQmlListProperty<SpriteAnimationItem> *list, SpriteAnimationItem *animation);

    QStateMachine *m_stateMachine;
    QState *m_stateGroup;
    QHash<QString, SpriteAnimationItem *> m_states;
    QString m_animation;
};

#endif /* _SPRITEITEM_H_ */
