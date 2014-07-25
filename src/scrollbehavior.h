/**
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
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

#ifndef _SCROLLBEHAVIOR_H_
#define _SCROLLBEHAVIOR_H_

#include "scrollbehaviorimpl.h"

class ScrollBehavior : public Behavior
{
    Q_OBJECT

    Q_PROPERTY(qreal horizontalStep READ horizontalStep WRITE setHorizontalStep)
    Q_PROPERTY(qreal verticalStep READ verticalStep WRITE setVerticalStep)

public:
    ScrollBehavior(QObject *parent = 0);

    virtual void update(const int &delta);
    virtual void setTarget(QQuickItem *target);

    qreal horizontalStep();
    void setHorizontalStep(qreal step);

    qreal verticalStep();
    void setVerticalStep(qreal step);

private:
    ScrollBehaviorImpl *m_currentBehavior;
    qreal m_horizontalStep;
    qreal m_verticalStep;
};

#endif
