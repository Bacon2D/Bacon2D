#ifndef _GAMEANIMATEDBACKGROUND_H_
#define _GAMEANIMATEDBACKGROUND_H_

#include <QtGui/QPixmap>
#include <QtGui/QPainter>

#include "gamebasebackground.h"

class GameAnimatedBackground : public GameBaseBackground
{
    Q_OBJECT

    Q_ENUMS(Direction Type)

    Q_PROPERTY(int horizontalOffset READ horizontalOffset WRITE setHorizontalOffset NOTIFY horizontalOffsetChanged)
    Q_PROPERTY(Direction direction READ direction WRITE setDirection NOTIFY directionChanged)
    Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeChanged)

public:
    enum Direction {
        Backward = 0, // -1 returns undefined on QML :(
        Forward = 1
    };

    enum Type {
        Infinite,
        Mirrored
    };

    GameAnimatedBackground(GameBaseBackground *parent = 0);
    ~GameAnimatedBackground();

    int horizontalOffset() const { return m_horizontalOffset; };
    void setHorizontalOffset(const int &offset);

    Direction direction() const { return m_direction; };
    void setDirection(const Direction &direction);

    Type type() const { return m_type; };
    void setType(const Type &type);

    void drawPixmap();
    void paint(QPainter *painter);

public slots:
    void updateTiles();

signals:
    void horizontalOffsetChanged();
    void directionChanged();
    void typeChanged();

private:
    int m_horizontalOffset;
    int m_columnOffset;
    Direction m_direction;
    Type m_type;

    bool m_drawingMirrored;
    bool m_shouldMirror;

    QList<QPixmap> m_mirroredTiles;
};

#endif /* _GAMEBACKGROUND_H_ */
