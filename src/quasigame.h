#ifndef _QUASIGAME_H_
#define _QUASIGAME_H_

#include <QtDeclarative>

class QuasiGame : public QQuickItem
{
    Q_OBJECT

public:
    QuasiGame(QQuickItem *parent = 0);

signals:
    void update(long delta);
};

#endif /* _QUASIGAME_H_ */
