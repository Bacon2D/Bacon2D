#include "gamesprite.h"

#include <QtGui/QPixmap>
#include <QtGui/QPainter>

GameSprite::GameSprite(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , m_pixMap(0)
    , m_frames(0)
    , m_frame(0)
    , m_initialFrame(0)
    , m_frameWidth(0)
{
}

QString GameSprite::source() const
{
    return m_source;
}

void GameSprite::setSource(const QString &source)
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

void GameSprite::paint(QPainter *painter)
{
    if (m_pixMap) {
        if (!m_frames)
            painter->drawPixmap(0, 0, *m_pixMap);
        else
            painter->drawPixmap(0, 0, *m_pixMap, (m_frame * m_frameWidth), 0, m_frameWidth, m_pixMap->height());
    }
}

int GameSprite::frames() const
{
    return m_frames;
}

void GameSprite::setFrames(const int &frames)
{
    if (m_frames != frames) {
        m_frames = frames;

        if (m_pixMap)
            updateSizeInfo();

        update();

        emit framesChanged();
    }
}

int GameSprite::frame() const
{
    return m_frame;
}

void GameSprite::setFrame(const int &frame)
{
    if (m_frame != frame) {
        m_frame = frame;

        update();

        emit frameChanged();
    }
}

void GameSprite::updateSizeInfo()
{
    m_frameWidth = m_pixMap->width() / m_frames;
    setWidth(m_frameWidth);
    setHeight(m_pixMap->height());
}

int GameSprite::initialFrame() const
{
    return m_initialFrame;
}

void GameSprite::setInitialFrame(const int &initialFrame)
{
    m_initialFrame = initialFrame;

    emit initialFrameChanged();
}
