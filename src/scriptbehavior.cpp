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

#include <QtQml/QQmlExpression>

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
