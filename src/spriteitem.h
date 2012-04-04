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

#include "gameitem.h"

#include <QtCore/QHash>
#include <QtCore/QStateMachine>

class GameScene;
class SpriteAnimationItem;

class SpriteItem : public GameItem
{
    Q_OBJECT

#if QT_VERSION >= 0x050000
    Q_PROPERTY(QQmlListProperty<SpriteAnimationItem> animations READ animations)
#else
    Q_PROPERTY(QDeclarativeListProperty<SpriteAnimationItem> animations READ animations)
#endif
    Q_PROPERTY(QString animation READ animation WRITE setAnimation NOTIFY animationChanged)
    Q_PROPERTY(bool verticalMirror READ verticalMirror WRITE setVerticalMirror NOTIFY verticalMirrorChanged)
    Q_PROPERTY(bool horizontalMirror READ horizontalMirror WRITE setHorizontalMirror NOTIFY horizontalMirrorChanged)

public:
    SpriteItem(GameScene *parent = 0);

#if QT_VERSION >= 0x050000
    QQmlListProperty<SpriteAnimationItem> animations() const;
#else
    QDeclarativeListProperty<SpriteAnimationItem> animations() const;
#endif

    QString animation() const;
    void setAnimation(const QString &animation, const bool &force = false);

    bool verticalMirror() const;
    void setVerticalMirror(const bool &verticalMirror);

    bool horizontalMirror() const;
    void setHorizontalMirror(const bool &horizontalMirror);

public slots:
    void initializeAnimation();

signals:
    void animationChanged();
    void verticalMirrorChanged();
    void horizontalMirrorChanged();

private:
    void initializeMachine();

private:
#if QT_VERSION >= 0x050000
    static void append_animation(QQmlListProperty<SpriteAnimationItem> *list, SpriteAnimationItem *animation);
#else
    static void append_animation(QDeclarativeListProperty<SpriteAnimationItem> *list, SpriteAnimationItem *animation);
#endif

    QStateMachine *m_stateMachine;
    QState *m_stateGroup;
    QHash<QString, SpriteAnimationItem *> m_states;
    QString m_animation;
    bool m_verticalMirror;
    bool m_horizontalMirror;
};

#endif /* _SPRITEITEM_H_ */
