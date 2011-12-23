#ifndef _GAMESPRITE_H_
#define _GAMESPRITE_H_

#include <QtQuick/QQuickPaintedItem>

class QPixmap;

class GameSprite : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(int frames READ frames WRITE setFrames NOTIFY framesChanged)
    Q_PROPERTY(int frame READ frame WRITE setFrame NOTIFY frameChanged)
    Q_PROPERTY(int initialFrame READ initialFrame WRITE setInitialFrame NOTIFY initialFrameChanged)

public:
    GameSprite(QQuickItem *parent = 0);

    QString source() const;
    void setSource(QString source);

    int frames() const;
    void setFrames(int frames);

    int frame() const;
    void setFrame(int frame);

    int initialFrame() const;
    void setInitialFrame(int initialFrame);

    void paint(QPainter *painter);

signals:
    void sourceChanged();
    void framesChanged();
    void frameChanged();
    void initialFrameChanged();

private:
    void updateSizeInfo();

private:
    QPixmap *m_pixMap;
    QString m_source;
    int m_frames;
    int m_frame;
    int m_initialFrame;
    int m_frameWidth;
};

#endif /* _GAMESPRITE_H_ */
