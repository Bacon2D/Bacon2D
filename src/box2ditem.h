#ifndef _BOX2DITEN_H_
#define _BOX2DITEN_H_

#include "gameitem.h"

class GameScene;
class b2World;
class b2Body;

class Box2DItem : public GameItem
{
    Q_OBJECT

public:
    enum BodyType {
        Static,
        Kinematic,
        Dynamic
    };

    Box2DItem(GameScene *parent = 0);

    b2Body *body();

    void synchronize();

    void initialize(b2World *world);

protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

private slots:
    void onRotationChanged();

private:
    b2Body *m_body;
    bool m_synchronizing;
    qreal m_linearDamping;
    qreal m_angularDamping;
    BodyType m_bodyType;
    bool m_bullet;
    bool m_sleepingAllowed;
    bool m_fixedRotation;
    bool m_active;
};

#endif /* _BOX2DITEN_H_ */
