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

#include "scrollbehavior.h"

#include <QtQml/QQmlExpression>

#include "bacon2dlayer.h"
#include "bacon2dimagelayer.h"
#include "layerscrollbehavior.h"
#include "imagelayerscrollbehavior.h"

/*!
  \qmltype ScrollBehavior
  \inqmlmodule Bacon2D
  \inherits Behavior
  \brief ScrollBehavior is a \l Behavior that scrolls its content based on horizontalStep and verticalStep properties.

  It can be used to scroll a ImageLayer or the elements inside a Layer

  \qml
  Game {
      width: 200
      height: 100

      currentScene: Scene {
          id: scene

          anchors.fill: parent

          Layer {
              anchors.fill: parent

              behavior: ScrollBehavior {
                  horizontalStep: 2
              }

              Rectangle {
                  width: 10
                  height: 10
                  color: "red"
              }
          }
      }
  }
  \endqml
 */
ScrollBehavior::ScrollBehavior(QObject *parent)
    : Behavior(parent)
    , m_currentBehavior(0)
    , m_horizontalStep(0)
    , m_verticalStep(0)
{
}

void ScrollBehavior::update(const int &delta)
{
    if (!m_currentBehavior)
        return;

    m_currentBehavior->setHorizontalStep(m_horizontalStep);
    m_currentBehavior->setVerticalStep(m_verticalStep);

    m_currentBehavior->update(delta);
}

void ScrollBehavior::setTarget(QQuickItem *target)
{
    if (m_target == target)
        return;

    m_target = target;

    if (m_currentBehavior) {
        delete m_currentBehavior;
        m_currentBehavior = 0;
    }

    if (dynamic_cast<Bacon2DImageLayer*>(target))
        m_currentBehavior = new ImageLayerScrollBehavior(this);
    else if (dynamic_cast<Bacon2DLayer*>(target))
        m_currentBehavior = new LayerScrollBehavior(this);

    if (!m_currentBehavior)
        return;

    m_currentBehavior->setTarget(m_target);
}

qreal ScrollBehavior::horizontalStep()
{
    return m_horizontalStep;
}

void ScrollBehavior::setHorizontalStep(qreal step)
{
    m_horizontalStep = step;
}


qreal ScrollBehavior::verticalStep()
{
    return m_verticalStep;
}

void ScrollBehavior::setVerticalStep(qreal step)
{
    m_verticalStep = step;
}
