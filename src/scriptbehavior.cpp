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
