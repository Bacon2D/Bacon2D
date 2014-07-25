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
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

#include "scrollbehavior.h"

#include <QtQml/QQmlExpression>

#include "layer.h"
#include "imagelayer.h"
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

    if (dynamic_cast<ImageLayer*>(target))
        m_currentBehavior = new ImageLayerScrollBehavior(this);
    else if (dynamic_cast<Layer*>(target))
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
