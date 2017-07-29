#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <QObject>
#include <QMap>
#include <QQuickItem>

class QQmlComponent;
class Entity;
class Scene;

class EntityManagerSingleton : public QObject
{
    Q_OBJECT
public:
    static EntityManagerSingleton &instance();

    Entity *createEntity(const QVariant &, Scene *parentScene, QQmlEngine *engine);
    Entity *addEntity(Entity *entity);
    Entity *getEntity(const QString &entityId);
    void removeEntity(const QString &entityId);
    int entityCount(const QString &entityType = QString());

    QString generateId(const QString &entityType) const;
private:
    explicit EntityManagerSingleton(QObject *parent = nullptr);
    static EntityManagerSingleton *m_entityManagerSingleton;
    QMap<QString, Entity *> m_entityMap;
    QMap<QString, QStringList> m_groupMap;
};

class EntityManager : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(Scene* parentScene READ parentScene WRITE setParentScene NOTIFY parentSceneChanged)
    Q_PROPERTY(int entityCount READ entityCount NOTIFY entityCountChanged)
public:
    EntityManager(QQuickItem *parent = nullptr);

    Q_INVOKABLE Entity *createEntity(const QVariant &);
    Q_INVOKABLE Entity *getEntity(const QString &entityId);
    Q_INVOKABLE void removeEntity(const QString &entityId);
    Q_INVOKABLE int getEntityCount(const QString &entityType = QString());

    int entityCount() const;

    Scene *parentScene() const;
    void setParentScene(Scene *);
protected:
    void componentComplete();
signals:
    void parentSceneChanged();
    void entityCountChanged();
private:
    Scene *m_parentScene;
};

#endif // ENTITYMANAGER_H
