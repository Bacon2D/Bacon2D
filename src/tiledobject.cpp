/**
 * Copyright (C) 2012 by INdT
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * @author Rodrigo Goncalves de Oliveira <rodrigo.goncalves@openbossa.org>
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

#include "tiledobject.h"
#include "box2dbody.h"
#include "box2dfixture.h"
#include "tmxlayer.h"
#include "tiledlayer.h"
#include "tmxobjectgroup.h"
#include "tiledscene.h"
#include <QDebug>
#include <QVariant>

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

TiledObject::TiledObject(QQuickItem *parent) :
    QQuickItem(parent)
  , m_id(0)
  , m_objectGroup(0)
  , m_body(0)
  , m_collisionIndex(-1)
  , m_componentCompleted(false)
{
}

TiledObject::~TiledObject()
{
    qDeleteAll(m_fixtures);
    qDeleteAll(m_collisionItems);
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

/*!
  \qmlproperty Body TiledObject::body
  \brief This property holds the Box2D body of the TMX object in the TMX map.
*/
Box2DBody *TiledObject::body() const
{
    return m_body;
}

void TiledObject::setBody(Box2DBody *body)
{
    if(m_body == body)
        return;

    m_body = body;
    emit bodyChanged();
}

/*!
  \qmlmethod string TiledObject::getProperty(string name)
  \brief This method returns the value of the custom property called \e name for this TMX object.

  \warning This method ignores the custom property set with the names
   \e x, \e y, \e width, \e height, \e rotation, \e visible and \e id and returns
   the actual value. For example, if an object is 50 pixels wide, getProperty("width")
   would return 50 pixels even if it has a custom property set for \e width.
*/
QVariant TiledObject::getProperty(const QString &name) const
{
    if(name.toLower() == "x")
        return QVariant::fromValue(x());
    else if(name.toLower() == "y")
        return QVariant::fromValue(y());
    else if(name.toLower() == "width")
        return QVariant::fromValue(width());
    else if(name.toLower() == "height")
        return QVariant::fromValue(height());
    else if(name.toLower() == "rotation")
        return QVariant::fromValue(rotation());
    else if(name.toLower() == "visible")
        return QVariant::fromValue(isVisible());
    else if(name.toLower() == "id")
        return QVariant::fromValue(m_id);

    return m_properties.value(name);
}

void TiledObject::initialize()
{
    if(!m_componentCompleted) {
        m_componentCompleted = true;
        return;
    }

    // Extract properties from layer
    TiledLayer *tiledLayer = qobject_cast<TiledLayer *>(parent());
    if(!tiledLayer && !tiledLayer->layer())
        return;
    if(!tiledLayer->layer()->isObjectLayer())
        return;

    m_layerName = tiledLayer->name();

    if(m_objectGroup)
        m_objectGroup->deleteLater();

    m_objectGroup = new TMXObjectGroup(*tiledLayer->layer(), this);
    if(!m_objectGroup)
        return;

    int collisions = 0;
    m_collisionIndex = -1;
    foreach(const TMXMapObject &object, m_objectGroup->objects())
    {
        if(object.name() == m_name && object.type() == m_type)
        {
            if(!static_cast<TiledScene *>(tiledLayer->parentItem()))
                return;

            //if(!collisions) {
                setProperties(object.properties());

                setX(object.x());
                setY(object.y());
                setWidth(object.width());
                setHeight(object.height());
                setRotation(object.rotation());

                setVisible(object.isVisible());
                setId(object.id());
            //}

            CollisionItem *item = new CollisionItem(tiledLayer->parentItem());
            item->setX(object.x());
            item->setY(object.y());
            item->setWidth(object.width());
            item->setHeight(object.height());
            item->setRotation(object.rotation());
            item->setVisible(object.isVisible());
            item->setId(object.id());
            item->setProperties(object.properties());
            item->setCollisionIndex(collisions);
            m_collisionItems.append(item);

            switch(object.shape())
            {
            case TMXMapObject::Rectangle:
                createRectangularFixture(object, item);
                break;
            case TMXMapObject::Ellipse:
                createEllipseFixture(object, item);
                break;
            case TMXMapObject::Polygon:
                createPolygonFixture(object, item);
                break;
            case TMXMapObject::Polyline:
                createPolylineFixture(object, item);
                break;
            default:
                qWarning() << "Unhandled object group: " << object.name();
                break;
            }

            setBody(item->body());
            collisions++;
        }
    }
}

