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

#include "box2dcontact.h"

#include "fixture.h"

Box2DContact::Box2DContact(b2Contact *contact, QObject *parent)
    : QObject(parent)
    , m_contact(contact)
{
    b2Fixture *b2FixtureA = contact->GetFixtureA();
    b2Fixture *b2FixtureB = contact->GetFixtureB();

    m_fixtureA = static_cast<Fixture *>(b2FixtureA->GetUserData());
    m_fixtureB = static_cast<Fixture *>(b2FixtureB->GetUserData());
}

void Box2DContact::setEnabled(const bool &enabled)
{
    if (m_contact->IsEnabled() != enabled) {
        m_contact->SetEnabled(enabled);

        emit enabledChanged();
    }
}

bool Box2DContact::enabled() const
{
    return m_contact->IsEnabled();
}

bool Box2DContact::touching() const
{
    return m_contact->IsTouching();
}

Fixture *Box2DContact::fixtureA() const
{
    return m_fixtureA;
}

Fixture *Box2DContact::fixtureB() const
{
    return m_fixtureB;
}

double Box2DContact::maxImpulse() const
{
    return m_maxImpulse;
}

void Box2DContact::setImpulse(const b2ContactImpulse* impulse)
{
    m_impulse = impulse;

    if (!m_contact)
        return;

    int count = m_contact->GetManifold()->pointCount;
    float32 max = 0.0f;
    for (int i = 0; i < count; ++i)
        max = b2Max(max, m_impulse->normalImpulses[i]);
    m_maxImpulse = max;
}

double Box2DContact::restitution() const
{
    if (!m_contact)
        return 0.0;
    return m_contact->GetRestitution();
}

void Box2DContact::setRestitution(const double &restitution)
{
    if (!m_contact)
        return;

    double value = Box2DContact::restitution();
    if (restitution == value)
        return;

    m_contact->SetRestitution(restitution);
    emit restitutionChanged();
}

double Box2DContact::friction() const
{
    if (!m_contact)
        return 0.0;
    return m_contact->GetFriction();
}

void Box2DContact::setFriction(const double &friction)
{
    if (!m_contact)
        return;

    double value = Box2DContact::friction();
    if (friction == value)
        return;

    m_contact->SetFriction(friction);

    emit frictionChanged();
}

void Box2DContact::resetRestitution()
{
    if (!m_contact)
        return;

    m_contact->ResetRestitution();
    emit restitutionChanged();
}

void Box2DContact::resetFriction()
{
    if (!m_contact)
        return;

    m_contact->ResetFriction();
    emit frictionChanged();
}
