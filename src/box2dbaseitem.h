#ifndef _BOX2DBASEITEM_H_
#define _BOX2DBASEITEM_H_

#include "gameitem.h"

class b2World;

class Box2DBaseItem : public GameItem
{
    Q_OBJECT

public:
    Box2DBaseItem(GameScene *parent = 0)
        : GameItem(parent)
        , m_initialized(false)
        {
        }

    bool initialized() { return m_initialized;  }

    virtual void initialize(b2World *world) = 0;

protected:
    bool m_initialized;
};

#endif /* _BOX2DBASEITEM_H_ */
