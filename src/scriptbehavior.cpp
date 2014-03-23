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

#include "scriptbehavior.h"

#if QT_VERSION >= 0x050000
#include <QtQml/QQmlExpression>
#else
#include <QtDeclarative/QDeclarativeExpression>
#endif

ScriptBehavior::ScriptBehavior(QObject *parent)
    : Behavior(parent)
    , m_expression(0)
{
}

void ScriptBehavior::update(const int &delta) {
    Q_UNUSED(delta);

    if (m_expression) {
        m_expression->evaluate();
    }
}

#if QT_VERSION >= 0x050000
QQmlScriptString ScriptBehavior::script() const
#else
QDeclarativeScriptString ScriptBehavior::script() const
#endif
{
    return m_script;
}

#if QT_VERSION >= 0x050000
void ScriptBehavior::setScript(const QQmlScriptString &script)
#else
void ScriptBehavior::setScript(const QDeclarativeScriptString &script)
#endif
{
    if (m_script.stringLiteral() != script.stringLiteral()) {
        m_script = script;

        if (m_expression)
            delete m_expression;

#if QT_VERSION >= 0x050000
        m_expression = new QQmlExpression(m_script);
#else
        m_expression = new QDeclarativeExpression(m_script.context(), m_script.scopeObject(), m_script.script());
#endif

        emit scriptChanged();
    }
}
