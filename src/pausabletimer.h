#ifndef PAUSABLETIMER_H
#define PAUSABLETIMER_H

#include <QObject>
#include <QQmlParserStatus>

class QTimer;

class PausableTimer : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)
    Q_PROPERTY(bool repeat READ repeat WRITE setRepeat NOTIFY repeatChanged)
    Q_PROPERTY(bool triggeredOnStart READ triggeredOnStart WRITE setTriggeredOnStart NOTIFY triggeredOnStartChanged)
public:
    PausableTimer(QObject *parent = nullptr);

    virtual void classBegin();
    virtual void componentComplete();

    bool running() const;
    void setRunning(bool running);

    qint64 interval() const;
    void setInterval(qint64 interval);

    bool repeat() const;
    void setRepeat(bool);

    bool triggeredOnStart() const;
    void setTriggeredOnStart(bool triggeredOnStart);
signals:
    void timeout();
    void startupTimeout();

    void runningChanged();
    void intervalChanged();
    void repeatChanged();
    void triggeredOnStartChanged();
public slots:
    void resume();
    void pause();
    void start();
    void restart();
    void stop();
private slots:
    void onTimeout();
private:
    QTimer *m_timer;
    qint64 m_interval;
    bool m_paused;
    bool m_repeat;
    bool m_triggeredOnStart;
};

#endif // PAUSABLETIMER_H
