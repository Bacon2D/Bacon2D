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

#include "quasideclarativeitem.h"

#include <QtCore/QtGlobal>
#include <QtCore/QSharedPointer>

class Material;
class Box2DItem;
class b2FixtureDef;
class b2Fixture;
class b2World;
class b2Body;

class Fixture : public QuasiDeclarativeItem
{
    Q_OBJECT

    Q_PROPERTY(Material *material READ material WRITE setMaterial NOTIFY materialChanged)
#if QT_VERSION >= 0x050000
    Q_PROPERTY(QQuickItem *shape READ shapeItem WRITE setShapeItem NOTIFY shapeChanged)
#else
    Q_PROPERTY(QDeclarativeItem *shape READ shapeItem WRITE setShapeItem NOTIFY shapeChanged)
#endif

public:
    Fixture(QuasiDeclarativeItem *parent = 0);
    ~Fixture();

    Material *material() const;
    void setMaterial(Material *material);

#if QT_VERSION >= 0x050000
    QQuickItem *shapeItem() const;
    void setShapeItem(QQuickItem *shapeItem);
#else
    QDeclarativeItem *shapeItem() const;
    void setShapeItem(QDeclarativeItem *shapeItem);
#endif

    void setWorld(QSharedPointer<b2World> world);
    void setBody(b2Body *body);
    void initialize();

signals:
    void materialChanged();
    void shapeChanged();

protected slots:
    void onDensityChanged(const float &density);
    void onFrictionChanged(const float &friction);
    void onRestitutionChanged(const float &restitution);
    void onParentChanged();
    void onBox2DShapeUpdated();

protected:
    void componentComplete();
    void updateFixture();

protected:
    b2Fixture *m_fixture;
    Material *m_material;
#if QT_VERSION >= 0x050000
    QQuickItem *m_shapeItem;
#else
    QDeclarativeItem *m_shapeItem;
#endif
    QWeakPointer<b2World> m_world;
    b2Body *m_body;
};


#endif /* _FIXTURE_H_ */
