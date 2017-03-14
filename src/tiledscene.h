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

#ifndef _TILEDSCENE_H_
#define _TILEDSCENE_H_

#include "game.h"
#include "scene.h"
#include "tmxmap.h"
#include "tmxtileset.h"
#include "tmxtilelayer.h"

#include <QSGTexture>
#include <QQuickWindow>
#include <QSGSimpleMaterialShader>
#include <QSGGeometryNode>
#include "tiledlayer.h"

class TiledScene : public Scene
{
    Q_OBJECT

    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QQmlListProperty<TiledLayer> layers READ layers)
public:
    TiledScene(Game *parent = 0);

    void setSource(const QUrl &source);

    QUrl source() const;

    QQmlListProperty<TiledLayer> layers();

    static void append_layer(QQmlListProperty<TiledLayer> *list, TiledLayer *layer);
    static int count_layer(QQmlListProperty<TiledLayer> *list);
    static TiledLayer *at_layer(QQmlListProperty<TiledLayer> *list, int index);

    TMXMap *tiledMap() const { return m_map; }
    virtual void componentComplete();
signals:
    void sourceChanged();
protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);
private:
    TMXMap *m_map;
    QUrl m_source;
    QPixmap m_image;
    QList<TiledLayer *> m_layers;

    bool loadMap(const QString &source);
    void loadLayers();
    void loadTileLayer(const TMXTileLayer &layer);
    void loadImageLayer(const TMXImageLayer &layer);
    // NOTE: Object layers are loaded by the TiledLayer and TiledObject classes.
};


#endif // _TILEDSCENE_H_

