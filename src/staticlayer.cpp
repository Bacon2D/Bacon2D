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
    : Layer(parent)
      , m_globalXPos(0.0)
      , m_localXPos(0.0)
{
}

StaticLayer::~StaticLayer()
{
}
void StaticLayer::moveX(qreal value)
{
    m_globalXPos += value; // XXX should multiply by -1??
    m_localXPos += value;

    if (m_localXPos > 0) {
        drawPixmap();
        m_localXPos =  -width() + value;
    } else if (m_localXPos * m_factor <= -width()) {
        drawPixmap();
        m_localXPos = 0;
    }
}

void StaticLayer::paint(QPainter *painter)
{
    if (m_currentPixmap)
        painter->drawPixmap(m_localXPos * m_factor, 0, *m_currentPixmap);
}
