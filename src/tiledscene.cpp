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

#include "tiledscene.h"
#include "box2dbody.h"
#include "box2dfixture.h"
#include "viewport.h"
#include "tmxmap.h"
#include "tiledlayer.h"
#include <libtiled/mapreader.h>

#include <QFile>
#include <QDebug>
#include <QPainter>
#include <QSGSimpleTextureNode>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickWindow>

/*!
  \qmltype TiledScene
  \inqmlmodule Bacon2D
  \inherits Scene
  \brief TiledScene is a \l Scene that supports reading and loading of TMX files.

  TMX (Tile Map XML) files describe a tile based map. A common use for this class is to load
  levels that were developed with a map editor. For more information on TMX files, please
  visit \l {http://doc.mapeditor.org/reference/tmx-map-format/} {this website}.

  The source of the TMX file is specified as a URL using the \l source property.

  Image layers, tile layers and object layers that were created on the map in the TMX file
  would be loaded onto the scene after the \l source property is set. Default fixtures
  are set on all TMX objects on the map.

  \warning Only the orthogonal map orientation is currently supported.

  The following example shows the simplest usage of the TiledScene type.
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
        }
    }
   \endqml

  If for some reason you need to access the tile layers of the map (for example, to access
  custom properties set on a tile layer), you can use the \l layers property, which takes a list
  of \l TiledLayer objects.

  The example below displays the width of a layer called "Player" to the console.

  \qml
    TiledScene {
        id: scene
        width: 640
        height: 480
        physics: true
        source: "levels/level_1.tmx"
        layers: [
            TiledLayer {
                id: playerLayer
                name: "Player"
            }
        ]

        Component.onCompleted: {
            // Display width of player layer to console
            console.log(playerLayer.getProperty("width")) // ...or playerLayer.width
        }
    }
   \endqml

   \sa TiledLayer TiledObject
*/

// TiledScene
TiledScene::TiledScene(QQuickItem *parent)
    : Scene(parent)
    , m_map(nullptr)
    , m_backgroundItem(nullptr)
    , m_useMapBackgroundColor(false)
{
    setFlag(QQuickItem::ItemHasContents, true);
}

/*!
  \qmlproperty url TiledScene::source
  \brief This property holds the source of the TMX file.
*/

QUrl TiledScene::source() const
{
    return m_source;
}


void TiledScene::setSource(const QUrl &source)
{
    if (m_source == source)
        return;

    m_source = source;

    QString sourceAsString;
    if (m_source.url().startsWith("qrc:/"))
        sourceAsString = m_source.url().replace(QString("qrc:/"), QString(":/"));
    else
        sourceAsString = m_source.toLocalFile();

    if (!loadMap(sourceAsString))
        return;

    setImplicitWidth(m_map->width() * m_map->tileWidth());
    setImplicitHeight(m_map->height() * m_map->tileHeight());

    m_image = QPixmap(m_map->tileWidth() * m_map->width(), m_map->tileHeight() * m_map->height());
    m_image.fill(m_useMapBackgroundColor ? m_map->backgroundColor() : Qt::transparent);

    loadLayers();
    emit sourceChanged();
}

/*!
 * \qmlproperty Item TiledScene::backgroundItem
 * \brief This property allows you to override the TMX image layer set in the TMX file. Note that the
 * background set takes the dimensions of the scene automatically.
 * \return
 */
QQuickItem *TiledScene::backgroundItem() const
{
    return m_backgroundItem;
}

void TiledScene::setBackgroundItem(QQuickItem *backgroundItem)
{
    if (m_backgroundItem == backgroundItem)
        return;

    m_backgroundItem = backgroundItem;
    emit backgroundItemChanged();
}

/*!
 * \qmlproperty bool TiledScene::useMapBackgroundColor
 * \brief This property determines whether the map background color is used as the background color
 * of this scene.
 *
 * The default value is false.
 * \return
 */
bool TiledScene::useMapBackgroundColor() const
{
    return m_useMapBackgroundColor;
}

void TiledScene::setUseMapBackgroundColor(bool useMapBackgroundColor)
{
    if (m_useMapBackgroundColor == useMapBackgroundColor)
        return;

    m_useMapBackgroundColor = useMapBackgroundColor;
    emit useMapBackgroundColorChanged();
}

QColor TiledScene::color() const
{
    return m_color;
}

void TiledScene::setColor(const QColor &color)
{
    if (m_color == color)
        return;

    m_color = color;
    emit colorChanged();
}

bool TiledScene::loadMap(const QString &source)
{
    Tiled::MapReader reader;
    Tiled::Map *tiledMap = nullptr;

    if (m_map) {
        m_map->deleteLater();
        m_map = nullptr;
    }

    if(!QFile::exists(source))
        qWarning() << "TiledScene:" << source << " does not exist.";

    tiledMap = reader.readMap(source);
    if (!tiledMap) {
        qCritical("Failed to read map: %s", qPrintable(source));
        return false;
    }

    m_map = new TMXMap(tiledMap, this);

    return true;
}

