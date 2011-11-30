#ifndef _GAMEITEM_H_
#define _GAMEITEM_H_

#include <QtDeclarative>

class GameItem : public QQuickItem
{
    Q_OBJECT

public:
    GameItem(QQuickItem *parent = 0);

public slots:
    virtual void update(long delta);
};

#endif /* _GAMEITEM_H_ */
