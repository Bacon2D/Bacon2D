#ifndef _GAMEITEM_H_
#define _GAMEITEM_H_

#include <QTime>
#include <QtDeclarative>
#include <QDeclarativeScriptString>

class QDeclarativeExpression;

class GameItem : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QDeclarativeScriptString updateScript READ updateScript WRITE setUpdateScript NOTIFY updateScriptChanged)
    Q_PROPERTY(int updateInterval READ updateInterval WRITE setUpdateInterval NOTIFY updateIntervalChanged)

public:
    GameItem(QQuickItem *parent = 0);

    QDeclarativeScriptString updateScript() const;
    void setUpdateScript(QDeclarativeScriptString updateScript);

    int updateInterval() const;
    void setUpdateInterval(int updateInterval);

public slots:
    virtual void update(long delta);

signals:
    void updateScriptChanged();
    void updateIntervalChanged();

private:
    QDeclarativeScriptString m_updateScript;
    QDeclarativeExpression *m_expression;
    int m_updateInterval;
    QTime m_updateTime;
};

#endif /* _GAMEITEM_H_ */
