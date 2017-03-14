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

#include "tiledscene.h"
#include <QFile>
#include <QDebug>
#include <QPainter>
#include <QSGSimpleTextureNode>
#include <QQmlEngine>
#include <QQmlContext>

#include "box2dbody.h"
#include "box2dfixture.h"
#include "viewport.h"

#include <libtiled/mapreader.h>

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
TiledScene::TiledScene(Game *parent)
    : Scene(parent)
    , m_map(0)
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
    m_image.fill(Qt::transparent);

    loadLayers();

    emit sourceChanged();
}

bool TiledScene::loadMap(const QString &source)
{
    Tiled::MapReader reader;
    Tiled::Map *tiledMap = 0;

    if (m_map)
        m_map->deleteLater();

    if(!QFile::exists(source))
        qWarning() << source << " does not exist.";

    tiledMap = reader.readMap(source);
    if (!tiledMap) {
        qCritical("Failed to read map: %s", qPrintable(source));
        return false;
    }

    m_map = new TMXMap(tiledMap, this);

    return true;
}

void TiledScene::loadLayers()
{
    // Extract tiles for each layer
    foreach(const TMXLayer &layer, m_map->layers())
    {
        if(layer.isTileLayer())
            loadTileLayer(static_cast<TMXTileLayer>(layer));
        else if(layer.isImageLayer())
            loadImageLayer(static_cast<TMXImageLayer>(layer));
        else if(layer.isObjectLayer()) {
            // This layer would be loaded by the TiledLayer and TiledObject classes.
        }
        else
            qWarning() << "Unknown layer type: " << layer.name();
    }

    QQuickItem::update();
}

void TiledScene::loadTileLayer(const TMXTileLayer &layer)
{
    // A cell represents a tile in the tileset.
    // You must extract the tiles used by the map
    int cellX, cellY;
    cellX = cellY = 0;

    foreach(const TMXCell &cell, layer.cells())
    {
        // Store tiles that are used from the tileset
        if(!cell.isEmpty()) {
            TMXTile tile = cell.tile();
            const QPoint &pos = QPoint(cellX * tile.width(), cellY * tile.height());
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
    const QPoint &pos = layer.position();
    const QSize &size = QSize(image.width(), image.height());

    QPainter painter(&m_image);

    QRect target = QRect(pos.x(), pos.y(), size.width(), size.height());
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

        connect(this, SIGNAL(destroyed()), texture, SLOT(deleteLater()));
    }
    node->setRect(boundingRect());

    return node;
}

void TiledScene::componentComplete()
{
    Scene::componentComplete();
}

/*!
  \qmlproperty list<TiledLayer> TiledScene::layers
  \brief This property holds a list of \l TiledLayer objects.

  \sa TiledLayer
*/

QQmlListProperty<TiledLayer> TiledScene::layers()
{
    return QQmlListProperty<TiledLayer>(this, 0,
                                        &TiledScene::append_layer,
                                        &TiledScene::count_layer,
                                        &TiledScene::at_layer,
                                        0);
}

void TiledScene::append_layer(QQmlListProperty<TiledLayer> *list, TiledLayer *layer)
{
    TiledScene *scene = static_cast<TiledScene *>(list->object);
    layer->setParent(scene);
    layer->setParentItem(scene);
    connect(scene, SIGNAL(sourceChanged()), layer, SLOT(initialize()));
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

