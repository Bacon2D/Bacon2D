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

#ifndef _BOX2DJOINTITEM_H_
#define _BOX2DJOINTITEM_H_

#include "box2dbaseitem.h"
#include "gameitem.h"

class Box2DItem;

class Box2DJointItem : public Box2DBaseItem
{
    Q_OBJECT

    Q_PROPERTY(Box2DItem *box2ditemA READ box2ditemA WRITE setBox2ditemA NOTIFY box2ditemAChanged)
    Q_PROPERTY(Box2DItem *box2ditemB READ box2ditemB WRITE setBox2ditemB NOTIFY box2ditemBChanged)
    Q_PROPERTY(bool collideConnected READ collideConnected WRITE setCollideConnected NOTIFY collideConnectedChanged)

public:
    Box2DJointItem(GameScene *parent = 0);

    Box2DItem *box2ditemA() const;
    void setBox2ditemA(Box2DItem *box2ditemA);

    Box2DItem *box2ditemB() const;
    void setBox2ditemB(Box2DItem *box2ditemB);

    bool collideConnected() const;
    void setCollideConnected(const bool &collideConnected);

signals:
    void box2ditemAChanged();
    void box2ditemBChanged();
    void collideConnectedChanged();

protected:
    Box2DItem *m_box2ditemA;
    Box2DItem *m_box2ditemB;
    bool m_collideConnected;
};

#endif /* _BOX2DJOINTITEM_H_ */
