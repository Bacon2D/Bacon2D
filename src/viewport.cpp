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
#include "scene.h"

Viewport::Viewport(Scene *parent)
    : Entity(parent)
    , m_animationEasingCurve(QEasingCurve::Linear)
    , m_xOffset(0.0f)
    , m_yOffset(0.0f)
    , m_contentWidth(0.0f)
    , m_contentHeight(0.0f)
    , m_maxXOffset(0.0f)
    , m_maxYOffset(0.0f)
    , m_scene(parent)
    , m_animationDuration(100)
{
    m_xGroupAnimation = new QParallelAnimationGroup(this);
    m_yGroupAnimation = new QParallelAnimationGroup(this);
}

float Viewport::xOffset()
{
    return m_xOffset;
}

void Viewport::setXOffset(float xOffset)
{
    xOffset = qBound<float>(0.0f, xOffset, m_maxXOffset);

    // TODO create a heuristic function to calculate the animation duration
    // when m_animationDuration < 0, according to this delta
    // (bigger delta -> bigger animation duration)
    //qreal delta = qAbs(m_xOffset - xOffset);

    if (m_xOffset != xOffset) {
        m_xOffset = xOffset;

        if (m_scene) {
            m_xGroupAnimation->clear();

            QPropertyAnimation *xAnim = new QPropertyAnimation(m_scene, "x");
            xAnim->setDuration(m_animationDuration); // TODO set duration according the offset value
            xAnim->setEasingCurve(m_animationEasingCurve);
            xAnim->setStartValue(m_scene->x());
            xAnim->setEndValue(-m_xOffset);
            m_xGroupAnimation->addAnimation(xAnim);

            /* TODO: Fix this according to current layer scheme
            QPropertyAnimation *xLayerAnimation = new QPropertyAnimation(m_scene->gameLayers(), "xOffset"); // TODO
            xLayerAnimation->setDuration(m_animationDuration); // TODO
            xLayerAnimation->setEasingCurve(m_animationEasingCurve);
            xLayerAnimation->setStartValue(m_scene->gameLayers()->xOffset());
            xLayerAnimation->setEndValue(m_xOffset);
            m_xGroupAnimation->addAnimation(xLayerAnimation);
            */

            m_xGroupAnimation->start();
        }

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

        if (m_scene) {
            m_yGroupAnimation->clear();

            QPropertyAnimation *yAnim = new QPropertyAnimation(m_scene, "y");
            yAnim->setDuration(m_animationDuration); // TODO set duration according the offset value
            yAnim->setEasingCurve(m_animationEasingCurve);
            yAnim->setStartValue(m_scene->y());
            yAnim->setEndValue(-m_yOffset);
            m_yGroupAnimation->addAnimation(yAnim);

            /* TODO: Fix this according to current layer scheme
            QPropertyAnimation *yLayerAnimation = new QPropertyAnimation(m_scene->gameLayers(), "yOffset"); // TODO
            yLayerAnimation->setDuration(m_animationDuration); // TODO
            yLayerAnimation->setEasingCurve(m_animationEasingCurve);
            yLayerAnimation->setStartValue(m_scene->gameLayers()->yOffset());
            yLayerAnimation->setEndValue(m_yOffset);
            m_yGroupAnimation->addAnimation(yLayerAnimation);
            */

            m_yGroupAnimation->start();
        }

        emit yOffsetChanged();
    }
}

void Viewport::hScroll(float step)
{
    setXOffset(step);
}

void Viewport::vScroll(float step)
{
    setYOffset(step);
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

int Viewport::animationDuration() const
{
    return m_animationDuration;
}

void Viewport::setAnimationDuration(const int &animationDuration)
{
    if (m_animationDuration != animationDuration) {
        m_animationDuration = animationDuration;

        emit animationDurationChanged();
    }
}

void Viewport::setScene(Scene *scene)
{
    m_scene = scene;
}

void Viewport::updateMaxOffsets()
{
    m_maxXOffset = m_contentWidth - width();
    m_maxYOffset = m_contentHeight - height();
}
