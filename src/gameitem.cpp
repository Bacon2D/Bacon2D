#include "gameitem.h"

#include <QDeclarativeExpression>

GameItem::GameItem(QQuickItem *parent)
    : QQuickItem(parent),
      m_expression(0)
{
}

void GameItem::update(long delta)
{
    if (m_expression)
        m_expression->evaluate();
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

    m_expression = new QDeclarativeExpression(m_updateScript);

    emit updateScriptChanged();
}
