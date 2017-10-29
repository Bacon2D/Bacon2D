#include "entitymanager.h"
#include "entity.h"
#include "scene.h"
#include <QMap>
#include <QCoreApplication>
#include <QQmlComponent>
#include <QDebug>
#include <QtQml>
#include <QFileInfo>
#include <QQmlIncubator>

EntityManagerSingleton *EntityManagerSingleton::m_entityManagerSingleton = nullptr;

class EntityIncubator : public QQmlIncubator {
public:
    EntityIncubator(Scene *parentScene, const QVariantMap &properties = QVariantMap())
        : m_parentScene(parentScene)
        , m_properties(properties)
        , QQmlIncubator(IncubationMode::AsynchronousIfNested) { }
protected:
    virtual void setInitialState(QObject *object) {
        if (!object)
            return;

        Entity *entity = qobject_cast<Entity *>(object);
        if (!entity)
            return;

        entity->setParent(m_parentScene);
        entity->setParentItem(m_parentScene);

        if (!m_properties.isEmpty()) {
            QVariantMap::const_iterator iter;
            for (iter = m_properties.constBegin(); iter != m_properties.constEnd(); ++iter) {
                if (entity->property(iter.key().toStdString().c_str()).isValid())
                    entity->setProperty(iter.key().toStdString().c_str(), iter.value());
            }
        }
    }
private:
    Scene *m_parentScene;
    QVariantMap m_properties;
};

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

Entity *EntityManagerSingleton::createEntity(const QVariant &item, Scene *parentScene, QQmlEngine *engine)
{
    if (item.isNull()) {
        qWarning() << Q_FUNC_INFO << ", Item passed in is null.";
        return nullptr;
    }
    if (!parentScene) {
        qWarning() << Q_FUNC_INFO << ", parent Scene is null.";
        return nullptr;
    }

    if (item.type() == QVariant::String && (item.toString().startsWith("file:/") || item.toString().startsWith("http:/") || item.toString().startsWith("https:/")))
    {
        const QUrl source = item.toUrl();

        QQmlComponent component(engine, source);
        EntityIncubator incubator(parentScene);
        component.create(incubator);

        Entity *entity = qobject_cast<Entity *>(incubator.object());
        return addEntity(entity);
    }

    else if (item.type() == QVariant::String)
    {
        const QUrl source = QQmlEngine::contextForObject(parentScene)->resolvedUrl(QUrl(item.toString()));

        QQmlComponent component(engine, source);
        EntityIncubator incubator(parentScene);
        component.create(incubator);

        Entity *entity = qobject_cast<Entity *>(incubator.object());
        return addEntity(entity);
    }

    else {
        QQmlComponent *component = qvariant_cast<QQmlComponent *>(item);
        if (component)
        {
            EntityIncubator incubator(parentScene);
            component->create(incubator);

            Entity *entity = qobject_cast<Entity *>(incubator.object());
            return addEntity(entity);
        }
        else
            qWarning() << Q_FUNC_INFO << ", Item passed (" << item.toString() << ") in is not a component nor a file URL.";
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

Entity *EntityManagerSingleton::findEntity(const QString &entityType, const QString &property, const QVariant &value)
{
    if (entityType.isEmpty() || property.isEmpty() || value.isNull())
        return nullptr;

    const QStringList &entityIds = m_groupMap.value(entityType);
    for (const QString &entityId : entityIds) {
        if (entityId.startsWith(entityType) && m_entityMap.value(entityId) && m_entityMap.value(entityId)->property(property.toStdString().c_str()) == value)
            return m_entityMap.value(entityId);
    }

    return nullptr;
}

Entity *EntityManagerSingleton::getEntity(const QString &entityId)
{
    return m_entityMap.value(entityId);
}

void EntityManagerSingleton::destroyAllEntities(const QString &entityType)
{
    if (entityType.isEmpty()) {
        for (Entity *entity : m_entityMap.values())
            entity->deleteLater();

        m_entityMap.clear();
        m_groupMap.clear();
    }
    else {
        const QStringList &entityIds = m_groupMap.value(entityType);
        for (const QString &entityId : entityIds) {
            if (entityId.startsWith(entityType) && m_entityMap.value(entityId)) {
                Entity *entity = m_entityMap.take(entityId);
                entity->deleteLater();
            }
        }

        m_groupMap.remove(entityType);
    }
}

void EntityManagerSingleton::destroyEntity(const QString &entityId)
{
    Entity *entity = m_entityMap.take(entityId);
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

    m_parentScene = qobject_cast<Scene *>(parentItem());
    if (m_parentScene)
        connect(m_parentScene, &Scene::destroyed, [this]() { destroyAllEntities(); });
}
