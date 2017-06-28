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

#ifndef _TILEDLAYER_H_
#define _TILEDLAYER_H_

#include <QQuickItem>
#include "box2dfixture.h"
#include "tiledobject.h"

class TMXLayer;

class TiledLayer : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QQmlListProperty<TiledObject> objects READ objects)
public:
    TiledLayer(QQuickItem *parent = 0);
    ~TiledLayer();

    QString name() const;
    void setName(const QString &name);

    void setProperties(const QMap<QString, QVariant> &properties) { m_properties = properties; }
    Q_INVOKABLE QVariant getProperty(const QString &name) const;

    TMXLayer *layer() const { return m_layer; }
    QList<TiledObject *> tiledObjects() const { return m_objects; }

    QQmlListProperty<TiledObject> objects();

    static void append_object(QQmlListProperty<TiledObject> *list, TiledObject *layer);
    static int count_object(QQmlListProperty<TiledObject> *list);
    static TiledObject *at_object(QQmlListProperty<TiledObject> *list, int index);
signals:
    void nameChanged();
    void layerChanged();
private slots:
    void initialize();
private:
    QString m_name;
    QList<TiledObject *> m_objects;
    QMap<QString, QVariant> m_properties;
    TMXLayer *m_layer;

    void setLayer(TMXLayer *layer);
};

#endif // _TILEDLAYER_H_
