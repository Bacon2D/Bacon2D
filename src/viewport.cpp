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
    xOffset = xOffset > m_maxXOffset ? m_maxXOffset : xOffset;

    if (xOffset < 0.0f)
        xOffset = 0.0f;

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
    yOffset = yOffset > m_maxYOffset ? m_maxYOffset : yOffset;
    if (yOffset < 0.0f)
        yOffset = 0.0f;

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
