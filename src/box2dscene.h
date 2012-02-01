#ifndef _BOX2DSCENE_H_
#define _BOX2DSCENE_H_

#include "gamescene.h"

class b2World;
class QuasiGame;
class Box2DDebugDrawItem;

class Box2DScene : public GameScene
{
    Q_OBJECT

public:
    Box2DScene(QuasiGame *parent = 0);

    b2World *world() const;

    void setGravity(const QPointF &gravity);
    QPointF gravity() const;

    void componentComplete();

    void update(const long &delta);

protected slots:
    void onDebugChanged();

private:
    b2World *m_world;
    QPointF m_gravity;
    Box2DDebugDrawItem *m_debugDraw;
};

#endif /* _BOX2DSCENE_H_ */
