#ifndef ENTITYMANAGERSINGLETON_H
#define ENTITYMANAGERSINGLETON_H

#include <QQmlComponent>

class Entity;
class Scene;

class EntityManagerSingleton : public QObject
{
    Q_OBJECT
public:
    enum class FixturePolicy {
        AddFixtures,
        DontAddFixtures
    };
    static EntityManagerSingleton &instance();

    Entity *createEntity(const QVariant &, Scene *parentScene, QQmlEngine *engine, FixturePolicy policy = FixturePolicy::AddFixtures);
    Entity *addEntity(Entity *entity);
    Entity *findEntity(const QString &entityType, const QString &property, const QVariant &value);
    Entity *getEntity(const QString &entityId);
    void destroyEntity(const QString &entityId);
    void destroyAllEntities(const QString &entityType = QString());
    int entityCount(const QString &entityType = QString());

    QString generateId(const QString &entityType) const;
private:
    explicit EntityManagerSingleton(QObject *parent = nullptr);
//    EntityManagerSingleton(const EntityManagerSingleton &) = delete;
//    EntityManagerSingleton& operator=(const EntityManagerSingleton &) = delete;

    QHash<QString, Entity *> m_entityMap;
    QHash<QString, QStringList> m_groupMap;
};

#endif // ENTITYMANAGERSINGLETON_H