void TiledObject::createRectangularFixture(const TMXMapObject &object, CollisionItem *item)
{
    if(!item)
        return;
    if(m_fixtures.isEmpty())
        return;

    Box2DBody *body = new Box2DBody(item);
    body->setBodyType(Box2DBody::Static);
    body->setTarget(item);
    body->setActive(true);
    body->setSleepingAllowed(false);

    foreach(Box2DFixture *objectFixture, m_fixtures)
    {
        if(!objectFixture)
            continue;

        // Check to see if the user of the library set the x, y, width and/or height values.
        Box2DBox *box = static_cast<Box2DBox *>(objectFixture);
        if(!box)
            return;

        Box2DBox *fixture = new Box2DBox(item);

        // Add x and y values set by user as offsets
        fixture->setX(box->x());
        fixture->setY(box->y());
        fixture->setWidth(box->width() == 0 ? object.width() : box->width());
        fixture->setHeight(box->height() == 0 ? object.height() : box->height());

        fixture->setDensity(box->density());
        fixture->setFriction(box->friction());
        fixture->setRestitution(box->restitution());
        fixture->setSensor(box->isSensor());
        fixture->setCategories(box->categories());
        fixture->setCollidesWith(box->collidesWith());
        fixture->setGroupIndex(box->groupIndex());

        connect(box, SIGNAL(beginContact(Box2DFixture*)), fixture, SIGNAL(beginContact(Box2DFixture*)));
        connect(box, SIGNAL(endContact(Box2DFixture*)), fixture, SIGNAL(endContact(Box2DFixture*)));

        body->addFixture(fixture);
    }

    body->componentComplete();
    item->setBody(body);
}

void TiledObject::createEllipseFixture(const TMXMapObject &object, CollisionItem *item)
{
    if(!item)
        return;
    if(m_fixtures.isEmpty())
        return;

    Box2DBody *body = new Box2DBody(item);
    body->setBodyType(Box2DBody::Static);
    body->setTarget(item);
    body->setActive(true);
    body->setSleepingAllowed(false);

    foreach(Box2DFixture *objectFixture, m_fixtures)
    {
        if(!objectFixture)
            continue;

        // Check to see if the user of the library set the x, y, width and/or height values.
        Box2DCircle *circle = static_cast<Box2DCircle *>(objectFixture);
        if(!circle)
            return;

        Box2DCircle *fixture = new Box2DCircle(item);

        fixture->setX(circle->x());
        fixture->setY(circle->y());

        if(circle->radius() == 0.0)
            fixture->setRadius(object.width() == 0.0 ? object.height() : object.width());
        else
            fixture->setRadius(circle->radius());

        fixture->setDensity(circle->density());
        fixture->setFriction(circle->friction());
        fixture->setRestitution(circle->restitution());
        fixture->setSensor(circle->isSensor());
        fixture->setCategories(circle->categories());
        fixture->setCollidesWith(circle->collidesWith());
        fixture->setGroupIndex(circle->groupIndex());

        connect(circle, SIGNAL(beginContact(Box2DFixture*)), fixture, SIGNAL(beginContact(Box2DFixture*)));
        connect(circle, SIGNAL(endContact(Box2DFixture*)), fixture, SIGNAL(endContact(Box2DFixture*)));

        body->addFixture(fixture);
    }
    body->componentComplete();
    item->setBody(body);
}

void TiledObject::createPolygonFixture(const TMXMapObject &object, CollisionItem *item)
{
    if(!item)
        return;
    if(m_fixtures.isEmpty())
        return;

    Box2DBody *body = new Box2DBody(item);
    body->setBodyType(Box2DBody::Static);
    body->setTarget(item);
    body->setActive(true);
    body->setSleepingAllowed(false);

    foreach(Box2DFixture *objectFixture, m_fixtures)
    {
        if(!objectFixture)
            continue;

        // Check to see if the user of the library set the x, y, width and/or height values.
        Box2DPolygon *polygon = static_cast<Box2DPolygon *>(objectFixture);
        if(!polygon)
            return;
        Box2DPolygon *fixture = new Box2DPolygon(item);

        QVariantList vertices = polygon->vertices().isEmpty() ? object.polygonAsList()
                                                                : polygon->vertices();
        fixture->setVertices(vertices);

        fixture->setDensity(polygon->density());
        fixture->setFriction(polygon->friction());
        fixture->setRestitution(polygon->restitution());
        fixture->setSensor(polygon->isSensor());
        fixture->setCategories(polygon->categories());
        fixture->setCollidesWith(polygon->collidesWith());
        fixture->setGroupIndex(polygon->groupIndex());

        connect(polygon, SIGNAL(beginContact(Box2DFixture*)), fixture, SIGNAL(beginContact(Box2DFixture*)));
        connect(polygon, SIGNAL(endContact(Box2DFixture*)), fixture, SIGNAL(endContact(Box2DFixture*)));

        body->addFixture(fixture);
    }
    body->componentComplete();
    item->setBody(body);
}

