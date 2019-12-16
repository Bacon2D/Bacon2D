#include "spritestrip.h"
#include "spritesheetgrid.h"
#include "sprite.h"

#include <QPainter>
#include <QQmlProperty>

SpriteStrip::SpriteStrip(QQuickItem *parent)
    : QQuickItem(parent)
    , m_spriteSheet(nullptr)
    , m_frame(-1)
    , m_frames(0)
    , m_frameX(0.0)
    , m_frameY(0.0)
    , m_frameWidth(0.0)
    , m_frameHeight(0.0)
    , m_initialFrame(0)
    , m_finalFrame(-1)
    , m_verticalScale(1)
    , m_horizontalScale(1)
{
}

QString SpriteStrip::name() const
{
    return m_name;
}

void SpriteStrip::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged();
}

int SpriteStrip::frame() const
{
    return m_frame;
}

void SpriteStrip::setFrame(const int &frame)
{
    if (m_frame == frame && frame >= m_frames)
        return;

    m_frame = frame;
    emit frameChanged();
}

int SpriteStrip::frames() const
{
    return m_frames;
}

void SpriteStrip::setFrames(const int &frames)
{
    if (m_frames != frames) {
        m_frames = frames;

        if (m_finalFrame <= 0)
            m_finalFrame = m_frames - 1;

        updateSizeInfo();

        emit framesChanged();
    }
}

void SpriteStrip::updateSizeInfo()
{
    if ((m_spriteSheet && m_spriteSheet->pixmap().isNull())
            || (m_frames <= 0 && m_spriteSheet && m_spriteSheet->horizontalFrameCount() <= 0))
        return;

    if (m_spriteSheet) {
        setImplicitWidth(m_spriteSheet->frameWidth());
        setImplicitHeight(m_spriteSheet->frameHeight());
    }
}

qreal SpriteStrip::frameX() const
{
    return m_frameX;
}

void SpriteStrip::setFrameX(const qreal &frameX)
{
    if (m_frameX == frameX)
        return;

    m_frameX = frameX;
    emit frameXChanged();
}

qreal SpriteStrip::frameY() const
{
    return m_frameY;
}

void SpriteStrip::setFrameY(const qreal &frameY)
{
    if (m_frameY == frameY)
        return;

    m_frameY = frameY;
    emit frameYChanged();
}

qreal SpriteStrip::frameWidth() const
{
    return m_frameWidth;
}

void SpriteStrip::setFrameWidth(const qreal &frameWidth)
{
    if (m_frameWidth == frameWidth)
        return;

    m_frameWidth = frameWidth;
    emit frameWidthChanged();
}

qreal SpriteStrip::frameHeight() const
{
    return m_frameHeight;
}

void SpriteStrip::setFrameHeight(const qreal &frameHeight)
{
    if (m_frameHeight == frameHeight)
        return;

    m_frameHeight = frameHeight;
    emit frameHeightChanged();
}

int SpriteStrip::initialFrame() const
{
    return m_initialFrame;
}

void SpriteStrip::setInitialFrame(const int &initialFrame)
{
    if (m_initialFrame == initialFrame)
        return;

    m_initialFrame = initialFrame;
    emit initialFrameChanged();
}

int SpriteStrip::finalFrame() const
{
    return m_finalFrame == -1 ? m_frames - 1 : m_finalFrame;
}

void SpriteStrip::setFinalFrame(const int &finalFrame)
{
    if (m_finalFrame == finalFrame)
        return;

    m_finalFrame = finalFrame;
    emit finalFrameChanged();
}

bool SpriteStrip::verticalMirror() const
{
    return m_verticalScale == -1;
}

void SpriteStrip::setVerticalMirror(const bool &verticalMirror)
{
    const bool currentState = this->verticalMirror();
    if (currentState == verticalMirror)
        return;

    m_verticalScale = verticalMirror ? -1 : 1;
    emit verticalMirrorChanged();
}

bool SpriteStrip::horizontalMirror() const
{
    return m_horizontalScale == -1;
}

void SpriteStrip::setHorizontalMirror(const bool &horizontalMirror)
{
    const bool currentState = this->horizontalMirror();
    if (currentState == horizontalMirror)
        return;

    m_horizontalScale = horizontalMirror ? -1 : 1;
    emit horizontalMirrorChanged();
}

int SpriteStrip::verticalScale() const
{
    return m_verticalScale;
}

int SpriteStrip::horizontalScale() const
{
    return m_horizontalScale;
}

SpriteSheetGrid *SpriteStrip::spriteSheet()
{
    return m_spriteSheet;
}

void SpriteStrip::setSpriteSheet(SpriteSheetGrid *spriteSheet)
{
    if (m_spriteSheet == spriteSheet)
        return;

    if (m_spriteSheet) {
        disconnect(m_spriteSheet, &SpriteSheetGrid::widthChanged, this, &SpriteStrip::updateSizeInfo);
        disconnect(m_spriteSheet, &SpriteSheetGrid::heightChanged, this, &SpriteStrip::updateSizeInfo);
        disconnect(m_spriteSheet, &SpriteSheetGrid::verticalFrameCountChanged, this, &SpriteStrip::updateSizeInfo);
    }

    m_spriteSheet = spriteSheet;

    if (m_spriteSheet) {
        if (m_frames <= 0)
            setFrames(m_spriteSheet->horizontalFrameCount());
        if (m_frameWidth <= 0.0 && m_frames > 0)
            setFrameWidth(m_spriteSheet->width() / m_frames);
        if (m_frameHeight <= 0.0)
            setFrameHeight(m_spriteSheet->frameHeight());

        setImplicitWidth(m_spriteSheet->frameWidth());
        setImplicitHeight(m_spriteSheet->frameHeight());

        if (!widthValid())
            setWidth(implicitWidth());
        if (!heightValid())
            setHeight(implicitHeight());

        connect(m_spriteSheet, &SpriteSheetGrid::widthChanged, this, &SpriteStrip::updateSizeInfo);
        connect(m_spriteSheet, &SpriteSheetGrid::heightChanged, this, &SpriteStrip::updateSizeInfo);
        connect(m_spriteSheet, &SpriteSheetGrid::verticalFrameCountChanged, this, &SpriteStrip::updateSizeInfo);
    } else {
        setImplicitWidth(m_frameWidth);
        setImplicitHeight(m_frameHeight);
    }

    emit spriteSheetChanged();
}

qreal SpriteStrip::currentFrameX() const
{
    if (m_frame >= 0 && m_frame < m_frames) {
        const int currentFrame = qBound(m_initialFrame, m_frame, m_finalFrame);
        return horizontalMirror() ? ((m_frames - 1) * m_frameWidth) - (currentFrame * m_frameWidth)
                                  : m_frameX + (currentFrame * m_frameWidth);
    }

    return 0.0;
}
