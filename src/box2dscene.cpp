#include "box2dscene.h"

#include "box2ditem.h"
#include "box2dbaseitem.h"

#include <Box2D/Box2D.h>

Box2DScene::Box2DScene(QQuickItem *parent)
    : GameScene(parent)
    , m_world(0)
    , m_gravity(qreal(0), qreal(-10))
{
    const b2Vec2 gravity(m_gravity.x(), m_gravity.y());

    m_world = new b2World(gravity);
}

b2World *Box2DScene::world() const
{
    return m_world;
}

void Box2DScene::setGravity(const QPointF &gravity)
{
    m_gravity = gravity;
    if (m_world)
        m_world->SetGravity(b2Vec2(gravity.x(), gravity.y()));
}

QPointF Box2DScene::gravity() const
{
    return m_gravity;
}

void Box2DScene::update(const long &delta)
{
    if (!m_running)
        return;

    GameScene::update(delta);

    // TODO crete properties for this arguments
    m_world->Step(1.0f / 60.0f, 10, 10);

    GameItem *item;

    foreach (item, m_gameItems) {
        item->update(delta);
        if (Box2DBaseItem *box2DItem = dynamic_cast<Box2DBaseItem *>(item))
            box2DItem->synchronize();
    }
}

void Box2DScene::componentComplete()
{
    QQuickItem::componentComplete();

    foreach (GameItem *item, m_gameItems) {
        if (Box2DBaseItem *box2DItem = dynamic_cast<Box2DBaseItem *>(item))
            box2DItem->initialize(m_world);
    }
}
