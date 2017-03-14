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

#include "tiledlayer.h"
#include "tiledscene.h"
#include "tmxlayer.h"
#include <QVariant>

/*!
  \qmltype TiledLayer
  \inqmlmodule Bacon2D
  \inherits Item
  \brief TiledLayer encapsulates a TMX layer in a TMX map.

  This class exposes all the properties of a TMX layer on a TMX map.

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
                    id: playerLayer
                    name: "Player"
                },

                TiledLayer {
                    id: groundLayer
                    name: "Ground"
                }
            ]

            Component.onCompleted: {
                // Display width of player TMX layer on console
                console.log(playerLayer.getProperty("width"))

                // Display y position of ground TMX layer on console
                console.log(groundLayer.y)
            }
        }
    }
   \endqml

   TMX objects on a TMX object layer can be accessed using the \l TiledObject class.

  \qml
    TiledScene {
        id: scene

        // Initialize TiledScene
        ...

        layers: [
            TiledLayer {
                name: "Player"
                objects: [
                    TiledObject {
                        id: playerObject
                        name: "position"
                    }
                ]
            }
        ]

        Component.onCompleted: {
            // Display the player's x position on console
            console.log(playerObject.x) // or playerObject.getProperty("x")
        }
    }
  \endqml

   \sa TiledScene TiledObject
*/

TiledLayer::TiledLayer(QQuickItem *parent) :
    QQuickItem(parent)
  , m_layer(0)
{
}

TiledLayer::~TiledLayer()
{

}

/*!
  \qmlproperty string TiledLayer::name
  \brief This property holds the name of this TMX layer.
*/
QString TiledLayer::name() const
{
    return m_name;
}

void TiledLayer::setName(const QString &name)
{
    if(m_name == name)
        return;

    m_name = name;
    emit nameChanged();
}

/*!
  \qmlmethod string TiledLayer::getProperty(string name)
  \brief This method returns the value of custom property \e name for this TMX layer.
*/
QVariant TiledLayer::getProperty(const QString &name) const
{
    if(name.toLower() == "opacity")
        return QVariant::fromValue(m_layer->opacity());
    else if(name.toLower() == "visible")
        return QVariant::fromValue(m_layer->isVisible());

    return m_properties.value(name);
}

void TiledLayer::initialize()
{
    // Extract properties from layer
    TiledScene *scene = qobject_cast<TiledScene *>(parent());
    if(!scene || !scene->tiledMap())
        return;

    foreach(const TMXLayer &layer, scene->tiledMap()->layers())
    {
        if(layer.name() == m_name)
        {
            if(layer.isTileLayer())
            {
                TMXTileLayer tileLayer = static_cast<TMXTileLayer>(layer);
                setProperties(tileLayer.properties());

                setX(tileLayer.x());
                setY(tileLayer.y());
                setWidth(tileLayer.width());
                setHeight(tileLayer.height());

                setOpacity(tileLayer.opacity());
                setVisible(tileLayer.isVisible());

                setLayer(new TMXLayer(layer.layer(), this));
            }
            else if(layer.isImageLayer())
            {
                TMXImageLayer imageLayer = static_cast<TMXImageLayer>(layer);
                setProperties(imageLayer.properties());

                setX(imageLayer.x());
                setY(imageLayer.y());
                setWidth(imageLayer.width());
                setHeight(imageLayer.height());

                setOpacity(imageLayer.opacity());
                setVisible(imageLayer.isVisible());

                setLayer(new TMXLayer(layer.layer(), this));
            }
            else if(layer.isObjectLayer())
            {
                TMXObjectGroup objectGroup = static_cast<TMXObjectGroup>(layer);
                setProperties(objectGroup.properties());

                setX(objectGroup.x());
                setY(objectGroup.y());
                setWidth(objectGroup.width());
                setHeight(objectGroup.height());

                setOpacity(objectGroup.opacity());
                setVisible(objectGroup.isVisible());

                setLayer(new TMXLayer(layer.layer(), this));
            }
            else
                qWarning() << "Unknown layer type: " << layer.name();

            break;
        }
    }
}

void TiledLayer::setLayer(TMXLayer *layer)
{
    if(m_layer == layer)
        return;

    m_layer = layer;
    emit layerChanged();
}

/*!
  \qmlproperty list<TiledObject> TiledLayer::objects
  \brief This property holds a list of \l TiledObject objects that exist on
   this TMX layer.
*/
QQmlListProperty<TiledObject> TiledLayer::objects()
{
    return QQmlListProperty<TiledObject>(this, 0,
                                        &TiledLayer::append_object,
                                        &TiledLayer::count_object,
                                        &TiledLayer::at_object,
                                        0);
}

void TiledLayer::append_object(QQmlListProperty<TiledObject> *list, TiledObject *object)
{
    TiledLayer *layer = static_cast<TiledLayer *>(list->object);
    object->setParent(layer);
    object->setParentItem(layer);
    connect(layer, SIGNAL(layerChanged()), object, SLOT(initialize()));
    layer->m_objects.append(object);
}

int TiledLayer::count_object(QQmlListProperty<TiledObject> *list)
{
    TiledLayer *layer = static_cast<TiledLayer *>(list->object);
    return layer->m_objects.length();
}

TiledObject *TiledLayer::at_object(QQmlListProperty<TiledObject> *list, int index)
{
    TiledLayer *layer = static_cast<TiledLayer *>(list->object);
    return layer->m_objects.at(index);
}

