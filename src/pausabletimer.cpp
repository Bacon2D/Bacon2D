#include "pausabletimer.h"
#include <QTimer>

/*!
    \qmltype PausableTimer
    \inqmlmodule Bacon2D
    \inherits QtObject
    \brief Timer that can be paused by the user at will

    The PausableTimer component is just like the Timer provided by Qt,
    the added ability to be paused by the user at any given time. Its
    interface is exactly the same at \a Timer, the only difference being
    that setting running to false does not stop the timer, but pauses it
    until set to true again. This allows you to bind the running flag to
    the application state, as illustrated below.

    Example usage:
    \qml
    import QtQuick 2.0
    import Bacon2D 1.0

    Game {
       id: game
       ...
    }

    PhysicsEntity {
        id: laserCannon
        ...
    }

    PausableTimer {
        id: fireTimer
        running: game.gameState == Bacon2D.Paused
        interval: 500
        onTriggered: laserCannon.fire(); // Will not be called while the game is paused.
    }
   \endqml
*/
PausableTimer::PausableTimer(QObject *parent)
    : m_timer(new QTimer(this))
    , m_interval(0)
    , m_paused(true)
    , m_repeat(false)
    , m_triggeredOnStart(false)
    , QObject(parent)
{
}

void PausableTimer::classBegin()
{
    m_timer->setSingleShot(true);
    connect(m_timer, &QTimer::timeout, this, &PausableTimer::onTimeout);
}

void PausableTimer::componentComplete()
{
    if (m_timer->isActive() && m_triggeredOnStart)
        emit triggered();
}

/*!
  \qmlproperty bool PauseableTimer::running
  \brief This property holds whether the timer is not paused or stopped.
*/

bool PausableTimer::running() const
{
    return !m_paused || m_timer->isActive();
}

void PausableTimer::setRunning(bool running)
{
    if (!m_paused == running)
        return;

    if (!m_paused)
        pause();
    else
        resume();

    emit runningChanged();
}

qint64 PausableTimer::interval() const
{
    return m_interval;
}

void PausableTimer::setInterval(qint64 interval)
{
    if (m_interval == interval)
        return;

    m_interval = interval;
    emit intervalChanged();
}

bool PausableTimer::repeat() const
{
    return m_repeat;
}

void PausableTimer::setRepeat(bool repeat)
{
    if (m_repeat == repeat)
        return;

    m_repeat = repeat;
    emit repeatChanged();
}

bool PausableTimer::triggeredOnStart() const
{
    return m_triggeredOnStart;
}

void PausableTimer::setTriggeredOnStart(bool triggeredOnStart)
{
    if (m_triggeredOnStart == triggeredOnStart)
        return;

    m_triggeredOnStart = triggeredOnStart;
    emit triggeredOnStartChanged();
}

void PausableTimer::resume()
{
    if (!m_paused)
        return;

    m_paused = false;
    m_timer->start();
}

void PausableTimer::pause()
{
    if (m_paused || !m_timer->isActive())
        return;

    m_paused = true;
    if (m_timer->isActive() && m_timer->remainingTime() > -1)
        m_timer->setInterval(m_timer->remainingTime());
    m_timer->stop();
}

void PausableTimer::start()
{
    m_paused = false;
    m_timer->start();
}

void PausableTimer::restart()
{
    m_paused = false;
    m_timer->stop();
    m_timer->setInterval(m_interval);
    m_timer->start();
}

void PausableTimer::stop()
{
    m_paused = false;
    m_timer->stop();
}

void PausableTimer::onTimeout()
{
    emit triggered();

    m_timer->setInterval(m_interval);
    if (m_repeat)
        m_timer->start();
}
