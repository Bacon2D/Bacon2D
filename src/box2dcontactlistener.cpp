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


#include "scene.h"
#include "box2dcontact.h"
#include "box2dcontactlistener.h"

ContactListener::ContactListener(Scene *scene)
    : m_scene(scene)
{
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
    b2Fixture *b2FixtureA = contact->GetFixtureA();
    b2Fixture *b2FixtureB = contact->GetFixtureB();

    Fixture *fixtureA = static_cast<Fixture *>(b2FixtureA->GetUserData());
    Fixture *fixtureB = static_cast<Fixture *>(b2FixtureB->GetUserData());

    int count = contact->GetManifold()->pointCount;
    float32 maxImpulse = 0.0f;
    for (int i = 0; i < count; ++i)
        maxImpulse = b2Max(maxImpulse, impulse->normalImpulses[i]);

    m_scene->onPostSolve(fixtureA, fixtureB, maxImpulse);
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold *oldManifold)
{
    Q_UNUSED(oldManifold);

    b2Fixture *b2FixtureA = contact->GetFixtureA();
    b2Fixture *b2FixtureB = contact->GetFixtureB();

    Fixture *fixtureA = static_cast<Fixture *>(b2FixtureA->GetUserData());
    Fixture *fixtureB = static_cast<Fixture *>(b2FixtureB->GetUserData());
    Box2DContact *contactObject = new Box2DContact(contact);

    m_scene->onPreSolve(fixtureA, fixtureB, contactObject);
}

void ContactListener::BeginContact(b2Contact *contact)
{
    b2Fixture *b2FixtureA = contact->GetFixtureA();
    b2Fixture *b2FixtureB = contact->GetFixtureB();

    Fixture *fixtureA = static_cast<Fixture *>(b2FixtureA->GetUserData());
    Fixture *fixtureB = static_cast<Fixture *>(b2FixtureB->GetUserData());
    Box2DContact *contactObject = new Box2DContact(contact);

    m_scene->onBeginContact(fixtureA, fixtureB, contactObject);
}

void ContactListener::EndContact(b2Contact *contact)
{
    b2Fixture *b2FixtureA = contact->GetFixtureA();
    b2Fixture *b2FixtureB = contact->GetFixtureB();

    Fixture *fixtureA = static_cast<Fixture *>(b2FixtureA->GetUserData());
    Fixture *fixtureB = static_cast<Fixture *>(b2FixtureB->GetUserData());
    Box2DContact *contactObject = new Box2DContact(contact);

    m_scene->onEndContact(fixtureA, fixtureB, contactObject);
}
