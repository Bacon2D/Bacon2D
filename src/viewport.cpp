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

#include "viewport.h"

#include "gamescene.h"

Viewport::Viewport(GameScene *parent)
    : GameItem(parent)
    , m_xOffset(0.0f)
    , m_yOffset(0.0f)
    , m_contentWidth(0.0f)
    , m_contentHeight(0.0f)
    , m_maxXOffset(0.0f)
    , m_maxYOffset(0.0f)
    , m_scene(parent)
{
    setClip(true);
}

float Viewport::xOffset()
{
    return m_xOffset;
}

void Viewport::setXOffset(float xOffset)
{
    xOffset = qBound<float>(0.0f, xOffset, m_maxXOffset);

    if (m_xOffset != xOffset) {
        m_xOffset = xOffset;

        if (m_scene)
            m_scene->setX(-m_xOffset);

        emit xOffsetChanged();
    }
}

float Viewport::yOffset()
{
    return m_yOffset;
}

void Viewport::setYOffset(float yOffset)
{
    yOffset = qBound<float>(0.0f, yOffset, m_maxYOffset);

    if (m_yOffset != yOffset) {
        m_yOffset = yOffset;

        if (m_scene)
            m_scene->setY(-m_yOffset);

        emit yOffsetChanged();
    }
}

void Viewport::hScroll(float step)
{
    setXOffset(m_xOffset + step);
}

void Viewport::vScroll(float step)
{
    setYOffset(m_yOffset + step);
}

float Viewport::contentWidth() const
{
    return m_contentWidth;
}

void Viewport::setContentWidth(const float &contentWidth)
{
    if (m_contentWidth != contentWidth) {
        m_contentWidth = contentWidth;

        emit contentWidthChanged();
    }
}

float Viewport::contentHeight() const
{
    return m_contentHeight;
}

void Viewport::setContentHeight(const float &contentHeight)
{
    if (m_contentHeight != contentHeight) {
        m_contentHeight = contentHeight;

        emit contentHeightChanged();
    }
}

void Viewport::setScene(GameScene *scene)
{
    m_scene = scene;
}

void Viewport::updateMaxOffsets()
{
    m_maxXOffset = m_contentWidth - width();
    m_maxYOffset = m_contentHeight - height();
}
