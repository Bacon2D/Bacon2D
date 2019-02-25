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

#include "tiledobject.h"
#include "box2dbody.h"
#include "box2dfixture.h"
#include "tmxlayer.h"
#include "tiledlayer.h"
#include "tmxobjectgroup.h"
#include "tiledscene.h"
#include "entitymanager.h"
#include "tiledscene.h"
#include "tiledpropertymapping.h"
#include "physicsentity.h"
#include "entitymanagersingleton.h"

#include <QDebug>
#include <QVariant>
#include <QQmlProperty>

/*!
  \qmltype TiledObject
  \inqmlmodule Bacon2D
  \inherits Item
  \brief TiledObject encapsulates one or more TMX objects on a TMX map.

   This class exposes all the properties of a TMX object on a TMX map.
   These properties can be accessed in two ways:
   \list
       \li By using QML properties (for example, the rotation property
        would be accessed through \c Item.rotation). This works for
        \e x, \e y, \e width, \e height, \e rotation, and \e visible
        only.
       \li By using the \l getProperty() method. This works for all properties.
    \endlist

   You can set the properties of \l Entity objects on your scene to the properties
   retrieved from the \l TiledObject to position, rotate etc. your created entities.

  Example usage:
  \qml
    import QtQuick 2.4
    import Bacon2D 1.0

    Game {
        anchors.fill: parent
        currentScene: scene
        width: 640
        height: 480

        TiledScene {
            id: scene
            width: parent.width
            height: parent.height
            physics: true
            source: "levels/level_1.tmx"
            layers: [
                TiledLayer {
                    name: "Player"
                    objects: [
                        TiledObject {
                            id: playerObject
                        }
                    ]
                }
            ]

            Component {
                id: playerComponent

                PhysicsEntity {
                    property bool faceLeft: false
                    // Define your entity's properties here
                    ...
                }
            }

            Component.onCompleted: {
                // Create player object
                var player = playerComponent.createObject(scene);

                // Position player on the x axis
                player.x = playerObject.x;
                // Position player on the y axis
                player.y = playerObject.y;
                // Set player's width
                player.width = playerObject.width;
                // Set player's height
                player.height = playerObject.height;

                // Set custom property "faceLeft"
                // This property must be defined in the TMX map as a custom property of the object
                player.faceLeft = playerObject.getProperty("faceLeft");
            }
        }
    }
   \endqml

   You can set the \l fixtures for a \l TiledObject as shown below.

  \qml
    TiledScene {
        id: scene
        width: 800
        height: 600
        physics: true
        source: "levels/level_1.tmx"
        layers: [
            TiledLayer {
                name: "Ground"
                objects: TiledObject {

                    fixtures: Box {
                        // Set fixtures of the TMX object here
                        ...
                    }
                }
            }
        ]
    }
   \endqml

    The \l TiledObject class also handles \e collisions. A \e collision is a TMX
    object that has exactly the same name and type as another object or group of
    objects on the same TMX layer. This also includes TMX objects that have
    empty strings as names and types.

    Navigating through collisions is performed with the following methods:
    \list
        \li \l next()
        \li \l previous()
        \li \l first()
        \li \l last()
        \li \l seek()
    \endlist
    These methods allow the programmer to move forward, backward or arbitrarily
    through the collisions of a \l TiledObject. Once a TMX object is positioned on a
    valid collision, properties can be retrieved using \l getProperty().

    The following example sets the properties of all collisions on the \e Enemy TMX
    object layer by calling the \l next() method.
   \qml
    TiledScene {
        id: scene
        width: 800
        height: 600
        physics: true
        source: "levels/final_level.tmx"
        layers: [
            TiledLayer {
                id: enemyLayer
                name: "Enemy"

                // Default initialization of object
                objects: TiledObject {}
            }
        ]

        Component {
                id: enemyComponent
            PhysicsEntity {
                // Define other properties here
                ...
            }
        }

        Component.onCompleted: {
            // Loop through every enemy object on the "Enemy" layer on the TMX map.
            for(var i = 0; i < enemyLayer.objects.length; ++i)
            {
                // Store the object as "object"
                var object = enemyLayer.objects[i]

                // Loop as long as there is a collision available
                while(object.next())
                {
                    // Create enemy component
                    var enemy = enemyComponent.createObject(scene)

                    // Set properties
                    enemy.x = object.x
                    enemy.y = object.y
                    enemy.width = object.width
                    enemy.height = object.height

                    // This is a convenient way to give all objects
                    // different object names (if required).
                    enemy.objectName = object.getProperty("id")
                }
            }
        }
    }
   \endqml

   \sa TiledScene TiledLayer
*/

