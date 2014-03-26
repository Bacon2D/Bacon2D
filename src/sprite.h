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

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "entity.h"

#include <QtCore/QHash>
#include <QtCore/QStateMachine>

class Scene;
class SpriteAnimation;

class Sprite : public Entity
{
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<SpriteAnimation> animations READ animations)
    Q_PROPERTY(QString animation READ animation WRITE setAnimation NOTIFY animationChanged)
    Q_PROPERTY(bool verticalMirror READ verticalMirror WRITE setVerticalMirror NOTIFY verticalMirrorChanged)
    Q_PROPERTY(bool horizontalMirror READ horizontalMirror WRITE setHorizontalMirror NOTIFY horizontalMirrorChanged)

public:
    Sprite(Scene *parent = 0);

    QQmlListProperty<SpriteAnimation> animations() const;

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
    static void append_animation(QQmlListProperty<SpriteAnimation> *list, SpriteAnimation *animation);

    QStateMachine *m_stateMachine;
    QState *m_stateGroup;
    QHash<QString, SpriteAnimation *> m_states;
    QString m_animation;
    bool m_verticalMirror;
    bool m_horizontalMirror;
};

#endif /* _SPRITE_H_ */
