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

#include "fixture.h"
#include "material.h"
#include "entity.h"
#include "shape.h"

#include <Box2D/Box2D.h>

Fixture::Fixture(QuasiDeclarativeItem *parent)
    : QuasiDeclarativeItem(parent)
    , m_fixture(0)
    , m_material(0)
    , m_shapeItem(0)
    , m_body(0)
    , m_entity(0)
    , m_sensor(false)
{
    connect(this, SIGNAL(parentChanged(QQuickItem*)),
            this, SLOT(onParentChanged(QQuickItem*)));
}

void Fixture::onParentChanged(QQuickItem*)
{
    if (!m_shapeItem)
        return;

    // NOTE: Probably we need to check if there is a
    // better place to set container Entity to be
    // parent of Shape.
    m_shapeItem->setParent(parentItem());
    m_shapeItem->setParentItem(parentItem());
}

Fixture::~Fixture()
{
    if (!m_world || !m_body || !m_fixture)
        return;

    m_body->DestroyFixture(m_fixture);

    if (!m_shapeItem)
        return;

    m_shapeItem->deleteLater();
}

void Fixture::setMaterial(Material *material)
{
    if (m_material == material)
        return;

    if (m_material)
        m_material->disconnect();

    m_material = material;

    if (m_fixture) {
        m_fixture->SetDensity(m_material->density());
        m_fixture->SetFriction(m_material->friction());
        m_fixture->SetRestitution(m_material->restitution());
    }

    connect(m_material, SIGNAL(densityChanged(const float &)),
            this, SLOT(onDensityChanged(const float &)));

    connect(m_material, SIGNAL(frictionChanged(const float &)),
            this, SLOT(onFrictionChanged(const float &)));

    connect(m_material, SIGNAL(restitutionChanged(const float &)),
            this, SLOT(onRestitutionChanged(const float &)));

    emit materialChanged();
}

#if QT_VERSION >= 0x050000
void Fixture::setShapeItem(QQuickItem *shapeItem)
#else
void Fixture::setShapeItem(QDeclarativeItem *shapeItem)
#endif
{
    if (m_shapeItem == shapeItem)
        return;

    if (m_shapeItem)
        m_shapeItem->disconnect();

    m_shapeItem = shapeItem;

    if (Shape *shape = dynamic_cast<Shape*>(m_shapeItem)) {
        connect(shape, SIGNAL(shapeUpdated()),
                this, SLOT(onShapeUpdated()));
    }

    emit shapeChanged();
}

void Fixture::onDensityChanged(const float &density)
{
    if (!m_fixture)
        return;

    m_fixture->SetDensity(density);

    if (m_body)
        m_body->ResetMassData();
}

void Fixture::onFrictionChanged(const float &friction)
{
    if (!m_fixture)
        return;

    m_fixture->SetFriction(friction);
}

void Fixture::onRestitutionChanged(const float &restitution)
{
    if (!m_fixture)
        return;

    m_fixture->SetRestitution(restitution);
}

void Fixture::setWorld(QSharedPointer<b2World> world)
{
    m_world = world;
}

void Fixture::setEntity(Entity *entity)
{
    m_entity = entity;
    m_body = m_entity->body();
}

void Fixture::initialize()
{
    if (!isComponentComplete())
        return;

    updateFixture();
}

void Fixture::updateFixture()
{
    if (!m_material || !m_shapeItem || !m_body)
        return;

    if (m_fixture) {
        m_body->DestroyFixture(m_fixture);
        m_fixture = 0;
    }

    b2FixtureDef fixtureDef;
    fixtureDef.density = m_material->density();
    fixtureDef.friction = m_material->friction();
    fixtureDef.restitution = m_material->restitution();
    fixtureDef.isSensor = m_sensor;

    // Test if the 'shape' property is a Shape derived class.
    // In that case, get the B2Shape created by it.
    if (Shape *quasiShape = dynamic_cast<Shape *>(m_shapeItem)) {
        b2Shape *shape = quasiShape->box2DShape();
        if (!shape)
            return;

        fixtureDef.shape = shape;
        m_fixture = m_body->CreateFixture(&fixtureDef);
        m_fixture->SetUserData(this);
        return;
    }

    // If 'shape' does not inherit from Shape, set it to be a Box.
    // It should be default if shape is set to be to any other
    // QML Item derived element (e.g. Rectangle, Image, etc).
    b2PolygonShape shape;

    //XXX: get coordinates
    shape.SetAsBox(m_shapeItem->width() / Box2DBase::m_scaleRatio / 2.0,
                   m_shapeItem->height() / Box2DBase::m_scaleRatio / 2.0);
    fixtureDef.shape = &shape;

    m_fixture = m_body->CreateFixture(&fixtureDef);
    m_fixture->SetUserData(this);
}

void Fixture::componentComplete()
{
    QuasiDeclarativeItem::componentComplete();

    if (Shape *shape = qobject_cast<Shape*>(m_shapeItem))
        shape->initialize();

    initialize();
}

void Fixture::onShapeUpdated()
{
    updateShape();
    updateFixture();
}

void Fixture::updateShape() {
    if (!m_shapeItem)
        return;

    if (Shape *shape = dynamic_cast<Shape *>(m_shapeItem)) {
        Fill *fill = shape->fill();
        if (!fill || !fill->initialized())
            return;

        shape->updateShape(fill->pen()->widthF());
    }
}

void Fixture::setSensor(const bool &sensor)
{
    if (m_sensor == sensor)
        return;

    m_sensor = sensor;

    if (m_fixture)
        updateFixture();

    emit sensorChanged();
}
