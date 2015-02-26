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

#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include <QtCore/QPropertyAnimation>
#include <QtCore/QEasingCurve>
#include <QtCore/QParallelAnimationGroup>

#include "entity.h"

class Viewport : public Entity
{
    Q_OBJECT

    Q_PROPERTY(float xOffset READ xOffset WRITE setXOffset NOTIFY xOffsetChanged)
    Q_PROPERTY(float yOffset READ yOffset WRITE setYOffset NOTIFY yOffsetChanged)
    Q_PROPERTY(float contentWidth READ contentWidth WRITE setContentWidth NOTIFY contentWidthChanged)
    Q_PROPERTY(float contentHeight READ contentHeight WRITE setContentHeight NOTIFY contentHeightChanged)
    Q_PROPERTY(int animationDuration READ animationDuration WRITE setAnimationDuration NOTIFY animationDurationChanged)

public:
    Viewport(Scene *parent = 0);

    float xOffset();
    void setXOffset(float xOffset);

    float yOffset();
    void setYOffset(float yOffset);

    float contentWidth() const;
    void setContentWidth(const float &contentWidth);

    float contentHeight() const;
    void setContentHeight(const float &contentHeight);

    int animationDuration() const;
    void setAnimationDuration(const int &animationDuration);

    void updateMaxOffsets();

    void setScene(Scene *scene);

    Q_INVOKABLE void hScroll(float step);
    Q_INVOKABLE void vScroll(float step);

signals:
    void xOffsetChanged();
    void yOffsetChanged();
    void contentWidthChanged();
    void contentHeightChanged();
    void animationDurationChanged();

private:
    QEasingCurve m_animationEasingCurve; // TODO expose property?
    float m_xOffset;
    float m_yOffset;
    float m_contentWidth;
    float m_contentHeight;
    float m_maxXOffset;
    float m_maxYOffset;
    Scene *m_scene;

    QParallelAnimationGroup *m_xGroupAnimation;
    QParallelAnimationGroup *m_yGroupAnimation;
    int m_animationDuration;
};

#endif /* _VIEWPORT_H_ */
