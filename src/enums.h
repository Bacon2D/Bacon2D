/**
 * Copyright (C) 2014 Bacon2D Project
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
 * @author Ken VanDine <ken@vandine.org>
 */

#ifndef _ENUMS_H_
#define _ENUMS_H_

#include <QObject>

class Bacon2D : public QObject
{
    Q_OBJECT

    Q_ENUMS (
        State
    )

public:
    Bacon2D(QObject *parent = 0);

    enum State {
        Active = 0,
        Inactive = 1,
        Running = 2,
        Paused = 3,
        Suspended = 4
    };
};

#endif /* _ENUMS_H_ */
