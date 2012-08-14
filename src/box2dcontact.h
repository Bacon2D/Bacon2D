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

#ifndef _BOX2DCONTACT_H_
#define _BOX2DCONTACT_H_

#include <Box2D/Box2D.h>
#include <QtCore/QObject>

class Fixture;

class Box2DContact : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(bool touching READ touching CONSTANT)
    Q_PROPERTY(Fixture *fixtureA READ fixtureA CONSTANT)
    Q_PROPERTY(Fixture *fixtureB READ fixtureB CONSTANT)
    Q_PROPERTY(double maxImpulse READ maxImpulse CONSTANT)
    Q_PROPERTY(double restitution READ restitution WRITE setRestitution NOTIFY restitutionChanged)
    Q_PROPERTY(double friction READ friction WRITE setFriction NOTIFY frictionChanged)

public:
    Box2DContact(b2Contact *contact, QObject *parent = 0);
    ~Box2DContact() {}

    void setImpulse(const b2ContactImpulse* impulse);

    void setEnabled(const bool &enabled);
    bool enabled() const;

    bool touching() const;

    Fixture *fixtureA() const;
    Fixture *fixtureB() const;

    double maxImpulse() const;

    double restitution() const;
    void setRestitution(const double &restitution);

    double friction() const;
    void setFriction(const double &friction);

    Q_INVOKABLE void resetRestitution();
    Q_INVOKABLE void resetFriction();

signals:
    void enabledChanged();
    void restitutionChanged();
    void frictionChanged();

private:
    b2Contact *m_contact;
    Fixture *m_fixtureA;
    Fixture *m_fixtureB;
    double m_maxImpulse;
    const b2ContactImpulse* m_impulse;
};

#endif /* _BOX2DCONTACT */