void TiledObject::createPolylineFixture(const TMXMapObject &object, CollisionItem *item)
{
    if(!item)
        return;
    if(m_fixtures.isEmpty())
        return;

    Box2DBody *body = new Box2DBody(item);
    body->setBodyType(Box2DBody::Static);
    body->setTarget(item);
    body->setActive(true);
    body->setSleepingAllowed(false);

    foreach(Box2DFixture *objectFixture, m_fixtures)
    {
        if(!objectFixture)
            continue;

        // Check to see if the user of the library set the x, y, width and/or height values.
        Box2DChain *chain = static_cast<Box2DChain *>(objectFixture);
        if(!chain)
            return;

        Box2DChain *fixture = new Box2DChain(item);

        QVariantList vertices = chain->vertices().isEmpty() ? object.polygonAsList()
                                                                : chain->vertices();
        fixture->setVertices(vertices);

        fixture->setDensity(chain->density());
        fixture->setFriction(chain->friction());
        fixture->setRestitution(chain->restitution());
        fixture->setSensor(chain->isSensor());
        fixture->setCategories(chain->categories());
        fixture->setCollidesWith(chain->collidesWith());
        fixture->setGroupIndex(chain->groupIndex());

        connect(chain, SIGNAL(beginContact(Box2DFixture*)), fixture, SIGNAL(beginContact(Box2DFixture*)));
        connect(chain, SIGNAL(endContact(Box2DFixture*)), fixture, SIGNAL(endContact(Box2DFixture*)));

        body->addFixture(fixture);
    }
    body->componentComplete();
    item->setBody(body);
}

/*!
  \qmlproperty int TiledObject::count
  \brief This property holds the total number of collisions.

   A collision is a TMX object that has exactly the same name and type as another
   object or group of objects on the same TMX layer. The name and type can be
   empty strings.
   \sa index
*/
int TiledObject::count() const
{
    return m_collisionItems.count();
}

/*!
  \qmlmethod void TiledObject::reset()
  \brief This method positions the \l TiledObject before the first collision.

  Returns true if successful, otherwise returns false.
  \sa first() next() last() previous() seek()
*/
void TiledObject::reset()
{
    setCollisionIndex(-1);
}

/*!
  \qmlmethod bool TiledObject::next()
  \brief This method retrieves the next collision in the \l TiledObject, if
    available, and positions the \l TiledObject on the retrieved collision.

   The following rules apply:
   \list
        \li If the \l TiledObject is currently located before the first collision,
         e.g. immediately after a \l TiledObject is created, an attempt is
         made to retrieve the first collision.
        \li If the \l TiledObject is currently located after the last collision,
         there is no change and false is returned.
        \li If the \l TiledObject is located somewhere in the middle, an attempt
         is made to retrieve the next collision.
   \endlist

   If the collision could not be retrieved, the \l TiledObject is positioned after the last
   collision and false is returned. If the collision is successfully retrieved, true is
   returned.

   \sa first() last() previous() reset() seek()
*/
bool TiledObject::next()
{
    return setCollisionIndex(m_collisionIndex + 1);
}

/*!
  \qmlmethod bool TiledObject::previous()
  \brief This method retrieves the previous collision in the \l TiledObject, if
   available, and positions the \l TiledObject on the retrieved collision.

   The following rules apply:
  \list
   \li If the \l TiledObject is currently located before the first collision, there
    is no change and false is returned.
   \li If the \l TiledObject is currently located after the last collision, an
    attempt is made to retrieve the last record.
   \li If the \l TiledObject result is somewhere in the middle, an attempt is
    made to retrieve the previous collision.
  \endlist

  If the collision could not be retrieved, the \l TiledObject is positioned before
  the first collision and false is returned. If the collision is successfully
  retrieved, true is returned.
  \sa first() next() last() reset() seek()
*/
bool TiledObject::previous()
{
    return setCollisionIndex(m_collisionIndex - 1);
}

