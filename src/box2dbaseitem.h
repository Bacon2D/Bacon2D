#ifndef _BOX2DBASEITEM_H_
#define _BOX2DBASEITEM_H_

#include "gameitem.h"
#include "box2dscene.h" // FIXME remove this include and remove scaleRatio from gameScene, make it a constant member of Box2DBaseItem

class b2World;
struct b2Vec2;

class Box2DBaseItem : public GameItem
{
    Q_OBJECT

public:
    Box2DBaseItem(GameScene *parent = 0);

    bool initialized();

    virtual void initialize(b2World *world) = 0;

    void synchronize();

protected:
    virtual b2Vec2 b2TransformOrigin() = 0;
    virtual float b2Angle() = 0;

protected:
    bool m_initialized;
    bool m_synchronizing;
    bool m_synchronize;
};

#endif /* _BOX2DBASEITEM_H_ */
