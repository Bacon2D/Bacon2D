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

#include "tiledobjectgroup.h"
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
#include "entityfactory.h"

#include <QDebug>
#include <QVariant>
#include <QQmlProperty>

/*!
  \qmltype TiledObjectGroup
  \inqmlmodule Bacon2D
  \inherits Item
  \brief TiledObjectGroup encapsulates one or more TMX objects on a TMX map.

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
   retrieved from the \l TiledObjectGroup to position, rotate etc. your created entities.

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
                    objectGroups: [
                        TiledObjectGroup {
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

   You can set the \l fixtures for a \l TiledObjectGroup as shown below.

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
                objects: TiledObjectGroup {

                    fixtures: Box {
                        // Set fixtures of the TMX object here
                        ...
                    }
                }
            }
        ]
    }
   \endqml

    The \l TiledObjectGroup class also handles \e collisions. A \e collision is a TMX
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
    through the collisions of a \l TiledObjectGroup. Once a TMX object is positioned on a
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
                objects: TiledObjectGroup {}
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

TiledEntityComponent::TiledEntityComponent(QQmlComponent *component,
                                           const TMXMapObject &object,
                                           TiledObjectGroup *objectGroup)
    : m_component(component)
    , m_mapObject(object)
    , m_objectGroup(objectGroup)
{
}

QObject *TiledEntityComponent::beginCreate(QQmlContext *publicContext)
{
    return m_component->beginCreate(publicContext);
}

void TiledEntityComponent::completeCreate()
{
    m_component->completeCreate();
}

QQmlComponent *TiledEntityComponent::component() const
{
    return m_component;
}

TMXMapObject TiledEntityComponent::mapObject() const
{
    return m_mapObject;
}

TiledObjectGroup *TiledEntityComponent::objectGroup()
{
    return m_objectGroup;
}

TiledObjectGroupAttached::TiledObjectGroupAttached(QObject *parent)
    : QObject(parent)
    , m_instance(nullptr)
{
    if (parent) {
        Entity *entity = qobject_cast<Entity *>(parent);
        if (entity)
            m_instance = qobject_cast<TiledObjectGroup *>(entity->parent());
        else
            qWarning() << "TiledObjectGroup: Component must inherit from Entity.";
    }
}

TiledObjectGroup *TiledObjectGroupAttached::instance() const
{
    return m_instance;
}

void TiledObjectGroupAttached::setInstance(TiledObjectGroup *instance)
{
    if (m_instance == instance)
        return;

    m_instance = instance;
    emit instanceChanged();
}

TiledObjectGroup::TiledObjectGroup(QQuickItem *parent)
    : QObject(parent)
    , m_objectGroup(nullptr)
    , m_entityComponent(nullptr)
    , m_active(true)
    , m_autoMapProperties(false)
    , m_ignoreFixtures(false)
    , m_count(0)
{
}

/*!
  \qmlproperty string TiledObjectGroup::name
  \brief This property holds the name of the TMX object in the TMX map.

   If multiple TMX objects have the same name, you can access them by using the
   \l first(), \l next(), \l last(), \l previous(), and \l seek().
*/
QString TiledObjectGroup::name() const
{
    return m_name;
}

void TiledObjectGroup::setName(const QString &name)
{
    if(m_name == name)
        return;

    m_name = name;
    emit nameChanged();
}

/*!
  \qmlproperty string TiledObjectGroup::type
  \brief This property holds the type of the TMX object defined in the TMX map.

   If multiple TMX objects have the same name, you can access them by using the
   \l first(), \l next(), \l last(), \l previous(), and \l seek().
*/
QString TiledObjectGroup::type() const
{
    return m_type;
}

void TiledObjectGroup::setType(const QString &type)
{
    if(m_type == type)
        return;

    m_type = type;
    emit typeChanged();
}

QQmlComponent *TiledObjectGroup::entity() const
{
    return m_entityComponent;
}

void TiledObjectGroup::setEntity(QQmlComponent *entity)
{
    if (m_entityComponent == entity)
        return;
    if (!m_entities.isEmpty())
        deinitialize();

    m_entityComponent = entity;
    emit entityChanged();
}