/*!
  \qmlmethod bool TiledObject::first()
  \brief This method retrieves the first collision in the \l TiledObject, if available, and
   positions the \l TiledObject on the retrieved collision.

   Returns true if successful. If unsuccessful the \l TiledObject position is set to an invalid
   position and false is returned.
  \sa next() last() previous() reset() seek()
*/
bool TiledObject::first()
{
    return setCollisionIndex(0);
}

/*!
  \qmlmethod bool TiledObject::last()
  \brief This method retrieves the last collision in the \l TiledObject, if available,
   and positions the \l TiledObject on the retrieved collision.

   Returns true if successful. If unsuccessful the \l TiledObject position is set to an
   invalid position and false is returned.
   \sa first() next() previous() reset() seek()
*/
bool TiledObject::last()
{
    return setCollisionIndex(m_collisionItems.count() - 1);
}

/*!
  \qmlmethod bool TiledObject::seek(int index)
  \brief This method retrieves the collision at position \e index, if available, and
   positions the \l TiledObject on the retrieved collision. The first collision is at position 0.

   Returns true if successful. If unsuccessful the \l TiledObject position is set to an
   invalid position and false is returned.
  \sa index
*/
bool TiledObject::seek(int index)
{
    return setCollisionIndex(index);
}

/*!
  \qmlproperty int TiledObject::index
  \brief This property holds the current collision index.

  A collision is a TMX object that has the same name and type as
  another TMX object or group of objects.

  You can set the value of the index to any value within the
  range of collisions. This has the same effect as \l seek().
  \sa seek()
*/
int TiledObject::collisionIndex() const
{
    return m_collisionIndex;
}

bool TiledObject::setCollisionIndex(int index)
{
    if(m_collisionIndex == index)
        return false;
    if(index < -1 || index > m_collisionItems.count())
    {
        qWarning() << "TiledObject: Collision index out of range.";
        return false;
    }
    if(index == -1 || index == m_collisionItems.count())
    {
        m_collisionIndex = index;
        emit collisionIndexChanged();
        return false;
    }

    if(index >= 0 && index < m_collisionItems.count())
    {
        CollisionItem *item = m_collisionItems[index];
        if(!item)
            return false;

        setProperties(item->properties());
        setX(item->x());
        setY(item->y());
        setWidth(item->width());
        setHeight(item->height());
        setRotation(item->rotation());

        setVisible(item->isVisible());
        setId(item->id());
        setBody(item->body());
    }

    m_collisionIndex = index;
    emit collisionIndexChanged();

    return true;
}

/*!
  \qmlproperty list<Fixture> TiledObject::fixtures
  \brief This property holds the fixtures of the object.

   \warning The fixtures set must match the shape used in the TMX map e.g. \l Box must be used for
   rectangular shapes. Using any other type would cause undefined behavior.
*/
QQmlListProperty<Box2DFixture> TiledObject::fixtures()
{
    return QQmlListProperty<Box2DFixture>(this, 0,
                                        &TiledObject::append_fixture,
                                        &TiledObject::count_fixture,
                                        &TiledObject::at_fixture,
                                        0);
}

void TiledObject::append_fixture(QQmlListProperty<Box2DFixture> *list, Box2DFixture *fixture)
{
    TiledObject *object = static_cast<TiledObject *>(list->object);
    fixture->setParent(object);
    object->m_fixtures.append(fixture);
}

int TiledObject::count_fixture(QQmlListProperty<Box2DFixture> *list)
{
    TiledObject *object = static_cast<TiledObject *>(list->object);
    return object->m_fixtures.length();
}

Box2DFixture *TiledObject::at_fixture(QQmlListProperty<Box2DFixture> *list, int index)
{
    TiledObject *object = static_cast<TiledObject *>(list->object);
    return object->m_fixtures.at(index);
}

void TiledObject::componentComplete() {
    QQuickItem::componentComplete();

    if(m_componentCompleted)
        initialize();
}

QQmlListProperty<CollisionItem> TiledObject::collisions()
{
    return QQmlListProperty<CollisionItem>(this, 0,
                                        &TiledObject::count_collision,
                                        &TiledObject::at_collision);
}

int TiledObject::count_collision(QQmlListProperty<CollisionItem> *list)
{
    TiledObject *object = static_cast<TiledObject *>(list->object);
    return object->m_collisionItems.length();
}

CollisionItem *TiledObject::at_collision(QQmlListProperty<CollisionItem> *list, int index)
{
    TiledObject *object = static_cast<TiledObject *>(list->object);
    return object->m_collisionItems.at(index);
}
