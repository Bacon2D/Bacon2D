/**
 * Copyright (C) 2012 by INdT
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
 * @author Rodrigo Goncalves de Oliveira <rodrigo.goncalves@openbossa.org>
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

#include "scriptbehavior.h"

#include <QtQml/QQmlExpression>

/*!
  \qmltype ScriptBehavior
  \inqmlmodule Bacon2D
  \inherits Behavior
  \brief ScriptBehavior is a \l Behavior including a script to evaluate on each update.

   The ScriptBehavior's script gets called each time the Scene update its entities. Can be used to build custom behavior, like movement logic and AI.

  \qml
  Game {
      width: 800
      height: 600
      Scene {
          width: parent.width
          height: parent.height
          Entity {
              width: parent.width
              height: parent.height
              updateInterval: 50
              behavior: ScriptBehavior {
                  script: {
                      var newPos = entity.x + 5
                      entity.x = newPos > parent.width ? 0 : newPos
                      console.log("update: x -> ", entity.x)
                  }
              }
          }
      }
  }
  \endqml
 */
ScriptBehavior::ScriptBehavior(QObject *parent)
    : Behavior(parent)
    , m_expression(0)
{
}

void ScriptBehavior::update(const int &delta) {
    Q_UNUSED(delta);

    if (m_expression) {
        m_expression->evaluate();
        if (m_expression->hasError())
            qWarning() << m_expression->error();
    }
}

/*!
 * \qmlproperty string ScriptBehavior::script
 * \brief This property contains the javascript to evaluate on each update
 */
QQmlScriptString ScriptBehavior::script() const
{
    return m_script;
}

void ScriptBehavior::setScript(const QQmlScriptString &script)
{
    m_script = script;

    if (m_expression)
        delete m_expression;

    m_expression = new QQmlExpression(m_script);

    emit scriptChanged();
}
