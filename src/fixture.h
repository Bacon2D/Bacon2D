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

#ifndef _FIXTURE_H_
#define _FIXTURE_H_

#include <QtQuick/QQuickItem>
#include <QtCore/QtGlobal>
#include <QtCore/QSharedPointer>

class Material;
class Entity;
class b2FixtureDef;
class b2Fixture;
class b2World;
class b2Body;

class Fixture : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(Material *material READ material WRITE setMaterial NOTIFY materialChanged)
    Q_PROPERTY(QQuickItem *shape READ shapeItem WRITE setShapeItem NOTIFY shapeChanged)
    Q_PROPERTY(Entity *entity READ entity)
    Q_PROPERTY(bool sensor READ sensor WRITE setSensor NOTIFY sensorChanged)

public:
    Fixture(QQuickItem *parent = 0);
    ~Fixture();

    Material *material() const { return m_material; }
    void setMaterial(Material *material);

    QQuickItem *shapeItem() const { return m_shapeItem; }
    void setShapeItem(QQuickItem *shapeItem);

    void setWorld(QSharedPointer<b2World> world);

    void setEntity(Entity *entity);
    Entity *entity() const { return m_entity; }

    void initialize();

    bool sensor() const { return m_sensor; }
    void setSensor(const bool &sensor);

    void updateFixture();

signals:
    void materialChanged();
    void shapeChanged();
    void sensorChanged();

protected slots:
    void onDensityChanged(const float &density);
    void onFrictionChanged(const float &friction);
    void onRestitutionChanged(const float &restitution);
    void onParentChanged(QQuickItem*);
    void onShapeUpdated();

protected:
    void componentComplete();
    void updateShape();

protected:
    b2Fixture *m_fixture;
    Material *m_material;
    QQuickItem *m_shapeItem;
    QWeakPointer<b2World> m_world;
    b2Body *m_body;
    Entity *m_entity;
    bool m_sensor;
};

#endif /* _FIXTURE_H_ */
