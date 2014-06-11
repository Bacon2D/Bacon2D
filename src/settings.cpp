/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** Copyright (C) 2014 Bacon2D Project
**
** This file is part of the Bacon2D project, based on an example from
** the Qt Toolkit.
**
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include "settings.h"

/*!
  \qmltype Settings
  \inqmlmodule Bacon2D
  \brief Provides local storage for settings or any in game data 

   Persistent Local storage for settings or any in game data, limited to 
   key/value pair.
 */
Settings::Settings(QObject *parent)
    : QObject(parent)
    , initialPropertyCount(metaObject()->propertyCount())
    , timerId(0)
    , propertyChanges(0)
    , isComplete(false)
{
}

Settings::~Settings()
{
}

void Settings::componentComplete()
{
    load();
    isComplete = true;
}

void Settings::load()
{
    const QMetaObject *mo = metaObject();
    int propertyCount = mo->propertyCount();
    for (int i = initialPropertyCount; i < propertyCount; ++i) {
        const QMetaProperty &property = mo->property(i);
        const QString name(property.name());

        QVariant previousValue = property.read(this);
        QVariant currentValue = m_settings.value(name, previousValue);

        if (!currentValue.isNull()
                && currentValue.canConvert(previousValue.type())
                && previousValue != currentValue)
            property.write(this, currentValue);

        // Setup change notifications on first load
        if (!isComplete && property.hasNotifySignal()) {
            static int pcSlot = metaObject()->indexOfSlot("propertyChanged()");
            Q_ASSERT(pcSlot != -1);

            bool ok = QMetaObject::connect(this, property.notifySignalIndex(), this, pcSlot);
            Q_UNUSED(ok) Q_ASSERT(ok);
        }
    }
}

void Settings::store()
{
    const QMetaObject *mo = metaObject();
    int propertyCount = mo->propertyCount();
    for (int i = initialPropertyCount; i < propertyCount; ++i) {
        const QMetaProperty &property = mo->property(i);
        m_settings.setValue(property.name(), property.read(this));
    }

    propertyChanges = 0;
}

void Settings::propertyChanged()
{
    ++propertyChanges;
    if (timerId == 0)
        timerId = startTimer(500);
}

void Settings::timerEvent(QTimerEvent *)
{
    if (propertyChanges == 0) {
        killTimer(timerId);
        timerId = 0;
        return;
    }

    store();
}

/*!
  \qmlproperty string Settings::category
  \brief This property holds a category to use for grouping settings.

   This is useful to separate game settings from game saved data like 
   high scores, etc.
*/
QString Settings::category() const
{
    return m_settings.group();
}

void Settings::setCategory(const QString &category)
{
    if (propertyChanges)
        store();
    if (!m_settings.group().isEmpty())
        m_settings.endGroup();

    if (!category.isEmpty())
        m_settings.beginGroup(category);
    if (isComplete)
        load();
}