bool TiledObjectGroup::isActive() const
{
    return m_active;
}

void TiledObjectGroup::setActive(bool active)
{
    if (m_active == active)
        return;

    if (active)
        initialize();
    else
        deinitialize();

    m_active = active;
    emit activeChanged();
}

bool TiledObjectGroup::autoMapProperties() const
{
    return m_autoMapProperties;
}

void TiledObjectGroup::setAutoMapProperties(bool enabled)
{
    if (m_autoMapProperties == enabled)
        return;

    m_autoMapProperties = enabled;
    emit autoMapPropertiesChanged();
}

bool TiledObjectGroup::ignoreFixtures() const
{
    return m_ignoreFixtures;
}

void TiledObjectGroup::setIgnoreFixtures(bool enabled)
{
    if (m_ignoreFixtures == enabled)
        return;

    m_ignoreFixtures = enabled;
    emit ignoreFixturesChanged();
}

int TiledObjectGroup::count() const
{
    return m_count;
}

void TiledObjectGroup::setCount(int count)
{
    if (m_count == count)
        return;

    m_count = count;
    emit countChanged();
}

/*!
  \qmlmethod string TiledObjectGroup::getProperty(string entityId, string name, variant defaultValue)
  \brief This method returns the value of the custom property called \e name for this TMX object.
  If the value is not provided, the \e defaultValue is used instead.

  \warning If this method fails to find the custom property, it attempts to
   associate the property with the closest existing QQuickItem property. This is true for
   the properties \e x, \e y, \e width, \e height, \e rotation, \e visible and \e id.
   For example, if an object is 50 pixels wide, getProperty("width") would return
   50 pixels even if no custom property was set for \e width.
*/
QVariant TiledObjectGroup::getProperty(const QString &entityId, const QString &property, const QVariant &defaultValue) const
{
    Entity *entity = m_entities.value(entityId);
    if (!entity)
        return defaultValue;

    const QVariantMap &properties = entity->property("__TiledObjectGroup__properties").toMap();

    if(!properties.contains(property) && property.toLower() == "x")
        return entity->property("__TiledObjectGroup__x");
    else if(!properties.contains(property) && property.toLower() == "y")
        return entity->property("__TiledObjectGroup__y");
    else if(!properties.contains(property) && property.toLower() == "width")
        return entity->property("__TiledObjectGroup__width");
    else if(!properties.contains(property) && property.toLower() == "height")
        return entity->property("__TiledObjectGroup__height");
    else if(!properties.contains(property) && property.toLower() == "rotation")
        return entity->property("__TiledObjectGroup__rotation");
    else if(!properties.contains(property) && property.toLower() == "visible")
        return entity->property("__TiledObjectGroup__visible");
    else if(!properties.contains(property) && property.toLower() == "id")
        return entity->property("__TiledObjectGroup__id");

    return properties.value(property, defaultValue);
}

Entity *TiledObjectGroup::getEntity(const QString &entityId) const
{
    if (entityId.isNull() && !m_entities.isEmpty())
        return m_entities.values().first();

    return m_entities.value(entityId);
}

QVariantList TiledObjectGroup::createdEntities() const
{
    QVariantList entities;
    for (Entity *entity : m_entities.values())
        entities.append(QVariant::fromValue(entity));

    return entities;
}

void TiledObjectGroup::initialize()
{
    if (!m_active)
        return;
    if (!m_entities.isEmpty())
        deinitialize();

    TiledLayer *tiledLayer = qobject_cast<TiledLayer *>(parent());
    if (!tiledLayer || !tiledLayer->layer() || !tiledLayer->layer()->isObjectLayer())
        return;

    m_layerName = tiledLayer->name();

    if (m_objectGroup) {
        m_objectGroup->deleteLater();
        m_objectGroup = nullptr;
    }

    m_objectGroup = new TMXObjectGroup(*tiledLayer->layer(), this);

    for (const TMXMapObject &object : m_objectGroup->objects()) {
        if (object.name() == m_name && object.type() == m_type) {
            if (!static_cast<TiledScene *>(tiledLayer->parent()))
                return;

            createEntity(object);
        }
    }

    setCount(m_objectGroup->objects().count());
}

