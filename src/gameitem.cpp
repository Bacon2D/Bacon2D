#include "gameitem.h"

#include <QDeclarativeExpression>

GameItem::GameItem(QQuickItem *parent)
    : QQuickItem(parent),
      m_expression(0),
      m_updateInterval(0)
{
}

void GameItem::update(long delta)
{
    if ((m_updateInterval && m_updateTime.elapsed() >= m_updateInterval)
        || !m_updateInterval) {
        m_updateTime.restart();
        if (m_expression)
            m_expression->evaluate();
    }
}

QDeclarativeScriptString GameItem::updateScript() const
{
    return m_updateScript;
}

void GameItem::setUpdateScript(QDeclarativeScriptString updateScript)
{
    m_updateScript = updateScript;

    if (m_expression)
        delete m_expression;

    m_expression = new QDeclarativeExpression(m_updateScript.context(), m_updateScript.scopeObject(), m_updateScript.script());

    emit updateScriptChanged();
}

int GameItem::updateInterval() const
{
    return m_updateInterval;
}

void GameItem::setUpdateInterval(int updateInterval)
{
    m_updateInterval = updateInterval;

    emit updateScriptChanged();
}
