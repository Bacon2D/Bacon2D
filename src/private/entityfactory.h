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

    Entity *createEntity(const QVariant &, Scene *parentScene, QQmlEngine *engine);
    Entity *addEntity(Entity *entity);
    Entity *findEntity(const QString &entityType, const QVariantMap &properties = QVariantMap());
    Entity *getEntity(const QString &entityId);
    QList<Entity *> getEntities(const QString &entityType);
    void destroyEntity(const QString &entityId);
    void destroyAllEntities(const QString &entityType = QString());
    int entityCount(const QString &entityType = QString());
private:
    explicit EntityFactory(QObject *parent = nullptr);
    explicit EntityFactory(const EntityFactory &) = delete;
    EntityFactory& operator=(const EntityFactory &) = delete;

    QString generateId(const QString &entityType) const;
private:
    QHash<QString, Entity *> m_entityMap;
    QHash<QString, QStringList> m_groupMap;
};

#endif // ENTITYFACTORY_H
