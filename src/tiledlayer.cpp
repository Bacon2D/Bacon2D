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

