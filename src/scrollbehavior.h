/**
 * The MIT License (MIT)
 *
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
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

#ifndef SCROLLBEHAVIOR_H
#define SCROLLBEHAVIOR_H

#include "scrollbehaviorimpl.h"

class ScrollBehavior : public Behavior
{
    Q_OBJECT
    Q_PROPERTY(qreal horizontalStep READ horizontalStep WRITE setHorizontalStep)
    Q_PROPERTY(qreal verticalStep READ verticalStep WRITE setVerticalStep)
public:
    explicit ScrollBehavior(QObject *parent = nullptr);

    virtual void update(const int &delta);
    virtual void setTarget(QQuickItem *target);

    qreal horizontalStep();
    void setHorizontalStep(qreal step);

    qreal verticalStep();
    void setVerticalStep(qreal step);
private:
    ScrollBehaviorImpl *m_currentBehavior;
    qreal m_horizontalStep;
    qreal m_verticalStep;
};

#endif // SCROLLBEHAVIOR_H
