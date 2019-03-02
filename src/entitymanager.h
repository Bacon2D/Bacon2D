#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <QObject>
#include <QHash>
#include <QQuickItem>

class QQmlComponent;
class Entity;
class Scene;

class EntityManager : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(Scene* parentScene READ parentScene WRITE setParentScene NOTIFY parentSceneChanged)
    Q_PROPERTY(int entityCount READ entityCount NOTIFY entityCountChanged)
public:
    EntityManager(QQuickItem *parent = nullptr);

    Q_INVOKABLE Entity *createEntity(const QVariant &);
    Q_INVOKABLE Entity *findEntity(const QString &entityType, const QVariantMap &properties);
    Q_INVOKABLE Entity *getEntity(const QString &entityId);
    Q_INVOKABLE void destroyEntity(const QString &entityId);
    Q_INVOKABLE int getEntityCount(const QString &entityType = QString());
    Q_INVOKABLE void destroyAllEntities(const QString &entityType = QString());

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
