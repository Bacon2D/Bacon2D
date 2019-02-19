/**
 * The MIT License (MIT)
 *
 * Copyright (C) 2012 by INdT
 * Copyright (C) 2014 Bacon2D Project
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @author Rodrigo Goncalves de Oliveira <rodrigo.goncalves@openbossa.org>
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

#include "spritesheet.h"

#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtQml/QQmlProperty>

#include "game.h"
#include "scene.h"
#include "sprite.h"
#include "spritesheet.h"
#include "spriteanimation.h"
#include "animationchangeevent.h"
#include "animationtransition.h"
#include "spritesheetgrid.h"

#include <QTime>
#include <QDebug>

/*!
  \qmltype Sprite
  \inqmlmodule Bacon2D
  \inherits Item
  \brief A Sprite, providing state based
   management of multiple SpriteAnimation animations.
 */
Sprite::Sprite(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , m_spriteSheet(nullptr)
    , m_frameX(0.0)
    , m_frameY(0.0)
    , m_frameWidth(0.0)
    , m_frameHeight(0.0)
    , m_vertical(1)
    , m_horizontal(1)
    , m_mirror(false)
    , m_fillMode(Bacon2D::Stretch)
{
    setVisible(true);
    setSmooth(true);
    setFlag(QQuickItem::ItemHasContents);
    QQmlProperty(this, "layer.enabled").write(true);
}

SpriteSheetGrid *Sprite::spriteSheet() const
{
    return m_spriteSheet;
}

void Sprite::setSpriteSheet(SpriteSheetGrid *spriteSheet)
{
    if (m_spriteSheet == spriteSheet)
        return;

    if (m_spriteSheet) {
        update();
    }

    m_spriteSheet = spriteSheet;

    if (m_spriteSheet) {
        m_spriteSheetPixmap = m_spriteSheet->pixmap();

        if (m_frameWidth <= 0.0)
            setFrameWidth(m_spriteSheet->frameWidth());
        if (m_frameHeight <= 0.0)
            setFrameHeight(m_spriteSheet->frameHeight());

        setImplicitWidth(m_spriteSheet->frameWidth());
        setImplicitHeight(m_spriteSheet->frameHeight());

        update();
    }

    emit spriteSheetChanged();
}

/*!
 * \qmlproperty bool Sprite::verticalMirror
 * \brief Shows the Sprite mirrored vertically (upside down)
 */
bool Sprite::verticalMirror() const
{
    return m_vertical == -1;
}

void Sprite::setVerticalMirror(const bool &verticalMirror)
{
    m_vertical = (verticalMirror) ? -1 : 1;

    if (m_vertical == -1 || m_horizontal == -1)
        m_mirror = true;

    update();
}

/*!
 * \qmlproperty bool Sprite::horizontalMirror
 * \brief Shows the Sprite mirrored horizontally
 */
bool Sprite::horizontalMirror() const
{
    return m_horizontal == -1;
}

void Sprite::setHorizontalMirror(const bool &horizontalMirror)
{
    m_horizontal = (horizontalMirror) ? -1 : 1;

    if (m_vertical == -1 || m_horizontal == -1)
        m_mirror = true;

    update();
}

Bacon2D::FillMode Sprite::fillMode() const
{
    return m_fillMode;
}

void Sprite::setFillMode(Bacon2D::FillMode fillMode)
{
    if (m_fillMode == fillMode)
        return;

    m_fillMode = fillMode;
    update();

    emit fillModeChanged();
}

void Sprite::componentComplete()
{
    QQuickPaintedItem::componentComplete();

    if (m_spriteSheet)
        m_spriteSheetPixmap = m_spriteSheet->pixmap();
}

void Sprite::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
}

