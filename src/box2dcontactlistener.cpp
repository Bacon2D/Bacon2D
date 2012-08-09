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
    Box2DContact *box2dContact = new Box2DContact(contact);
    box2dContact->setImpulse(impulse);
    m_scene->onPostSolve(box2dContact);
    delete box2dContact;
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold *oldManifold)
{
    Q_UNUSED(oldManifold);

    Box2DContact *box2dContact = new Box2DContact(contact);
    m_scene->onPreSolve(box2dContact);
    delete box2dContact;
}

void ContactListener::BeginContact(b2Contact *contact)
{
    Box2DContact *box2dContact = new Box2DContact(contact);
    m_scene->onBeginContact(box2dContact);
    delete box2dContact;
}

void ContactListener::EndContact(b2Contact *contact)
{
    Box2DContact *box2dContact = new Box2DContact(contact);
    m_scene->onEndContact(box2dContact);
    delete box2dContact;
}