TiledObjectAttached::TiledObjectAttached(QObject *parent)
    : QObject(parent)
    , m_instance(nullptr)
{
    Entity *entity = qobject_cast<Entity *>(parent);
    m_instance = qobject_cast<TiledObject *>(entity->parent());
    //qDebug() << "TiledObjectAttached? " << entity->entityId() << entity->objectName() << qobject_cast<TiledObject *>(entity->parent());
}

TiledObject *TiledObjectAttached::instance() const
{
    return m_instance;
}

void TiledObjectAttached::setInstance(TiledObject *instance)
{
    if (m_instance == instance)
        return;

    m_instance = instance;
    emit instanceChanged();
}

TiledObject::TiledObject(QQuickItem *parent)
    : QObject (parent)
    , m_id(0)
    , m_objectGroup(nullptr)
    , m_componentComplete(false)
    , m_entityComponent(nullptr)
    , m_autoMapProperties(false)
    , m_ignoreFixtures(false)
{
}

/*!
  \qmlproperty string TiledObject::name
  \brief This property holds the name of the TMX object in the TMX map.

   If multiple TMX objects have the same name, you can access them by using the
   \l first(), \l next(), \l last(), \l previous(), and \l seek().
*/
QString TiledObject::name() const
{
    return m_name;
}

void TiledObject::setName(const QString &name)
{
    if(m_name == name)
        return;

    m_name = name;
    emit nameChanged();
}

/*!
  \qmlproperty string TiledObject::type
  \brief This property holds the type of the TMX object defined in the TMX map.

   If multiple TMX objects have the same name, you can access them by using the
   \l first(), \l next(), \l last(), \l previous(), and \l seek().
*/
QString TiledObject::type() const
{
    return m_type;
}

void TiledObject::setType(const QString &type)
{
    if(m_type == type)
        return;

    m_type = type;
    emit typeChanged();
}

QQmlComponent *TiledObject::entity() const
{
    return m_entityComponent;
}

void TiledObject::setEntity(QQmlComponent *entity)
{
    if (m_entityComponent == entity)
        return;
    if (!m_entities.isEmpty()) {
        for (auto entity : m_entities.values())
            EntityManagerSingleton::instance().destroyEntity(entity->entityId());
        m_entities.clear();
    }

    m_entityComponent = entity;
    emit entityChanged();
}

bool TiledObject::autoMapProperties() const
{
    return m_autoMapProperties;
}

void TiledObject::setAutoMapProperties(bool enabled)
{
    if (m_autoMapProperties == enabled)
        return;

    m_autoMapProperties = enabled;
    emit autoMapPropertiesChanged();
}

bool TiledObject::ignoreFixtures() const
{
    return m_ignoreFixtures;
}

void TiledObject::setIgnoreFixtures(bool enabled)
{
    if (m_ignoreFixtures == enabled)
        return;

    m_ignoreFixtures = enabled;
    emit ignoreFixturesChanged();
}

/*!
  \qmlmethod string TiledObject::getProperty(string name, variant defaultValue)
  \brief This method returns the value of the custom property called \e name for this TMX object.
  If the value is not provided, the \e defaultValue is used instead.

  \warning If this method fails to find the custom property, it attempts to
   associate the property with the closest existing QQuickItem property. This is true for
   the properties \e x, \e y, \e width, \e height, \e rotation, \e visible and \e id.
   For example, if an object is 50 pixels wide, getProperty("width") would return
   50 pixels even if no custom property was set for \e width.
*/
QVariant TiledObject::getProperty(const QString &entityId, const QString &property) const
{
    Entity *entity = m_entities.value(entityId);
    const QVariantMap &properties = entity->property("__tiledobject__properties").toMap();

    if(!properties.contains(property) && property.toLower() == "x")
        return QVariant::fromValue(entity->property("__tiledobject__x").toDouble());
    else if(!properties.contains(property) && property.toLower() == "y")
        return QVariant::fromValue(entity->property("__tiledobject__y").toDouble());
    else if(!properties.contains(property) && property.toLower() == "width")
        return QVariant::fromValue(entity->property("__tiledobject__width").toDouble());
    else if(!properties.contains(property) && property.toLower() == "height")
        return QVariant::fromValue(entity->property("__tiledobject__height").toDouble());
    else if(!properties.contains(property) && property.toLower() == "rotation")
        return QVariant::fromValue(entity->property("__tiledobject__rotation").toDouble());
    else if(!properties.contains(property) && property.toLower() == "visible")
        return QVariant::fromValue(entity->property("__tiledobject__visible").toBool());
    else if(!properties.contains(property) && property.toLower() == "id")
        return QVariant::fromValue(entity->property("__tiledobject__id").toInt());

    return properties.value(property);
}

