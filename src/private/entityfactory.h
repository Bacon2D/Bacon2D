#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <QQmlComponent>

class Entity;
class Scene;

class EntityFactory : public QObject
{
    Q_OBJECT
public:
    enum class FixturePolicy {
        AddFixtures,
        DontAddFixtures
    };
    static EntityFactory &instance();

    Entity *createEntity(const QVariant &, Scene *parentScene, QQmlEngine *engine, FixturePolicy policy = FixturePolicy::AddFixtures);
    Entity *addEntity(Entity *entity);
    Entity *findEntity(const QString &entityType, const QString &property, const QVariant &value);
    Entity *getEntity(const QString &entityId);
    void destroyEntity(const QString &entityId);
    void destroyAllEntities(const QString &entityType = QString());
    int entityCount(const QString &entityType = QString());

    QString generateId(const QString &entityType) const;
private:
    explicit EntityFactory(QObject *parent = nullptr);
    explicit EntityFactory(const EntityFactory &) = delete;
    EntityFactory& operator=(const EntityFactory &) = delete;

    QHash<QString, Entity *> m_entityMap;
    QHash<QString, QStringList> m_groupMap;
};

#endif // ENTITYFACTORY_H
