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
#include "box2ditem.h"
#include "shape.h"

#include <Box2D/Box2D.h>

Fixture::Fixture(QuasiDeclarativeItem *parent)
    : QuasiDeclarativeItem(parent)
    , m_fixture(0)
    , m_material(0)
    , m_shapeItem(0)
    , m_body(0)
{
}

Fixture::~Fixture()
{
    if (!m_world || !m_body || !m_fixture)
        return;

    m_body->DestroyFixture(m_fixture);
}

Material *Fixture::material() const
{
    return m_material;
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

    connect(m_material,
            SIGNAL(densityChanged(const float &)),
            this,
            SLOT(onDensityChanged(const float &)));

    connect(m_material,
            SIGNAL(frictionChanged(const float &)),
            this,
            SLOT(onFrictionChanged(const float &)));

    connect(m_material,
            SIGNAL(restitutionChanged(const float &)),
            this,
            SLOT(onRestitutionChanged(const float &)));

    emit materialChanged();
}

#if QT_VERSION >= 0x050000
QQuickItem *Fixture::shapeItem() const
#else
QDeclarativeItem *Fixture::shapeItem() const
#endif
{
    return m_shapeItem;
}

#if QT_VERSION >= 0x050000
void Fixture::setShapeItem(QQuickItem *shapeItem)
#else
void Fixture::setShapeItem(QDeclarativeItem *shapeItem)
#endif
{
    if (m_shapeItem == shapeItem)
        return;

    m_shapeItem = shapeItem;

    m_shapeItem->setParent(this);
    m_shapeItem->setParentItem(this);

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

void Fixture::setBody(b2Body *body)
{
    m_body = body;
}

void Fixture::initialize()
{
    if (!m_material || !m_shapeItem || !m_body)
        return;

    b2FixtureDef fixtureDef;
    fixtureDef.density = m_material->density();
    fixtureDef.friction = m_material->friction();
    fixtureDef.restitution = m_material->restitution();

    if (Shape *quasiShape = dynamic_cast<Shape *>(m_shapeItem)) {
        fixtureDef.shape = quasiShape->box2DShape();
        m_fixture = m_body->CreateFixture(&fixtureDef);
    } else {
        b2PolygonShape *shape = new b2PolygonShape;

        //XXX get coordinates
        shape->SetAsBox(m_shapeItem->width() / Box2DBaseItem::m_scaleRatio / 2.0
                        , m_shapeItem->height() / Box2DBaseItem::m_scaleRatio / 2.0);
        fixtureDef.shape = shape;
        m_fixture = m_body->CreateFixture(&fixtureDef);
        delete shape;
    }
}

void Fixture::componentComplete()
{
    if (!m_fixture)
        initialize();
}
