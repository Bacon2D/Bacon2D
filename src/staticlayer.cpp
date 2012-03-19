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

#include "staticlayer.h"

StaticLayer::StaticLayer(Layer *parent)
    : Layer((QuasiDeclarativeItem *)parent)
    , m_globalXPos(0.0)
    , m_localXPos(0.0)
    , m_localYPos(0.0)
{
}

StaticLayer::~StaticLayer()
{
}

// move to a X value
void StaticLayer::moveX(const qreal &x)
{
    qreal newValue = x * m_factor;
    qreal delta = m_globalXPos + newValue;

    m_globalXPos = newValue * -1;
    m_localXPos -= delta;

    if (m_localXPos <= -width()) {
            drawPixmap();
            m_localXPos =  width() + m_localXPos;
    } else if (m_localXPos >= 0) {
        if (m_globalXPos != 0) {
            drawPixmap();
            m_localXPos =  -width() + m_localXPos;
        } else
            m_localXPos = 0;
    }
}

#include <QDebug>
void StaticLayer::moveY(const qreal &y)
{
    Q_UNUSED(y);
    // TODO
    qDebug() << "I WILL KILL YOUR WHOLE FAMILY!!";
}

#if QT_VERSION >= 0x050000
void StaticLayer::paint(QPainter *painter)
{
#else
void StaticLayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
#endif
    if (m_currentImage)
        painter->drawImage(m_localXPos, 0, *m_currentImage);
}
