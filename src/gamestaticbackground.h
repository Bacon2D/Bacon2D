#ifndef _GAMESTATICBACKGROUND_H_
#define _GAMESTATICBACKGROUND_H_

#include <QtGui/QPixmap>
#include <QtGui/QPainter>

#include "gamebasebackground.h"

class GameStaticBackground : public GameBaseBackground
{
    Q_OBJECT

public:
    GameStaticBackground(GameBaseBackground *parent = 0);
    ~GameStaticBackground();

    void drawPixmap();
    void paint(QPainter *painter);

public slots:
    void updateTiles();

private:
    QList<QPixmap> m_mirroredTiles;
};

#endif /* _GAMESTATICBACKGROUND_H_ */
