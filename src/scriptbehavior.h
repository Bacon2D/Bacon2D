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

#include "behavior.h"

#if QT_VERSION >= 0x050000
#include <QtQml/QQmlScriptString>
class QQmlExpression;
#else
#include <QtDeclarative/QDeclarativeScriptString>
class QDeclarativeExpression;
#endif

class ScriptBehavior : public  Behavior
{
    Q_OBJECT

#if QT_VERSION >= 0x050000
    Q_PROPERTY(QQmlScriptString script READ script WRITE setScript NOTIFY scriptChanged)
#else
    Q_PROPERTY(QDeclarativeScriptString script READ script WRITE setScript NOTIFY scriptChanged)
#endif

public:
    ScriptBehavior(QObject *parent = 0);

#if QT_VERSION >= 0x050000
    QQmlScriptString script() const;
    void setScript(const QQmlScriptString &script);
#else
    QDeclarativeScriptString script() const;
    void setScript(const QDeclarativeScriptString &script);
#endif
    void update(const int &delta);

signals:
    void scriptChanged();

private:
#if QT_VERSION >= 0x050000
    QQmlScriptString m_script;
    QQmlExpression *m_expression;
#else
    QDeclarativeScriptString m_script;
    QDeclarativeExpression *m_expression;
#endif
};
