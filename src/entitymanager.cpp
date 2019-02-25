#include "entitymanager.h"
#include "entity.h"
#include "scene.h"
#include "physicsentity.h"
#include "private/entitymanagersingleton.h"

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
    Entity *entity = EntityManagerSingleton::instance().createEntity(item, m_parentScene, qmlEngine(this));
    if (initialCount != entityCount())
        emit entityCountChanged();

    return entity;
}

Entity *EntityManager::findEntity(const QString &entityType, const QString &property, const QVariant &value)
{
    return EntityManagerSingleton::instance().findEntity(entityType, property, value);
}

Entity *EntityManager::getEntity(const QString &entityId)
{
    return EntityManagerSingleton::instance().getEntity(entityId);
}

void EntityManager::destroyEntity(const QString &entityId)
{
    const int initialCount = EntityManagerSingleton::instance().entityCount();
    EntityManagerSingleton::instance().destroyEntity(entityId);
    if (initialCount != entityCount())
        emit entityCountChanged();
}

int EntityManager::entityCount() const
{
    return EntityManagerSingleton::instance().entityCount();
}

int EntityManager::getEntityCount(const QString &entityType)
{
    return EntityManagerSingleton::instance().entityCount(entityType);
}

void EntityManager::destroyAllEntities(const QString &entityType)
{
    EntityManagerSingleton::instance().destroyAllEntities(entityType);
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
