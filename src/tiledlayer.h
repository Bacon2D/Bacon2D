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
