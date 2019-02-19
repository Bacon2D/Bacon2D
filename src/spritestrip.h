#ifndef SPRITESTRIP_H
#define SPRITESTRIP_H

#include <QQuickItem>
#include <QPixmap>

class SpriteSheetGrid;
class Sprite;

class SpriteStrip : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(SpriteSheetGrid *spriteSheet READ spriteSheet WRITE setSpriteSheet NOTIFY spriteSheetChanged)
    Q_PROPERTY(qreal frameX READ frameX WRITE setFrameX NOTIFY frameXChanged)
    Q_PROPERTY(qreal frameY READ frameY WRITE setFrameY NOTIFY frameYChanged)
    Q_PROPERTY(qreal frameWidth READ frameWidth WRITE setFrameWidth NOTIFY frameWidthChanged)
    Q_PROPERTY(qreal frameHeight READ frameHeight WRITE setFrameHeight NOTIFY frameHeightChanged)
    Q_PROPERTY(int frame READ frame WRITE setFrame NOTIFY frameChanged)
    Q_PROPERTY(int frames READ frames WRITE setFrames NOTIFY framesChanged)
    Q_PROPERTY(int initialFrame READ initialFrame WRITE setInitialFrame NOTIFY initialFrameChanged)
    Q_PROPERTY(int finalFrame READ finalFrame WRITE setFinalFrame NOTIFY finalFrameChanged)

public:
    explicit SpriteStrip(QQuickItem *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    int frame() const;
    void setFrame(const int &frame);

    int frames() const;
    void setFrames(const int &frames);

    qreal frameX() const;
    void setFrameX(const qreal &frameX);

    qreal frameY() const;
    void setFrameY(const qreal &frameY);

    qreal frameWidth() const;
    void setFrameWidth(const qreal &frameWidth);

    qreal frameHeight() const;
    void setFrameHeight(const qreal &frameHeight);

    int initialFrame() const;
    void setInitialFrame(const int &initialFrame);

    int finalFrame() const;
    void setFinalFrame(const int &finalFrame);

    bool verticalMirror() const;
    void setVerticalMirror(const bool &verticalMirror);

    bool horizontalMirror() const;
    void setHorizontalMirror(const bool &horizontalMirror);

    int verticalScale() const;
    int horizontalScale() const;

    SpriteSheetGrid *spriteSheet();
    void setSpriteSheet(SpriteSheetGrid *spriteSheet);

    qreal currentFrameX() const;

    void componentComplete() override;

signals:
    void spriteSheetChanged();
    void nameChanged();
    void frameChanged();
    void framesChanged();
    void frameXChanged();
    void frameYChanged();
    void frameWidthChanged();
    void frameHeightChanged();
    void initialFrameChanged();
    void finalFrameChanged();
    void verticalMirrorChanged();
    void horizontalMirrorChanged();

private:
    QVector<Sprite *> m_sprites;
    SpriteSheetGrid *m_spriteSheet;
    QString m_name;
    int m_frame;
    int m_frames;
    qreal m_frameX;
    qreal m_frameY;
    qreal m_frameWidth;
    qreal m_frameHeight;
    int m_initialFrame;
    int m_finalFrame;
    int m_verticalScale;
    int m_horizontalScale;

    void updateSizeInfo();
};

#endif // SPRITESTRIP_H
