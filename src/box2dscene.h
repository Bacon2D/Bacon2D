#ifndef _BOX2DSCENE_H_
#define _BOX2DSCENE_H_

#include "gamescene.h"

class b2World;

class Box2DScene : public GameScene
{
    Q_OBJECT

public:
    Box2DScene(QQuickItem *parent = 0);

    b2World *world();

    void setGravity(QPointF gravity);
    QPointF gravity();

    void componentComplete();

public slots:
    void update(long delta);

private:
    b2World *m_world;
    QPointF m_gravity;
};

#endif /* _BOX2DSCENE_H_ */
