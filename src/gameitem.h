#ifndef _GAMEITEM_H_
#define _GAMEITEM_H_

#include <QtDeclarative>
#include <QDeclarativeScriptString>

class QDeclarativeExpression;

class GameItem : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QDeclarativeScriptString updateScript READ updateScript WRITE setUpdateScript NOTIFY updateScriptChanged)

public:
    GameItem(QQuickItem *parent = 0);

    QDeclarativeScriptString updateScript() const;
    void setUpdateScript(QDeclarativeScriptString updateScript);

public slots:
    virtual void update(long delta);

signals:
    void updateScriptChanged();

private:
    QDeclarativeScriptString m_updateScript;
    QDeclarativeExpression *m_expression;
};

#endif /* _GAMEITEM_H_ */
