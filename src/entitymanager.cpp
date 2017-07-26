#include "entitymanager.h"
#include "entity.h"
#include "scene.h"
#include <QMap>
#include <QCoreApplication>
#include <QQmlComponent>
#include <QDebug>
#include <QtQml>

EntityManagerSingleton *EntityManagerSingleton::m_entityManagerSingleton = nullptr;

EntityManagerSingleton::EntityManagerSingleton(QObject *parent)
    : QObject(parent)
{

}

EntityManagerSingleton &EntityManagerSingleton::instance()
{
    if (!m_entityManagerSingleton) {
        m_entityManagerSingleton = new EntityManagerSingleton;
        connect(qApp, &QCoreApplication::aboutToQuit, m_entityManagerSingleton, &EntityManagerSingleton::deleteLater);
    }

    return *m_entityManagerSingleton;
}

Entity *EntityManagerSingleton::createEntity(const QVariant &item, QQuickItem *parentScene, QQmlEngine *engine)
{
    if (item.isNull())
        return nullptr;

    if (item.type() == QVariant::String)
    {
        const QUrl source = item.toUrl();

        QQmlComponent component(engine, source);
        Entity *entity = qobject_cast<Entity *>(component.create(QQmlEngine::contextForObject(parentScene)));
        if (entity)
            entity->setParentItem(parentScene);
        return addEntity(entity);
    }

    QQmlComponent *component = qvariant_cast<QQmlComponent *>(item);
    if (component)
    {
        Entity *entity = qobject_cast<Entity *>(component->create(QQmlEngine::contextForObject(parentScene)));
        if (entity)
            entity->setParentItem(parentScene);
        return addEntity(entity);
    }

    return nullptr;
}

Entity *EntityManagerSingleton::addEntity(Entity *entity)
{
    if (!entity) {
        qWarning() << "Bacon2D: Entity is null.";
        return nullptr;
    }
    if (m_entityMap.contains(entity->entityId())) {
        qWarning() << "Bacon2D: Entity already exists.";
        //QMetaObject::invokeMethod(entity, "destroy");
        entity->deleteLater();
        return nullptr;
    }

    const QString entityId = generateId(entity->entityType());
    entity->setEntityId(entityId);
    m_entityMap.insert(entityId, entity);
    QStringList entityList = m_groupMap.value(entity->entityType());
    entityList.append(entity->entityId());
    m_groupMap.insert(entity->entityType(), entityList);

    return entity;
}

Entity *EntityManagerSingleton::getEntity(const QString &entityId)
{
    return m_entityMap.value(entityId);
}

void EntityManagerSingleton::removeEntity(const QString &entityId)
{
    Entity *entity = m_entityMap.take(entityId);
    //QMetaObject::invokeMethod(entity, "destroy");
    entity->deleteLater();
}

int EntityManagerSingleton::entityCount(const QString &entityType)
{
    if (entityType.isEmpty())
        return m_entityMap.count();

    return m_groupMap.value(entityType).count();
}

QString EntityManagerSingleton::generateId(const QString &entityType) const
{
    QString baseName = entityType;
    QString entityId;
    baseName.replace("%", "%%");
    if (baseName.isEmpty())
        baseName = "entity_%1";
    else
        baseName += "_%1";

    int index = 0;
    do {
        entityId = QString(baseName).arg(QString::number(index++));
    } while (m_entityMap.contains(entityId));

    baseName.replace("%%", "%");

    return entityId;
}

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

Entity *EntityManager::getEntity(const QString &entityId)
{
    return EntityManagerSingleton::instance().getEntity(entityId);
}

void EntityManager::removeEntity(const QString &entityId)
{
    EntityManagerSingleton::instance().removeEntity(entityId);
}

int EntityManager::entityCount() const
{
    return EntityManagerSingleton::instance().entityCount();
}

int EntityManager::getEntityCount(const QString &entityType)
{
    return EntityManagerSingleton::instance().entityCount(entityType);
}

Scene *EntityManager::parentScene() const
{
    return m_parentScene;
}

void EntityManager::setParentScene(Scene *parentScene)
{
    if (m_parentScene == parentScene)
        return;

    m_parentScene = parentScene;
    emit parentSceneChanged();
}

void EntityManager::componentComplete()
{
    QQuickItem::componentComplete();
    m_parentScene = qobject_cast<Scene *>(parentItem());
}
