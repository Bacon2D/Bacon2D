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

#ifndef TILEDLAYER_H
#define TILEDLAYER_H

#include <QObject>
#include <QQmlListProperty>

class TMXLayer;
class TiledObjectGroup;

class TiledLayer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QQmlListProperty<TiledObjectGroup> objectGroups READ objectGroups)
    Q_CLASSINFO("DefaultProperty", "objectGroups")
public:
    explicit TiledLayer(QObject *parent = nullptr);
    ~TiledLayer() override = default;

    void initialize();

    qreal x() const;
    void setX(qreal x);

    qreal y() const;
    void setY(qreal y);

    qreal width() const;
    void setWidth(qreal width);

    qreal height() const;
    void setHeight(qreal height);

    qreal opacity() const;
    void setOpacity(qreal opacity);

    bool isVisible() const;
    void setVisible(bool visible);

    QString name() const;
    void setName(const QString &name);

    QQmlListProperty<TiledObjectGroup> objectGroups();

    void setProperties(const QVariantMap &properties);
    Q_INVOKABLE QVariant getProperty(const QString &name, const QVariant &defaultValue = QVariant()) const;

    TMXLayer *layer() const { return m_layer; }
signals:
    void xChanged();
    void yChanged();
    void widthChanged();
    void heightChanged();
    void opacityChanged();
    void visibleChanged();
    void nameChanged();
private:
    static void append_object_group(QQmlListProperty<TiledObjectGroup> *list, TiledObjectGroup *layer);
    static int count_object_group(QQmlListProperty<TiledObjectGroup> *list);
    static TiledObjectGroup *at_object_group(QQmlListProperty<TiledObjectGroup> *list, int index);

    void setLayer(TMXLayer *layer);
private:
    qreal m_x;
    qreal m_y;
    qreal m_width;
    qreal m_height;
    qreal m_opacity;
    qreal m_visible;
    QString m_name;
    TMXLayer *m_layer;
    QList<TiledObjectGroup *> m_objectGroups;
    QMap<QString, QVariant> m_properties;
};

#endif // TILEDLAYER_H
