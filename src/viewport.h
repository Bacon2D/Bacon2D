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

#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include <QtQuick/QQuickItem>

#include "gameitem.h"

class Viewport : public GameItem
{
    Q_OBJECT

    Q_PROPERTY(float xOffset READ xOffset WRITE setXOffset NOTIFY xOffsetChanged)
    Q_PROPERTY(float yOffset READ yOffset WRITE setYOffset NOTIFY yOffsetChanged)
    Q_PROPERTY(float contentWidth READ contentWidth WRITE setContentWidth NOTIFY contentWidthChanged)
    Q_PROPERTY(float contentHeight READ contentHeight WRITE setContentHeight NOTIFY contentHeightChanged)

public:
    Viewport(GameScene *parent = 0);

    float xOffset();
    void setXOffset(float xOffset);

    float yOffset();
    void setYOffset(float yOffset);

    float contentWidth() const;
    void setContentWidth(const float &contentWidth);

    float contentHeight() const;
    void setContentHeight(const float &contentHeight);

    void updateMaxOffsets();

    void setScene(GameScene *scene);

    Q_INVOKABLE void hScroll(float step);
    Q_INVOKABLE void vScroll(float step);

signals:
    void xOffsetChanged();
    void yOffsetChanged();
    void contentWidthChanged();
    void contentHeightChanged();

private:
    float m_xOffset;
    float m_yOffset;
    float m_contentWidth;
    float m_contentHeight;
    float m_maxXOffset;
    float m_maxYOffset;
    GameScene *m_scene;
};

#endif /* _VIEWPORT_H_ */
