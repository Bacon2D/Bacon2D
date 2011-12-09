#ifndef _GAMEITEM_H_
#define _GAMEITEM_H_

#include <QTime>
#include <QtDeclarative>
#include <QDeclarativeScriptString>

class QDeclarativeExpression;
class GameScene;

class GameItem : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QDeclarativeScriptString updateScript READ updateScript WRITE setUpdateScript NOTIFY updateScriptChanged)
    Q_PROPERTY(int updateInterval READ updateInterval WRITE setUpdateInterval NOTIFY updateIntervalChanged)
    Q_PROPERTY(bool collided READ collided WRITE setCollided NOTIFY collidedChanged)

public:
    GameItem(GameScene *parent = 0);

    QDeclarativeScriptString updateScript() const;
    void setUpdateScript(QDeclarativeScriptString updateScript);

    int updateInterval() const;
    void setUpdateInterval(int updateInterval);

    bool collided();
    void setCollided(bool collided);

    Q_INVOKABLE QList<QObject *> collidedItems();

public slots:
    virtual void update(long delta);

signals:
    void updateScriptChanged();
    void updateIntervalChanged();
    void collidedChanged();

private:
    QDeclarativeScriptString m_updateScript;
    QDeclarativeExpression *m_expression;
    int m_updateInterval;
    QTime m_updateTime;
    bool m_collided;
};

#endif /* _GAMEITEM_H_ */
