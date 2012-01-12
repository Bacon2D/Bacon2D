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

    connect(this, SIGNAL(gameItemAdded(GameItem*)), SLOT(onGameItemAdded(GameItem*)));
}

b2World *Box2DScene::world()
{
    return m_world;
}

void Box2DScene::setGravity(QPointF gravity)
{
    m_gravity = gravity;
    if (m_world)
        m_world->SetGravity(b2Vec2(gravity.x(), gravity.y()));
}

QPointF Box2DScene::gravity()
{
    return m_gravity;
}

void Box2DScene::update(long delta)
{
    if (!m_running)
        return;

    GameScene::update(delta);

    // TODO crete properties for this arguments
    m_world->Step(1.0f / 60.0f, 10, 10);

    GameItem *item;

    foreach (item, m_gameItems) {
        item->update(delta);
        if (Box2DBaseItem* baseItem = dynamic_cast<Box2DBaseItem*>(item)) {
            if (!baseItem->initialized())
                baseItem->initialize(m_world);
            if (Box2DItem *box2DItem = dynamic_cast<Box2DItem *>(item))
                box2DItem->synchronize();
        }
    }
}

void Box2DScene::onGameItemAdded(GameItem* gameItem)
{
    Box2DBaseItem *box2DItem = dynamic_cast<Box2DBaseItem *>(gameItem);
    if (box2DItem && !box2DItem->initialized())
        box2DItem->initialize(m_world);
}
