#include "spritesheet.h"

#include <QtGui/QPixmap>
#include <QtGui/QPainter>

SpriteSheet::SpriteSheet(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , m_pixMap(0)
    , m_frames(0)
    , m_frame(0)
    , m_initialFrame(0)
    , m_frameWidth(0)
{
    setVisible(false);
}

QString SpriteSheet::source() const
{
    return m_source;
}

void SpriteSheet::setSource(const QString &source)
{
    if (m_source != source) {
        if (m_pixMap)
            delete m_pixMap;

        m_source = source;

        m_pixMap = new QPixmap(m_source);

        if (m_frames)
            updateSizeInfo();

        update();

        emit sourceChanged();
    }
}

void SpriteSheet::paint(QPainter *painter)
{
    if (m_pixMap) {
        if (!m_frames)
            painter->drawPixmap(0, 0, *m_pixMap);
        else
            painter->drawPixmap(0, 0, *m_pixMap, (m_frame * m_frameWidth), 0, m_frameWidth, m_pixMap->height());
    }
}

int SpriteSheet::frames() const
{
    return m_frames;
}

void SpriteSheet::setFrames(const int &frames)
{
    if (m_frames != frames) {
        m_frames = frames;

        if (m_pixMap)
            updateSizeInfo();

        update();

        emit framesChanged();
    }
}

int SpriteSheet::frame() const
{
    return m_frame;
}

void SpriteSheet::setFrame(const int &frame)
{
    if (m_frame != frame
        && frame < m_frames) { //FIXME: using qt5 and non infinite animations, the property animation updates this value to m_frames, the max should be m_frames-1
        m_frame = frame;

        update();

        emit frameChanged();
    }
}

void SpriteSheet::updateSizeInfo()
{
    m_frameWidth = m_pixMap->width() / m_frames;
    setWidth(m_frameWidth);
    setHeight(m_pixMap->height());
}

int SpriteSheet::initialFrame() const
{
    return m_initialFrame;
}

void SpriteSheet::setInitialFrame(const int &initialFrame)
{
    if (m_initialFrame != initialFrame) {
        m_initialFrame = initialFrame;

        emit initialFrameChanged();
    }
}