void TiledScene::loadBackground()
{
    if (m_backgroundItem == nullptr)
        return;

    m_backgroundItem->setParentItem(this);
    m_backgroundItem->setWidth(implicitWidth());
    m_backgroundItem->setHeight(implicitHeight());
    m_backgroundItem->setZ(-1);
}

void TiledScene::loadLayers()
{
    for (const TMXLayer &layer : m_map->layers()) {
        if(layer.isTileLayer())
            loadTileLayer(static_cast<TMXTileLayer>(layer));
        else if(layer.isImageLayer() && !m_backgroundItem)
            loadImageLayer(static_cast<TMXImageLayer>(layer));
        else if (!layer.isObjectLayer() && m_backgroundItem == nullptr)
            qWarning() << "Unknown layer type: " << layer.name();
    }

    for (auto layer : m_layers)
        layer->initialize();
}

void TiledScene::loadTileLayer(const TMXTileLayer &layer)
{
    // A cell represents a tile in the tileset.
    // You must extract the tiles used by the map
    int cellX, cellY;
    cellX = cellY = 0;

    for (const TMXCell &cell : layer.cells())
    {
        // Store tiles that are used from the tileset
        if(!cell.isEmpty()) {
            TMXTile tile = cell.tile();
            const QPoint &pos = QPoint(cellX * m_map->tileWidth(), cellY * m_map->tileHeight() - tile.height() + m_map->tileHeight());
            QPainter painter(&m_image);

            QPainter::PixmapFragment fragment;
            fragment.x = pos.x();
            fragment.y = pos.y();
            fragment.sourceLeft = 0;
            fragment.sourceTop = 0;
            fragment.width = tile.width();
            fragment.height = tile.height();
            fragment.scaleX = cell.flippedHorizontally() ? -1 : 1;
            fragment.scaleY = cell.flippedVertically() ? -1 : 1;
            fragment.rotation = 0;
            fragment.opacity = 1;

            if (cell.flippedAntiDiagonally())
                fragment.rotation = 90;

            QTransform transform;
            transform.translate(pos.x() + tile.width() * .5, pos.y() + tile.height() * .5);
            transform.rotate(fragment.rotation);
            transform.scale(fragment.scaleX, fragment.scaleY);

            QRect target = QRect(pos.x(), pos.y(), tile.width(), tile.height());
            QRect source = QRect(tile.image().rect());
            const QPixmap &tileImage = tile.image().transformed(transform);
            painter.drawPixmap(target, tileImage, source);
        }

        cellY++;
        if(((cellY * m_map->tileHeight()) % (m_map->height() * m_map->tileHeight())) == 0) {
            cellY = 0;
            cellX++;
        }
    }
}

void TiledScene::loadImageLayer(const TMXImageLayer &layer)
{
    const QPixmap &image = layer.image();
    const QPoint &pos = layer.offset().toPoint();
    const QSize &size = image.size();

    QPainter painter(&m_image);

    QRect target = QRect(pos, size);
    QRect source = QRect(image.rect());
    painter.drawPixmap(target, image, source);
}

QSGNode *TiledScene::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGSimpleTextureNode *node = static_cast<QSGSimpleTextureNode *>(oldNode);

    if(!node) {
        node = new QSGSimpleTextureNode();
        QSGTexture *texture = window()->createTextureFromImage(m_image.toImage());
        node->setTexture(texture);

        connect(this, &TiledScene::destroyed, texture, &QSGTexture::deleteLater);
    }
    node->setRect(boundingRect());

    return node;
}

void TiledScene::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    Scene::geometryChanged(newGeometry, oldGeometry);
    if (newGeometry.isEmpty() || !isComponentComplete() || (newGeometry == oldGeometry))
        return;

    loadBackground();
}

/*!
  \qmlproperty list<TiledLayer> TiledScene::layers
  \brief This property holds a list of \l TiledLayer objects.

  \sa TiledLayer
*/

QQmlListProperty<TiledLayer> TiledScene::layers()
{
    return QQmlListProperty<TiledLayer>(this, nullptr,
                                        &TiledScene::append_layer,
                                        &TiledScene::count_layer,
                                        &TiledScene::at_layer,
                                        nullptr);
}

QVariant TiledScene::getMapProperty(const QString &name, const QVariant &defaultValue) const
{
    if (m_map)
        return m_map->properties().value(name, defaultValue);

    return defaultValue;
}

void TiledScene::append_layer(QQmlListProperty<TiledLayer> *list, TiledLayer *layer)
{
    TiledScene *scene = static_cast<TiledScene *>(list->object);
    layer->setParent(scene);
    scene->m_layers.append(layer);
}

int TiledScene::count_layer(QQmlListProperty<TiledLayer> *list)
{
    TiledScene *scene = static_cast<TiledScene *>(list->object);
    return scene->m_layers.length();
}

TiledLayer *TiledScene::at_layer(QQmlListProperty<TiledLayer> *list, int index)
{
    TiledScene *scene = static_cast<TiledScene *>(list->object);
    return scene->m_layers.at(index);
}