void Sprite::paint(QPainter *painter)
{
    if (!m_spriteSheetPixmap.isNull()) {
        if (frameWidth() <= 0.0) {
            m_pixmap = m_spriteSheetPixmap.scaled(width(), height(),
                                                  Bacon2D::PreserveAspectFit ? Qt::KeepAspectRatio : (Bacon2D::PreserveAspectCrop ? Qt::KeepAspectRatioByExpanding : Qt::IgnoreAspectRatio),
                                                  smooth() ? Qt::SmoothTransformation : Qt::FastTransformation);
            painter->drawPixmap(0, 0, m_pixmap);
        } else if(m_fillMode == Bacon2D::TileHorizontally) {
            QRectF target = QRectF(boundingRect());
            m_pixmap = m_spriteSheetPixmap.transformed(QTransform().scale(m_horizontal, m_vertical),
                                                       smooth() ? Qt::SmoothTransformation : Qt::FastTransformation);
            QRectF source = QRectF(frameX(),
                                   frameY(),
                                   frameWidth(),
                                   frameHeight());

            for (qreal x = 0.0; x < boundingRect().width(); x += frameWidth()) {
                painter->drawPixmap(target, m_pixmap, source);
                target.setX(x + frameWidth());
            }
        } else if (m_fillMode == Bacon2D::TileVertically) {
            QRectF target = QRectF(boundingRect());
            m_pixmap = m_spriteSheetPixmap.transformed(QTransform().scale(m_horizontal, m_vertical),
                                                       smooth() ? Qt::SmoothTransformation : Qt::FastTransformation);
            QRectF source = QRectF(/*(horizontalMirror() ? ((m_frames - (m_finalFrame + 1) + m_frame - m_initialFrame) * frameWidth())
                                                                              : (m_frame * frameWidth())) + */frameX(),
                                   frameY(),
                                   frameWidth(),
                                   frameHeight());

            for (qreal y = 0.0; y < boundingRect().height(); y += frameHeight()) {
                painter->drawPixmap(target, m_pixmap, source);
                target.setY(y + frameHeight());
            }
        } else if (m_fillMode == Bacon2D::Tile) {
            qWarning() << "Untested implementation for Bacon2D::Tile!";

            QRectF target = QRectF(boundingRect());
            m_pixmap = m_spriteSheetPixmap.transformed(QTransform().scale(m_horizontal, m_vertical),
                                                       smooth() ? Qt::SmoothTransformation : Qt::FastTransformation);
            QRectF source = QRectF(frameX(),
                                   frameY(),
                                   frameWidth(),
                                   frameHeight());

            for (qreal x = 0.0; x < boundingRect().width(); x += frameWidth()) {
                painter->drawPixmap(target, m_pixmap, source);
                target.setX(x + frameWidth());
            }

            for (qreal y = 0.0; y < boundingRect().height(); y += frameHeight()) {
                painter->drawPixmap(target, m_pixmap, source);
                target.setY(y + frameHeight());
            }
        } else {
            QRectF target = QRectF(boundingRect());
            m_pixmap = m_spriteSheetPixmap.transformed(QTransform().scale(m_horizontal, m_vertical),
                                                       smooth() ? Qt::SmoothTransformation : Qt::FastTransformation);
            QRectF source = QRectF(frameX(),
                                   frameY(),
                                   frameWidth(),
                                   frameHeight());

            painter->drawPixmap(target, m_pixmap, source);
        }
    }
}

qreal Sprite::frameX() const
{
    return m_frameX <= 0.0 ? 0.0 : m_frameX;
}

void Sprite::setFrameX(const qreal &frameX)
{
    if (frameX == m_frameX)
        return;

    m_frameX = frameX;
    update();

    emit frameXChanged();
}

qreal Sprite::frameY() const
{
    return m_frameY <= 0.0 ? 0.0 : m_frameY;
}

void Sprite::setFrameY(const qreal &frameY)
{
    if (m_frameY == frameY)
        return;

    m_frameY = frameY;
    update();

    emit frameYChanged();
}

qreal Sprite::frameWidth() const
{
    // Default value if frame width is not set
    if (m_frameWidth <= 0.0 && m_spriteSheet && m_spriteSheet->horizontalFrameCount() > 0)
        return m_spriteSheetPixmap.width() / m_spriteSheet->horizontalFrameCount();

    return m_frameWidth;
}

void Sprite::setFrameWidth(const qreal &frameWidth)
{
    if (m_frameWidth == frameWidth)
        return;

    m_frameWidth = frameWidth;
    emit frameWidthChanged();
}

qreal Sprite::frameHeight() const
{
    // Default value if frame height is not set
    if (m_frameHeight <= 0.0 && m_spriteSheet && m_spriteSheet->verticalFrameCount() > 0)
        return m_spriteSheetPixmap.height() / m_spriteSheet->verticalFrameCount();

    return m_frameHeight;
}

void Sprite::setFrameHeight(const qreal &frameHeight)
{
    if (m_frameHeight == frameHeight)
        return;

    m_frameHeight = frameHeight;
    emit frameHeightChanged();
}
