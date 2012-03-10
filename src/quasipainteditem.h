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

#ifndef _QUASIPAINTEDITEM_H_
#define _QUASIPAINTEDITEM_H_

#include <QtCore/qglobal.h>

#if QT_VERSION >= 0x050000
#include <QtQuick/QQuickPaintedItem>
#else
#include <QtDeclarative/QDeclarativeItem>
#endif

#include "quasideclarativeitem.h"

class QuasiPaintedItem
#if QT_VERSION >= 0x050000
    : public QQuickPaintedItem
#else
    : public QDeclarativeItem
#endif
{
public:
    QuasiPaintedItem(QuasiDeclarativeItem *parent = 0)
#if QT_VERSION >= 0x050000
        : QQuickPaintedItem(parent) {}
#else
        : QDeclarativeItem(parent)
    {
        setFlag(ItemHasNoContents, false);
    }
#endif

#if QT_VERSION >= 0x050000
    virtual void paint(QPainter *painter) { Q_UNUSED(painter); };
#else
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0)
    {
        Q_UNUSED(painter);
        Q_UNUSED(option);
        Q_UNUSED(widget);
    };
#endif

    virtual ~QuasiPaintedItem() {}
};

#endif /* _QUASIPAINTEDITEM_H_ */
