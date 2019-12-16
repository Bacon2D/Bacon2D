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

#ifndef TILEDSCENE_H
#define TILEDSCENE_H

#include "scene.h"
#include <QColor>
#include <QPixmap>

class QSGNode;
class TMXMap;
class UpdatePaintNodeData;
class QRectF;
class TiledLayer;
class TMXTileLayer;
class TMXImageLayer;

class TiledScene : public Scene
{
    Q_OBJECT
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QQuickItem *backgroundItem READ backgroundItem WRITE setBackgroundItem NOTIFY backgroundItemChanged)
    Q_PROPERTY(bool useMapBackgroundColor READ useMapBackgroundColor WRITE setUseMapBackgroundColor NOTIFY useMapBackgroundColorChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QQmlListProperty<TiledLayer> layers READ layers)
public:
    explicit TiledScene(QQuickItem *parent = nullptr);
    ~TiledScene() override = default;

    QUrl source() const;
    void setSource(const QUrl &source);

    QQuickItem *backgroundItem() const;
    void setBackgroundItem(QQuickItem *);

    bool useMapBackgroundColor() const;
    void setUseMapBackgroundColor(bool);

    QColor color() const;
    void setColor(const QColor &color);

    QQmlListProperty<TiledLayer> layers();

    Q_INVOKABLE QVariant getMapProperty(const QString &name, const QVariant &defaultValue = QVariant()) const;

    TMXMap *tiledMap() const { return m_map; }
signals:
    void sourceChanged();
    void backgroundItemChanged();
    void useMapBackgroundColorChanged();
    void colorChanged();
protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;
private:
    bool loadMap(const QString &source);
    void loadBackground();
    void loadLayers();
    void loadTileLayer(const TMXTileLayer &layer);
    void loadImageLayer(const TMXImageLayer &layer);
    // NOTE: Object layers are loaded by the TiledLayer and TiledObject classes.

    static void append_layer(QQmlListProperty<TiledLayer> *list, TiledLayer *layer);
    static int count_layer(QQmlListProperty<TiledLayer> *list);
    static TiledLayer *at_layer(QQmlListProperty<TiledLayer> *list, int index);
private:
    TMXMap *m_map;
    QUrl m_source;
    QQuickItem *m_backgroundItem;
    bool m_useMapBackgroundColor;
    QPixmap m_image;
    QList<TiledLayer *> m_layers;
    QColor m_color;
};


#endif // TILEDSCENE_H

