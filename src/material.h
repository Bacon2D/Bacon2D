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

#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <QtCore/QObject>

class Material : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal density READ density WRITE setDensity NOTIFY densityChanged)
    Q_PROPERTY(qreal friction READ friction WRITE setFriction NOTIFY frictionChanged)
    Q_PROPERTY(qreal restitution READ restitution WRITE setRestitution NOTIFY restitutionChanged)

public:
    Material(QObject *parent = 0);

    float density() const;
    void setDensity(const float &density);

    float friction() const;
    void setFriction(const float &friction);

    float restitution() const;
    void setRestitution(const float &restitution);

signals:
    void densityChanged(const float &density);
    void frictionChanged(const float &friction);
    void restitutionChanged(const float &restitution);

private:
    float m_density;
    float m_friction;
    float m_restitution;
};

#endif /* _MATERIAL_H_ */
