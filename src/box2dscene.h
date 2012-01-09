#ifndef _BOX2DSCENE_H_
#define _BOX2DSCENE_H_

#include "gamescene.h"

class b2World;

static const float scaleRatio = 32.0f; // 32 pixels in one meter

class Box2DScene : public GameScene
{
    Q_OBJECT

public:
    Box2DScene(QQuickItem *parent = 0);

    b2World *world();

    void setGravity(QPointF gravity);
    QPointF gravity();

public slots:
    void update(long delta);
    void onGameItemAdded(GameItem* gameItem);

private:
    b2World *m_world;
    QPointF m_gravity;
};

#endif /* _BOX2DSCENE_H_ */
