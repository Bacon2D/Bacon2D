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

#ifndef _ANIMATEDLAYER_H_
#define _ANIMATEDLAYER_H_

#include <QtGui/QPixmap>
#include <QtGui/QPainter>

#include "layer.h"

class AnimatedLayer : public Layer
{
    Q_OBJECT

    Q_PROPERTY(qreal horizontalStep READ horizontalStep WRITE setHorizontalStep NOTIFY horizontalStepChanged)

public:
    AnimatedLayer(Layer *parent = 0);
    ~AnimatedLayer();

    qreal horizontalStep() const { return m_horizontalStep; };
    void setHorizontalStep(const qreal &step);

    void paint(QPainter *painter);

signals:
    void horizontalStepChanged();

private:
    void updateHorizontalStep();

    qreal m_horizontalStep;
    qreal m_currentHorizontalStep;
};

#endif /* _ANIMATEDLAYER_H_ */
