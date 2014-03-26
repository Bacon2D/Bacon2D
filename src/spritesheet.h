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

#ifndef _SPRITESHEET_H_
#define _SPRITESHEET_H_

#include "quasipainteditem.h"

#include <QtCore/QtGlobal>

class QPixmap;

class SpriteSheet : public QuasiPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(int frame READ frame WRITE setFrame NOTIFY frameChanged)

public:
    SpriteSheet(QuasiDeclarativeItem *parent = 0);

    QString source() const;
    void setSource(const QString &source);

    int frames() const;
    void setFrames(const int &frames);

    int frame() const;
    void setFrame(const int &frame);

    int initialFrame() const;
    void setInitialFrame(const int &initialFrame);

    bool verticalMirror() const;
    void setVerticalMirror(const bool &verticalMirror);

    bool horizontalMirror() const;
    void setHorizontalMirror(const bool &horizontalMirror);

    void paint(QPainter *painter);

signals:
    void sourceChanged();
    void framesChanged();
    void frameChanged();
    void initialFrameChanged();

private:
    void updateSizeInfo();

private:
    QPixmap *m_pixMap;
    QString m_source;
    int m_frames;
    int m_frame;
    int m_initialFrame;
    int m_frameWidth;
    int m_vertical;
    int m_horizontal;
    bool m_mirror;
};

#endif /* _SPRITESHEET_H_ */
