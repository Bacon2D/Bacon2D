/**
 * The MIT License (MIT)
 *
 * Copyright (C) 2017 Bacon2D Project
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef TILEDOBJECT_H
#define TILEDOBJECT_H

#include <QQuickItem>
#include "tmxmapobject.h"

class TMXObjectGroup;
class Entity;
class TiledScene;
class TiledObject;
class QQmlComponent;
class TiledPropertyMapping;

class TiledObjectAttached : public QObject {
    Q_OBJECT
    Q_PROPERTY(TiledObject *instance READ instance NOTIFY instanceChanged)
public:
    explicit TiledObjectAttached(QObject *parent = nullptr);
    TiledObject *instance() const;
    void setInstance(TiledObject *instance);
signals:
    void instanceChanged();
private:
    TiledObject *m_instance;
};

class TiledObject : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QQmlComponent *entity READ entity WRITE setEntity NOTIFY entityChanged)
    Q_PROPERTY(bool active READ isActive WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(bool autoMapProperties READ autoMapProperties WRITE setAutoMapProperties NOTIFY autoMapPropertiesChanged)
    Q_PROPERTY(bool ignoreFixtures READ ignoreFixtures WRITE setIgnoreFixtures NOTIFY ignoreFixturesChanged)
    Q_PROPERTY(QQmlListProperty<TiledPropertyMapping> mappings READ mappings)
    Q_CLASSINFO("DefaultProperty", "mappings")
public:
    explicit TiledObject(QQuickItem *parent = nullptr);
    ~TiledObject() override;

    Q_INVOKABLE QVariant getProperty(const QString &entityId, const QString &property) const;
    Q_INVOKABLE QVariant getProperty(const QString &property) const;
    Q_INVOKABLE Entity *getEntity(const QString &entityId = QString()) const;

    void initialize();

    QString name() const;
    void setName(const QString &name);

    QString type() const;
    void setType(const QString &type);

    QQmlComponent *entity() const;
    void setEntity(QQmlComponent *entity);

    bool isActive() const;
    void setActive(bool active);

    bool autoMapProperties() const;
    void setAutoMapProperties(bool enabled);

    bool ignoreFixtures() const;
    void setIgnoreFixtures(bool enabled);

    QQmlListProperty<TiledPropertyMapping> mappings();

    void classBegin() override;
    void componentComplete() override;

    static TiledObjectAttached *qmlAttachedProperties(QObject *entity)
    {
        return new TiledObjectAttached(entity);
    }
signals:
    void nameChanged();
    void typeChanged();
    void entityChanged();
    void activeChanged();
    void autoMapPropertiesChanged();
    void ignoreFixturesChanged();

    void entityCreated(Entity *entity);
    void entityDestroyed(Entity *entity);
private:
    void createEntity(const TMXMapObject &object);
    TiledScene *findParentScene() const;
    void attemptAutoMapping(Entity *entity, const TMXMapObject &object);
    void applyMappings(Entity *entity, const TMXMapObject &object);
    void applyFixtureProperties(Entity *entity, const TMXMapObject &object);
    static QVariant propertyFromMapObject(const QString &property, const TMXMapObject &object);
    void deinitialize();

    static void append_mapping(QQmlListProperty<TiledPropertyMapping> *list, TiledPropertyMapping *mapping);
    static int count_mapping(QQmlListProperty<TiledPropertyMapping> *list);
    static TiledPropertyMapping *at_mapping(QQmlListProperty<TiledPropertyMapping> *list, int index);
private:
    int m_id;
    QString m_name;
    QString m_type;
    QString m_layerName;
    QMap<QString, QVariant> m_properties;
    TMXObjectGroup *m_objectGroup;
    bool m_componentComplete;
    QQmlComponent *m_entityComponent;
    TiledScene *m_parentScene;
    bool m_active;
    bool m_autoMapProperties;
    bool m_ignoreFixtures;
    QHash<QString, Entity *> m_entities;
    QList<TiledPropertyMapping *> m_mappings;
}; QML_DECLARE_TYPEINFO(TiledObject, QML_HAS_ATTACHED_PROPERTIES)

#endif // TILEDOBJECT_H