QVariant TiledObject::getProperty(const QString &property) const
{
    if (m_entities.isEmpty())
        return QVariant();
    if (m_entities.count() > 1) {
        qWarning() << "TiledObject: Can't get property: Multiple entities created. Use overload TiledObject::getProperty(string, string).";
        return QVariant();
    }

    return getProperty(m_entities.values().first()->entityId(), property);
}

Entity *TiledObject::getEntity(const QString &entityId) const
{
    if (entityId.isNull() && !m_entities.isEmpty())
        return m_entities.values().first();

    return m_entities.value(entityId);
}

void TiledObject::initialize()
{
    if(!m_componentComplete) {
        m_componentComplete = true;
        return;
    }

    // Extract properties from layer
    TiledLayer *tiledLayer = qobject_cast<TiledLayer *>(parent());
    if((!tiledLayer && !tiledLayer->layer()) || !tiledLayer->layer()->isObjectLayer())
        return;

    m_layerName = tiledLayer->name();

    if(m_objectGroup) {
        m_objectGroup->deleteLater();
        m_objectGroup = nullptr;
    }

    m_objectGroup = new TMXObjectGroup(*tiledLayer->layer(), this);

    for (const TMXMapObject &object : m_objectGroup->objects())
    {
        if(object.name() == m_name && object.type() == m_type)
        {
            if(!static_cast<TiledScene *>(tiledLayer->parentItem()))
                return;

            createEntity(object);
        }
    }
}

void TiledObject::createEntity(const TMXMapObject &object)
{
    auto parentScene = findParentScene();
    if (parentScene) {
        Entity *entity = EntityManagerSingleton::instance().createEntity(QVariant::fromValue(m_entityComponent),
                                                                         parentScene,
                                                                         qmlEngine(this),
                                                                         EntityManagerSingleton::FixturePolicy::DontAddFixtures);
        if (entity) {
            entity->setParent(this);
            entity->setProperty("__tiledobject__x", object.x());
            entity->setProperty("__tiledobject__y", object.y());
            entity->setProperty("__tiledobject__width", object.width());
            entity->setProperty("__tiledobject__height", object.height());
            entity->setProperty("__tiledobject__rotation", object.rotation());
            entity->setProperty("__tiledobject__visible", object.isVisible());
            entity->setProperty("__tiledobject__id", object.id());
            entity->setProperty("__tiledobject__properties", object.properties());

            TiledObjectAttached *attached = qobject_cast<TiledObjectAttached *>(qmlAttachedPropertiesObject<TiledObject>(entity));
            attached->setInstance(this);

            if (m_autoMapProperties)
                attemptAutoMapping(entity, object);

            applyMappings(entity, object);
            applyFixtureProperties(entity, object);
        }

        m_entities.insert(entity->entityId(), entity);
        emit entityCreated(entity);
    } else if (m_componentComplete) {
        qWarning() << "TiledObject: Cannot create entity with null parent scene.";
    }
}

void TiledObject::applyFixtureProperties(Entity *entity, const TMXMapObject &object)
{
    PhysicsEntity *physicsEntity = qobject_cast<PhysicsEntity *>(entity);
    if (!physicsEntity)
        return;

    const QList<Box2DFixture *> &fixtures = physicsEntity->fixtureList();
    if (fixtures.isEmpty())
        return;

    switch (object.shape()) {
    case TMXMapObject::Rectangle:
        for (Box2DFixture *fixture : fixtures)
        {
            Box2DBox *box = static_cast<Box2DBox *>(fixture);
            if(box && !m_ignoreFixtures) {
                box->setWidth(box->width() == 0.0 ? object.width() : box->width());
                box->setHeight(box->height() == 0.0 ? object.height() : box->height());
            }
            physicsEntity->body()->addFixture(box);
        }
        break;
    case TMXMapObject::Ellipse:
        for (Box2DFixture *fixture : fixtures)
        {
            Box2DCircle *circle = static_cast<Box2DCircle *>(fixture);
            if(circle && !m_ignoreFixtures) {
                circle->setRadius(object.width() == 0.0
                                  ? static_cast<float>(object.height())
                                  : static_cast<float>(object.width()));
            }

            physicsEntity->body()->addFixture(circle);
        }
        break;
    case TMXMapObject::Polygon:
        for (Box2DFixture *fixture : fixtures) {
            Box2DPolygon *polygon = static_cast<Box2DPolygon *>(fixture);
            if(polygon && !m_ignoreFixtures) {
                const QVariantList &vertices = polygon->vertices().isEmpty() ? object.polygonAsList()
                                                                             : polygon->vertices();

                polygon->setVertices(vertices);
            }
            physicsEntity->body()->addFixture(polygon);
        }
        break;
    case TMXMapObject::Polyline:
        for (Box2DFixture *fixture : fixtures)
        {
            Box2DChain *chain = static_cast<Box2DChain *>(fixture);
            if(chain && !m_ignoreFixtures) {
                const QVariantList &vertices = chain->vertices().isEmpty() ? object.polygonAsList()
                                                                           : chain->vertices();
                chain->setVertices(vertices);
            }
            physicsEntity->body()->addFixture(chain);
        }
        break;
    }
}

