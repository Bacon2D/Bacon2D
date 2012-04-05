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

#ifndef _STATICLAYER_H_
#define _STATICLAYER_H_

#include "layer.h"

#include <QtCore/QtGlobal>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>

class StaticLayer : public Layer
{
    Q_OBJECT

public:
    StaticLayer(Layer *parent = 0);
    ~StaticLayer();

    void moveX(const qreal &x);
    void moveY(const qreal &y);

#if QT_VERSION >= 0x050000
    void paint(QPainter *painter);
#else
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
#endif

private:
    qreal m_globalXPos; // global positioning
    qreal m_globalYPos;
    qreal m_localXPos; // local positioning
    qreal m_localYPos;
};

#endif /* _STATICLAYER_H_ */
