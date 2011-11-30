#ifndef _GAMEITEM_H_
#define _GAMEITEM_H_

#include <QtDeclarative>

class GameItem : public QQuickItem
{
    Q_OBJECT

public:
    GameItem(QQuickItem *parent = 0);
};

#endif /* _GAMEITEM_H_ */
