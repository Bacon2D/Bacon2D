#include "entitymanager.h"
#include "entity.h"
#include "scene.h"
#include "physicsentity.h"
#include "private/entityfactory.h"

#include <QMap>
#include <QCoreApplication>
#include <QQmlComponent>
#include <QDebug>
#include <QtQml>
#include <QFileInfo>
#include <QQmlIncubator>

EntityManager::EntityManager(QQuickItem *parent)
    : QQuickItem(parent)
    , m_parentScene(nullptr)
{
}

Entity *EntityManager::createEntity(const QVariant &item)
{
    const int initialCount = entityCount();
    Entity *entity = EntityFactory::instance().createEntity(item, m_parentScene, qmlEngine(this));
    if (initialCount != entityCount())
        emit entityCountChanged();

    return entity;
}

Entity *EntityManager::findEntity(const QString &entityType, const QVariantMap &properties)
{
    return EntityFactory::instance().findEntity(entityType, properties);
}

Entity *EntityManager::getEntity(const QString &entityId)
{
    return EntityFactory::instance().getEntity(entityId);
}

void EntityManager::destroyEntity(const QString &entityId)
{
    const int initialCount = EntityFactory::instance().entityCount();
    EntityFactory::instance().destroyEntity(entityId);
    if (initialCount != entityCount())
        emit entityCountChanged();
}

int EntityManager::entityCount() const
{
    return EntityFactory::instance().entityCount();
}

int EntityManager::getEntityCount(const QString &entityType)
{
    return EntityFactory::instance().entityCount(entityType);
}

void EntityManager::destroyAllEntities(const QString &entityType)
{
    EntityFactory::instance().destroyAllEntities(entityType);
}

Scene *EntityManager::parentScene() const
{
    return m_parentScene;
}

void EntityManager::setParentScene(Scene *parentScene)
{
    if (m_parentScene == parentScene)
        return;

    if (m_parentScene)
        m_parentScene->disconnect(this);

    m_parentScene = parentScene;

    if (m_parentScene)
        connect(m_parentScene, &Scene::destroyed, [this]() { destroyAllEntities(); });

    emit parentSceneChanged();
}

void EntityManager::componentComplete()
{
    QQuickItem::componentComplete();

    if (!m_parentScene) {
        m_parentScene = qobject_cast<Scene *>(parentItem());
        if (m_parentScene)
            connect(m_parentScene, &Scene::destroyed, [this]() { destroyAllEntities(); });
    }
}
