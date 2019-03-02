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
#include "tmxmap.h"
#include "box2dfixture.h"
#include "tiledobjectgroup.h"

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

TiledLayer::TiledLayer(QObject *parent)
    : QObject(parent)
    , m_x(0.0)
    , m_y(0.0)
    , m_width(0.0)
    , m_height(0.0)
    , m_opacity(0.0)
    , m_visible(false)
    , m_layer(nullptr)
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
QVariant TiledLayer::getProperty(const QString &name, const QVariant &defaultValue) const
{
    if(!m_properties.contains(name) && name.toLower() == "opacity")
        return QVariant::fromValue(m_layer->opacity());
    else if(!m_properties.contains(name) && name.toLower() == "visible")
        return QVariant::fromValue(m_layer->isVisible());

    return m_properties.value(name, defaultValue);
}

void TiledLayer::initialize()
{
    // Extract properties from layer
    TiledScene *scene = qobject_cast<TiledScene *>(parent());
    if (!scene || !scene->tiledMap())
        return;

    for (const TMXLayer &layer : scene->tiledMap()->layers()) {
        if (layer.name() == m_name) {
            if (layer.isTileLayer() && layer.isVisible()) {
                TMXTileLayer tileLayer = static_cast<TMXTileLayer>(layer);
                setProperties(tileLayer.properties());

                setX(tileLayer.x());
                setY(tileLayer.y());
                setWidth(tileLayer.width());
                setHeight(tileLayer.height());

                setOpacity(static_cast<qreal>(tileLayer.opacity()));
                setVisible(tileLayer.isVisible());

                setLayer(new TMXLayer(layer.layer(), this));
            }
            else if (layer.isImageLayer() && layer.isVisible()) {
                TMXImageLayer imageLayer = static_cast<TMXImageLayer>(layer);
                setProperties(imageLayer.properties());

                setX(imageLayer.x());
                setY(imageLayer.y());
                setWidth(imageLayer.width());
                setHeight(imageLayer.height());

                setOpacity(static_cast<qreal>(imageLayer.opacity()));
                setVisible(imageLayer.isVisible());

                setLayer(new TMXLayer(layer.layer(), this));
            }
            else if (layer.isObjectLayer() && layer.isVisible()) {
                TMXObjectGroup objectGroup = static_cast<TMXObjectGroup>(layer);
                setProperties(objectGroup.properties());

                setX(objectGroup.x());
                setY(objectGroup.y());
                setWidth(objectGroup.width());
                setHeight(objectGroup.height());

                setOpacity(static_cast<qreal>(objectGroup.opacity()));
                setVisible(objectGroup.isVisible());

                setLayer(new TMXLayer(layer.layer(), this));
            }
            else if (!layer.isVisible()) {
                qWarning() << "TiledLayer:" << layer.name() << "is hidden.";
            } else {
                qWarning() << "TiledLayer: Unknown layer type: " << layer.name();
            }
            break;
        }
    }

    for (auto objectGroup : m_objectGroups)
        objectGroup->initialize();
}

qreal TiledLayer::x() const
{
    return m_x;
}

void TiledLayer::setX(qreal x)
{
    if (m_x == x)
        return;

    m_x = x;
    emit xChanged();
}

qreal TiledLayer::y() const
{
    return m_y;
}

void TiledLayer::setY(qreal y)
{
    if (m_y == y)
        return;

    m_y = y;
    emit yChanged();
}

qreal TiledLayer::width() const
{
    return m_width;
}

void TiledLayer::setWidth(qreal width)
{
    if (m_width == width)
        return;

    m_width = width;
    emit widthChanged();
}

qreal TiledLayer::height() const
{
    return m_height;
}

void TiledLayer::setHeight(qreal height)
{
    if (m_height == height)
        return;

    m_height = height;
    emit heightChanged();
}

qreal TiledLayer::opacity() const
{
    return m_opacity;
}

void TiledLayer::setOpacity(qreal opacity)
{
    if (m_opacity == opacity)
        return;

    m_opacity = opacity;
    emit opacityChanged();
}

bool TiledLayer::isVisible() const
{
    return m_visible;
}

void TiledLayer::setVisible(bool visible)
{
    if (m_visible == visible)
        return;

    m_visible = visible;
    emit visibleChanged();
}

void TiledLayer::setLayer(TMXLayer *layer)
{
    m_layer = layer;
}

/*!
  \qmlproperty list<TiledObject> TiledLayer::objects
  \brief This property holds a list of \l TiledObject objects that exist on
   this TMX layer.
*/
QQmlListProperty<TiledObjectGroup> TiledLayer::objectGroups()
{
    return QQmlListProperty<TiledObjectGroup>(this, nullptr,
                                         &TiledLayer::append_object_group,
                                         &TiledLayer::count_object_group,
                                         &TiledLayer::at_object_group,
                                              nullptr);
}

void TiledLayer::setProperties(const QVariantMap &properties)
{
    m_properties = properties;
}

void TiledLayer::append_object_group(QQmlListProperty<TiledObjectGroup> *list, TiledObjectGroup *object)
{
    TiledLayer *layer = static_cast<TiledLayer *>(list->object);
    object->setParent(layer);
    layer->m_objectGroups.append(object);
}

int TiledLayer::count_object_group(QQmlListProperty<TiledObjectGroup> *list)
{
    TiledLayer *layer = static_cast<TiledLayer *>(list->object);
    return layer->m_objectGroups.length();
}

TiledObjectGroup *TiledLayer::at_object_group(QQmlListProperty<TiledObjectGroup> *list, int index)
{
    TiledLayer *layer = static_cast<TiledLayer *>(list->object);
    return layer->m_objectGroups.at(index);
}
