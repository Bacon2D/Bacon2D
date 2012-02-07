#ifndef _SPRITESHEET_H_
#define _SPRITESHEET_H_

#include <QtQuick/QQuickPaintedItem>

class QPixmap;

class SpriteSheet : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(int frame READ frame WRITE setFrame NOTIFY frameChanged)

public:
    SpriteSheet(QQuickItem *parent = 0);

    QString source() const;
    void setSource(const QString &source);

    int frames() const;
    void setFrames(const int &frames);

    int frame() const;
    void setFrame(const int &frame);

    int initialFrame() const;
    void setInitialFrame(const int &initialFrame);

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

#endif /* _SPRITESHEET_H_ */
