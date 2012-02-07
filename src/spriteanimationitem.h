#ifndef _SPRITEANIMATIONITEM_H_
#define _SPRITEANIMATIONITEM_H_

#include <QState>

class SpriteSheet;
class QPropertyAnimation;

class SpriteSheet;

class SpriteAnimationItem : public QState
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(int frames READ frames WRITE setFrames NOTIFY framesChanged)
    Q_PROPERTY(int frame READ frame WRITE setFrame NOTIFY frameChanged)
    Q_PROPERTY(int initialFrame READ initialFrame WRITE setInitialFrame NOTIFY initialFrameChanged)
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(int loops READ loops WRITE setLoops NOTIFY loopsChanged)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(int duration READ duration WRITE setDuration NOTIFY durationChanged)

public:
    SpriteAnimationItem(QState *parent = 0);

    QString name() const;
    void setName(const QString &name);

    bool running() const;
    void setRunning(const bool &running);

    int loops() const;
    void setLoops(const int &loops);

    QString source() const;
    void setSource(const QString &source);

    int frames() const;
    void setFrames(const int &frames);

    int frame() const;
    void setFrame(const int &frame);

    int initialFrame() const;
    void setInitialFrame(const int &initialFrame);

    bool visible() const;
    void setVisible(const bool &visible);

    int duration() const;
    void setDuration(const int &duration);

    SpriteSheet *spriteSheet();

signals:
    void runningChanged();
    void loopsChanged();
    void sourceChanged();
    void framesChanged();
    void frameChanged();
    void initialFrameChanged();
    void visibleChanged();
    void durationChanged();
    void finished();

private:
    QString m_name;
    SpriteSheet *m_spriteSheet;
    QPropertyAnimation *m_spriteAnimation;
};

#endif /* _SPRITEANIMATIONITEM_H_ */
