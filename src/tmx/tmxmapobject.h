#ifndef TMXMAPOBJECT_H
#define TMXMAPOBJECT_H

#include "tmxobject.h"
#include "tmxcell.h"

#include <libtiled/mapobject.h>
#include <QVariant>

class TMXMapObject : public TMXObject
{
    Q_OBJECT

public:
    enum Shape {
        Rectangle,
        Polygon,
        Polyline,
        Ellipse
    };

    explicit TMXMapObject(Tiled::MapObject *mapObject, QObject *parent = 0)
        : TMXObject(mapObject, parent), m_mapObject(mapObject) {}

    TMXMapObject& operator=(const TMXMapObject &other)
    {
        setTiledMapObject(other.tiledMapObject());
        return *this;
    }

    Tiled::MapObject *tiledMapObject() const { return m_mapObject; }
    void setTiledMapObject(Tiled::MapObject *mapObject) { m_mapObject = mapObject; }

    const QString &name() const { return m_mapObject->name(); }
    void setName(const QString &name) { m_mapObject->setName(name); }

    const QString &type() const { return m_mapObject->type(); }
    void setType(const QString &type) { m_mapObject->setType(type); }

    const QPointF &position() const { return m_mapObject->position(); }
    void setPosition(const QPointF &pos) { m_mapObject->setPosition(pos); }

    qreal x() const { return m_mapObject->x(); }
    void setX(qreal x) { m_mapObject->setX(x); }

    qreal y() const { return m_mapObject->y(); }
    void setY(qreal y) { m_mapObject->setY(y); }

    qreal width() const { return m_mapObject->width(); }
    void setWidth(qreal width) { m_mapObject->setWidth(width); }

    qreal height() const { return m_mapObject->height(); }
    void setHeight(qreal height) { m_mapObject->setHeight(height); }

    qreal rotation() const { return m_mapObject->rotation(); }
    void setRotation(qreal rotation) { m_mapObject->setRotation(rotation); }

    Shape shape() const { return static_cast<Shape>(m_mapObject->shape()); }
    void setShape(Shape shape) { m_mapObject->setShape(static_cast<Tiled::MapObject::Shape>(shape)); }

    bool isVisible() const { return m_mapObject->isVisible(); }
    void setVisible(bool visible) { m_mapObject->setVisible(visible); }

    const QPolygonF &polygon() const { return m_mapObject->polygon(); }
    void setPolygon(const QPolygonF &polygon) { m_mapObject->setPolygon(polygon); }

    QVariantList polygonAsList() const
    {
        QVariantList allVertices;
        foreach(const QPointF &point, m_mapObject->polygon())
            allVertices.append(QVariant(point));

        return allVertices;
    }

    int id() const { return m_mapObject->id(); }

    TMXCell cell() const { return TMXCell(m_mapObject->cell()); }
private:
    Tiled::MapObject *m_mapObject;
};

#endif // TMXMAPOBJECT_H