TiledScene* TiledObject::findParentScene() const
{
    QObject *parent = this->parent();
    while (parent) {
        auto tiledScene = qobject_cast<TiledScene *>(parent);
        if (tiledScene)
            return tiledScene;

        parent = parent->parent();
    }

    return nullptr;
}

void TiledObject::attemptAutoMapping(Entity *entity, const TMXMapObject &object)
{
    if (entity == nullptr)
        return;

    const QStringList defaultProperties {
        "x", "y", "width", "height", "rotation", "visible" // id intentionally omitted
    };
    const QVariantMap &properties = object.properties();

    for (const auto &property : defaultProperties) {
        const QVariant &value = propertyFromMapObject(property, object);
        if (entity->property(property.toStdString().c_str()).isValid()) {
            if (value.isValid())
                QQmlProperty::write(entity, property, value);
            else
                qWarning() << "TiledPropertyMapping:" << property << "invalid";
        } else {
            qWarning() << "TiledPropertyMapping:" << property << "does not exist.";
        }
    }

    for (const auto &property : properties.keys()) {
        const QVariant &value = propertyFromMapObject(property, object);
        if (entity->property(property.toStdString().c_str()).isValid()) {
            if (value.isValid())
                QQmlProperty::write(entity, property, value);
            else
                qWarning() << "TiledPropertyMapping:" << property << "invalid";
        } else {
            qWarning() << "TiledPropertyMapping:" << property << "does not exist.";
        }
    }
}

void TiledObject::applyMappings(Entity *entity, const TMXMapObject &object)
{
    for (const auto mapping : m_mappings) {
        const QVariant &value = propertyFromMapObject(mapping->property(), object);
        if (entity->property(mapping->property().toStdString().c_str()).isValid()) {
            if (value.isValid())
                QQmlProperty::write(entity, mapping->property(), value);
            else
                qWarning() << "TiledPropertyMapping:" << mapping->property() << "invalid";
        } else {
            qWarning() << "TiledPropertyMapping:" << mapping->property() << "does not exist.";
        }
    }
}

QVariant TiledObject::propertyFromMapObject(const QString &property, const TMXMapObject &object)
{
    if(!object.properties().contains(property) && property.toLower() == "x")
        return QVariant::fromValue(object.x());
    else if(!object.properties().contains(property) && property.toLower() == "y")
        return QVariant::fromValue(object.y());
    else if(!object.properties().contains(property) && property.toLower() == "width")
        return QVariant::fromValue(object.width());
    else if(!object.properties().contains(property) && property.toLower() == "height")
        return QVariant::fromValue(object.height());
    else if(!object.properties().contains(property) && property.toLower() == "rotation")
        return QVariant::fromValue(object.rotation());
    else if(!object.properties().contains(property) && property.toLower() == "visible")
        return QVariant::fromValue(object.isVisible());
    else if(!object.properties().contains(property) && property.toLower() == "id")
        return QVariant::fromValue(object.id());

    return object.properties().value(property);
}

void TiledObject::classBegin()
{

}

void TiledObject::componentComplete()
{
    if (m_componentComplete)
        initialize();
}

QQmlListProperty<TiledPropertyMapping> TiledObject::mappings()
{
    return QQmlListProperty<TiledPropertyMapping>(this, nullptr,
                                                  &TiledObject::append_mapping,
                                                  &TiledObject::count_mapping,
                                                  &TiledObject::at_mapping,
                                                  nullptr);
}

void TiledObject::append_mapping(QQmlListProperty<TiledPropertyMapping> *list, TiledPropertyMapping *mapping)
{
    TiledObject *object = static_cast<TiledObject *>(list->object);
    mapping->setParent(object);
    object->m_mappings.append(mapping);
}

int TiledObject::count_mapping(QQmlListProperty<TiledPropertyMapping> *list)
{
    TiledObject *object = static_cast<TiledObject *>(list->object);
    return object->m_mappings.count();
}

TiledPropertyMapping *TiledObject::at_mapping(QQmlListProperty<TiledPropertyMapping> *list, int index)
{
    TiledObject *object = static_cast<TiledObject *>(list->object);
    return object->m_mappings.at(index);
}
