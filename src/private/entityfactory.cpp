#include "entityfactory.h"
#include "entity.h"
#include "scene.h"
#include "physicsentity.h"
#include "tiledobjectgroup.h"

#include <QMap>
#include <QCoreApplication>
#include <QQmlComponent>
#include <QDebug>
#include <QtQml>
#include <QFileInfo>
#include <QQmlIncubator>


class EntityIncubator : public QQmlIncubator {
public:
    explicit EntityIncubator(Scene *parentScene,
                             const QVariantMap &properties = QVariantMap())
        : QQmlIncubator(IncubationMode::AsynchronousIfNested)
        , m_parentScene(parentScene)
        , m_properties(properties)
        , m_fixturePolicy(EntityFactory::FixturePolicy::AddFixtures) { }

    ~EntityIncubator() override = default;
protected:
    void setInitialState(QObject *entityObject) override {
        if (m_fixturePolicy == EntityFactory::FixturePolicy::DontAddFixtures) {
            PhysicsEntity *entity = qobject_cast<PhysicsEntity *>(entityObject);
            if (!entity)
                return;

            entity->setParentItem(m_parentScene);
            entity->setFixturePolicy(EntityFactory::FixturePolicy::DontAddFixtures);

            if (!m_properties.isEmpty()) {
                QVariantMap::const_iterator iter;
                for (iter = m_properties.constBegin(); iter != m_properties.constEnd(); ++iter) {
                    if (entity->property(iter.key().toStdString().c_str()).isValid())
                        entity->setProperty(iter.key().toStdString().c_str(), iter.value());
                }
            }
        } else {
            Entity *entity = qobject_cast<Entity *>(entityObject);
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
    EntityFactory::FixturePolicy m_fixturePolicy;
};

EntityFactory::EntityFactory(QObject *parent)
    : QObject(parent)
{

}

EntityFactory &EntityFactory::instance()
{
    static EntityFactory instance;
    return instance;
}

Entity *EntityFactory::createEntity(const QVariant &item, Scene *parentScene, QQmlEngine *engine)
{
    if (item.isNull()) {
        qWarning() << "EntityFactory: Item passed in is null.";
        return nullptr;
    }
    if (!parentScene) {
        qWarning() << "EntityFactory: parent Scene is null.";
        return nullptr;
    }

    if (item.type() == QVariant::String && (item.toString().startsWith("file:/")
                                            || item.toString().startsWith("http:/")
                                            || item.toString().startsWith("https:/"))) {
        const QUrl source = item.toUrl();

        QQmlComponent component(engine, source);
        EntityIncubator incubator(parentScene);
        component.create(incubator);

        if (component.isError()) {
            qWarning() << "EntityFactory:" << component.errorString();
            return nullptr;
        }

        Entity *entity = qobject_cast<Entity *>(incubator.object());
        if (!entity) {
            qWarning() << "EntityFactory: Component must inherit Entity.";
            incubator.object()->deleteLater();
            return nullptr;
        }

        if (m_entityMap.contains(entity->entityId())) {
            qWarning() << "EntityFactory: Entity already exists.";
            entity->deleteLater();
            return nullptr;
        }

        return addEntity(entity);
    } else if (item.type() == QVariant::String) {
        const QUrl source = QQmlEngine::contextForObject(parentScene)->resolvedUrl(QUrl(item.toString()));

        QQmlComponent component(engine, source);
        EntityIncubator incubator(parentScene);
        component.create(incubator);

        if (component.isError()) {
            qWarning() << "EntityFactory:" << component.errorString();
            return nullptr;
        }

        Entity *entity = qobject_cast<Entity *>(incubator.object());
        if (!entity) {
            qWarning() << "EntityFactory: Component must inherit Entity.";
            incubator.object()->deleteLater();
            return nullptr;
        }

        if (m_entityMap.contains(entity->entityId())) {
            qWarning() << "EntityFactory: Entity already exists.";
            entity->deleteLater();
            return nullptr;
        }

        return addEntity(entity);
    } else if (TiledEntityComponent *entityComponent = item.value<TiledEntityComponent *>()) {
        QObject *entityObject = entityComponent->beginCreate(qmlContext(parentScene));
        if (entityComponent->isError()) {
            qWarning() << "EntityFactory:" << entityComponent->errorString();
            return nullptr;
        }

        PhysicsEntity *entity = qobject_cast<PhysicsEntity *>(entityObject);
        if (!entity) {
            qWarning() << "EntityFactory: Component must inherit Entity.";
            entityComponent->completeCreate();
            entityObject->deleteLater();
            return nullptr;
        }

        entity->setParentItem(parentScene);
        entity->setParent(entityComponent->objectGroup());
        entity->setFixturePolicy(EntityFactory::FixturePolicy::DontAddFixtures);
        entity->setProperty("__TiledObjectGroup__x", entityComponent->mapObject().x());
        entity->setProperty("__TiledObjectGroup__y", entityComponent->mapObject().y());
        entity->setProperty("__TiledObjectGroup__width", entityComponent->mapObject().width());
        entity->setProperty("__TiledObjectGroup__height", entityComponent->mapObject().height());
        entity->setProperty("__TiledObjectGroup__rotation", entityComponent->mapObject().rotation());
        entity->setProperty("__TiledObjectGroup__visible", entityComponent->mapObject().isVisible());
        entity->setProperty("__TiledObjectGroup__id", entityComponent->mapObject().id());
        entity->setProperty("__TiledObjectGroup__properties", entityComponent->mapObject().properties());

        if (m_entityMap.contains(entity->entityId())) {
            qWarning() << "EntityFactory: Entity already exists.";
            entity->deleteLater();
            return nullptr;
        }

        return addEntity(entity);
    }

    return nullptr;
}

Entity *EntityFactory::addEntity(Entity *entity)
{
    if (!entity) {
        qWarning() << "EntityFactory: Entity is null.";
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

Entity *EntityFactory::findEntity(const QString &entityType, const QVariantMap &properties)
{
    if (entityType.isEmpty())
        return nullptr;

    const QStringList &entityIds = m_groupMap.value(entityType);
    int matchedPropertyCount = 0;
    for (const QString &entityId : entityIds) {
        matchedPropertyCount = 0;

        Entity *entity = m_entityMap.value(entityId);
        if (properties.isEmpty()) {
            return entity;
        } else {
            for (const QString &property : properties.keys()) {
                if (QQmlProperty::read(entity, property) == properties.value(property))
                    matchedPropertyCount++;
                if (matchedPropertyCount == properties.count())
                    return entity;
            }
        }
    }

    return nullptr;
}

Entity *EntityFactory::getEntity(const QString &entityId)
{
    return m_entityMap.value(entityId);
}

QList<Entity *> EntityFactory::getEntities(const QString &entityType)
{
    if (entityType.isEmpty())
        return m_entityMap.values();

    QList<Entity *> entities;
    const QStringList &entityIds = m_groupMap.value(entityType);
    for (const QString &entityId : entityIds)
        entities.append(m_entityMap.value(entityId));

    return entities;
}

void EntityFactory::destroyAllEntities(const QString &entityType)
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

void EntityFactory::destroyEntity(const QString &entityId)
{
    Entity *entity = m_entityMap.take(entityId);
    entity->deleteLater();
}

int EntityFactory::entityCount(const QString &entityType)
{
    if (entityType.isEmpty())
        return m_entityMap.count();

    return m_groupMap.value(entityType).count();
}

QString EntityFactory::generateId(const QString &entityType) const
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