void TiledObjectGroup::deinitialize()
{
    for (const auto entity : m_entities.values()) {
        if (entity)
            EntityFactory::instance().destroyEntity(entity->entityId());
    }

    setCount(0);
    m_entities.clear();
}

void TiledObjectGroup::createEntity(const TMXMapObject &object)
{
    auto parentScene = findParentScene();
    if (parentScene) {
        if (!m_entityComponent)
            return;

        QScopedPointer<TiledEntityComponent> component(new TiledEntityComponent(m_entityComponent, object, this));
        Entity *entity = EntityFactory::instance().createEntity(QVariant::fromValue(component.data()),
                                                                parentScene,
                                                                qmlEngine(this));
        if (entity) {
            if (m_autoMapProperties)
                attemptAutoMapping(entity, object);

            applyMappings(entity, object);
            applyFixtureProperties(entity, object);

            m_entities.insert(entity->entityId(), entity);
            component->completeCreate();
            connect(entity, &Entity::destroyed, this, [this](QObject *object) {
                emit entityDestroyed(static_cast<Entity *>(object));
            });
            emit entityCreated(entity);
        }
    }
}

void TiledObjectGroup::applyFixtureProperties(Entity *entity, const TMXMapObject &object)
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

TiledScene* TiledObjectGroup::findParentScene() const
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

void TiledObjectGroup::attemptAutoMapping(Entity *entity, const TMXMapObject &object)
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

void TiledObjectGroup::applyMappings(Entity *entity, const TMXMapObject &object)
{
    for (const auto mapping : m_mappings) {
        const QString &property = mapping->mapsTo().isNull() ? mapping->property()
                                                             : mapping->mapsTo();
        const QVariant &value = mapping->defaultValue().isNull() ? propertyFromMapObject(mapping->property(), object)
                                                                 : mapping->defaultValue();

        if (QQmlProperty::read(entity, property).isValid()) {
            if (value.isValid())
                QQmlProperty::write(entity, property, value);
            else
                qWarning() << "TiledPropertyMapping:" << mapping->property() << "invalid" << entity;
        } else {
            qWarning() << "TiledPropertyMapping:" << mapping->property() << "does not exist." << entity;
        }
    }
}

QVariant TiledObjectGroup::propertyFromMapObject(const QString &property, const TMXMapObject &object)
{
    if(!object.properties().contains(property) && property.toLower() == "x")
        return object.x();
    else if(!object.properties().contains(property) && property.toLower() == "y")
        return object.y();
    else if(!object.properties().contains(property) && property.toLower() == "width")
        return object.width();
    else if(!object.properties().contains(property) && property.toLower() == "height")
        return object.height();
    else if(!object.properties().contains(property) && property.toLower() == "rotation")
        return object.rotation();
    else if(!object.properties().contains(property) && property.toLower() == "visible")
        return object.isVisible();
    else if(!object.properties().contains(property) && property.toLower() == "id")
        return object.id();

    return object.properties().value(property);
}

QQmlListProperty<TiledPropertyMapping> TiledObjectGroup::mappings()
{
    return QQmlListProperty<TiledPropertyMapping>(this, nullptr,
                                                  &TiledObjectGroup::append_mapping,
                                                  &TiledObjectGroup::count_mapping,
                                                  &TiledObjectGroup::at_mapping,
                                                  nullptr);
}

void TiledObjectGroup::append_mapping(QQmlListProperty<TiledPropertyMapping> *list, TiledPropertyMapping *mapping)
{
    TiledObjectGroup *object = static_cast<TiledObjectGroup *>(list->object);
    mapping->setParent(object);
    object->m_mappings.append(mapping);
}

int TiledObjectGroup::count_mapping(QQmlListProperty<TiledPropertyMapping> *list)
{
    TiledObjectGroup *object = static_cast<TiledObjectGroup *>(list->object);
    return object->m_mappings.count();
}

TiledPropertyMapping *TiledObjectGroup::at_mapping(QQmlListProperty<TiledPropertyMapping> *list, int index)
{
    TiledObjectGroup *object = static_cast<TiledObjectGroup *>(list->object);
    return object->m_mappings.at(index);
}
