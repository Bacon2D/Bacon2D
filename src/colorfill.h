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

#ifndef _COLORFILL_H_
#define _COLORFILL_H_

#include "fill.h"

#include <QtGui/QColor>

class ColorFill : public Fill
{
    Q_OBJECT

    Q_PROPERTY(QColor brushColor READ brushColor WRITE setBrushColor NOTIFY brushColorChanged)
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor NOTIFY penColorChanged)

public:
    ColorFill(Fill *parent = 0);

    void initialize();

    QColor brushColor() const;
    void setBrushColor(const QColor &brushColor);

    QColor penColor() const;
    void setPenColor(const QColor &penColor);

signals:
    void brushColorChanged();
    void penColorChanged();

private:
    QColor m_brushColor;
    QColor m_penColor;
};

#endif /* _COLORFILL_H_ */
