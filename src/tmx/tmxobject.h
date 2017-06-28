/**
 * The MIT License (MIT)
 *
 * Copyright (C) 2017 Bacon2D Project
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef TMXOBJECT_H
#define TMXOBJECT_H

#include <libtiled/object.h>
#include <libtiled/properties.h>

#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtCore/QString>

class TMXObject : public QObject
{
    Q_OBJECT

public:
    explicit TMXObject(Tiled::Object *tiledObject, QObject *parent = 0)
        : QObject(parent), m_tiledObject(tiledObject) {}

    TMXObject(const TMXObject &other) { setTiledObject(other.tiledObject()); }

    Tiled::Object *tiledObject() const { return m_tiledObject; }
    void setTiledObject(Tiled::Object *tiledObject) { m_tiledObject = tiledObject; }

    QVariant property(const QString &name) const { return m_tiledObject->property(name); }
    void setProperty(const QString &name, const QVariant &value) { m_tiledObject->setProperty(name, value); }
    const QMap<QString, QVariant> &properties() const { return m_tiledObject->properties(); }

private:
    Tiled::Object *m_tiledObject;
};

#endif // TMXOBJECT_H
