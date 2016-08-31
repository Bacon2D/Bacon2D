#ifndef TILEDOBJECT_H
#define TILEDOBJECT_H

#include <QQuickItem>
#include "tmxmapobject.h"

class Box2DBody;
class Box2DFixture;
class TMXObjectGroup;

class CollisionItem;

class TiledObject : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(Box2DBody *body READ body NOTIFY bodyChanged)
    Q_PROPERTY(QQmlListProperty<Box2DFixture> fixtures READ fixtures)
    Q_PROPERTY(QQmlListProperty<CollisionItem> collisions READ collisions)

    // To handle objects that have the same name
    Q_PROPERTY(int count READ count)
    Q_PROPERTY(int index READ collisionIndex WRITE setCollisionIndex NOTIFY collisionIndexChanged)
public:
    TiledObject(QQuickItem *parent = 0);
    ~TiledObject();

    QString name() const;
    void setName(const QString &name);

    QString type() const;
    void setType(const QString &type);

    Box2DBody *body() const;
    void setBody(Box2DBody *body);

    QList<Box2DFixture *> fixtureList() const { return m_fixtures; }

    void setProperties(const QMap<QString, QVariant> &properties) { m_properties = properties; }
    void setId(int id) { m_id = id; }
    Q_INVOKABLE QVariant getProperty(const QString &name, const QVariant &defaultValue = QVariant()) const;

    QQmlListProperty<Box2DFixture> fixtures();
    static void append_fixture(QQmlListProperty<Box2DFixture> *list, Box2DFixture *fixture);
    static int count_fixture(QQmlListProperty<Box2DFixture> *list);
    static Box2DFixture *at_fixture(QQmlListProperty<Box2DFixture> *list, int index);

    QQmlListProperty<CollisionItem> collisions();
    static int count_collision(QQmlListProperty<CollisionItem> *list);
    static CollisionItem *at_collision(QQmlListProperty<CollisionItem> *list, int index);

    void componentComplete();

    // Handling collision of object names
    Q_INVOKABLE bool next();
    Q_INVOKABLE bool previous();
    Q_INVOKABLE bool first();
    Q_INVOKABLE bool last();
    Q_INVOKABLE bool seek(int index);
    int count() const;
    Q_INVOKABLE void reset();

    int collisionIndex() const;
    bool setCollisionIndex(int index);
signals:
    void nameChanged();
    void typeChanged();
    void bodyChanged();
    void collisionIndexChanged();
private slots:
    void initialize();
private:
    int m_id;
    QString m_name;
    QString m_type;
    QString m_layerName;
    Box2DBody *m_body;
    QList<Box2DFixture *> m_fixtures;
    QMap<QString, QVariant> m_properties;
    TMXObjectGroup *m_objectGroup;
    bool m_componentCompleted;

    // Handling collision of object names
    QList<CollisionItem *> m_collisionItems;
    int m_collisionIndex;

    void createRectangularFixture(const TMXMapObject &object, CollisionItem *item);
    void createEllipseFixture(const TMXMapObject &object, CollisionItem *item);
    void createPolygonFixture(const TMXMapObject &object, CollisionItem *item);
    void createPolylineFixture(const TMXMapObject &object, CollisionItem *item);
};

// An item that represents a single collision object.
// A collision object is an object that has the same name with another object.
// This library has this feature to avoid having to type properties for each object.
class CollisionItem : public QQuickItem
{
    Q_OBJECT
public:
    CollisionItem(QQuickItem *parent = 0) : m_id(0), m_body(0), m_collisionIndex(-1), QQuickItem(parent) {}

    QMap<QString, QVariant> properties() const { return m_properties; }
    void setProperties(const QMap<QString, QVariant> &properties) { m_properties = properties; }

    Box2DBody *body() const { return m_body; }
    void setBody(Box2DBody *body) { m_body = body; }

    int id() const { return m_id; }
    void setId(int id) { m_id = id; }

    int collisionIndex() const { return m_collisionIndex; }
    void setCollisionIndex(int index) { m_collisionIndex = index; }
private:
    int m_id;
    Box2DBody *m_body;
    QMap<QString, QVariant> m_properties;
    int m_collisionIndex;
};

#endif // TILEDOBJECT_H
