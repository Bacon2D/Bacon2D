#include "entitymanagersingleton.h"
#include "entity.h"
#include "scene.h"
#include "physicsentity.h"

#include <QMap>
#include <QCoreApplication>
#include <QQmlComponent>
#include <QDebug>
#include <QtQml>
#include <QFileInfo>
#include <QQmlIncubator>


class EntityIncubator : public QQmlIncubator {
public:
    explicit EntityIncubator(Scene *parentScene, const QVariantMap &properties = QVariantMap())
        : QQmlIncubator(IncubationMode::AsynchronousIfNested)
        , m_parentScene(parentScene)
        , m_properties(properties)
        , m_fixturePolicy(EntityManagerSingleton::FixturePolicy::AddFixtures) { }

    explicit EntityIncubator(Scene *parentScene, const EntityManagerSingleton::FixturePolicy fixturePolicy)
        : QQmlIncubator(IncubationMode::AsynchronousIfNested)
        , m_parentScene(parentScene)
        , m_fixturePolicy(fixturePolicy) { }

    ~EntityIncubator() override = default;
protected:
    void setInitialState(QObject *object) override {
        if (m_fixturePolicy == EntityManagerSingleton::FixturePolicy::DontAddFixtures) {
            PhysicsEntity *entity = qobject_cast<PhysicsEntity *>(object);
            if (!entity)
                return;

            entity->setParentItem(m_parentScene);
            entity->setFixturePolicy(EntityManagerSingleton::FixturePolicy::DontAddFixtures);

            if (!m_properties.isEmpty()) {
                QVariantMap::const_iterator iter;
                for (iter = m_properties.constBegin(); iter != m_properties.constEnd(); ++iter) {
                    if (entity->property(iter.key().toStdString().c_str()).isValid())
                        entity->setProperty(iter.key().toStdString().c_str(), iter.value());
                }
            }
        } else {
            Entity *entity = qobject_cast<Entity *>(object);
            if (!entity)
                return;

            entity->setParentItem(m_parentScene);

            if (!m_properties.isEmpty()) {
                QVariantMap::const_iterator iter;
                for (iter = m_properties.constBegin(); iter != m_properties.constEnd(); ++iter) {
                    if (entity->property(iter.key().toStdString().c_str()).isValid())
                        entity->setProperty(iter.key().toStdString().c_str(), iter.value());
                }
            }
        }
    }
private:
    Scene *m_parentScene;
    QVariantMap m_properties;
    EntityManagerSingleton::FixturePolicy m_fixturePolicy;
};

EntityManagerSingleton::EntityManagerSingleton(QObject *parent)
    : QObject(parent)
{

}

EntityManagerSingleton &EntityManagerSingleton::instance()
{
    static EntityManagerSingleton instance;
    return instance;
}

Entity *EntityManagerSingleton::createEntity(const QVariant &item, Scene *parentScene, QQmlEngine *engine, FixturePolicy policy)
{
    if (item.isNull()) {
        qWarning() << Q_FUNC_INFO << ", Item passed in is null.";
        return nullptr;
    }
    if (!parentScene) {
        qWarning() << Q_FUNC_INFO << ", parent Scene is null.";
        return nullptr;
    }

    if (item.type() == QVariant::String && (item.toString().startsWith("file:/")
                                            || item.toString().startsWith("http:/")
                                            || item.toString().startsWith("https:/")))
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
            EntityIncubator incubator(parentScene, policy);
            component->create(incubator);

            if (component->status() == QQmlComponent::Error)
                qDebug() << "EntityManager:" << component->errorString();

            Entity *entity = qobject_cast<Entity *>(incubator.object());
            return addEntity(entity);
        }
        else {
            qWarning() << "EntityManager: Item passed (" << item.toString() << ") in is not a component nor a file URL.";
        }
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

    const QString &entityId = generateId(entity->entityType());
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
        if (entityId.startsWith(entityType)
                && m_entityMap.value(entityId)
                && m_entityMap.value(entityId)->property(property.toStdString().c_str()) == value)
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
