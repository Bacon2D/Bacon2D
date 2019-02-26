#include "tiledpropertymapping.h"

TiledPropertyMapping::TiledPropertyMapping(QObject *parent)
    : QObject(parent)
{

}

QString TiledPropertyMapping::property() const
{
    return m_property;
}

void TiledPropertyMapping::setProperty(const QString &property)
{
    if (m_property == property)
        return;

    m_property = property;
    emit propertyChanged();
}

QString TiledPropertyMapping::mapsTo() const
{
    return m_mapsTo;
}

void TiledPropertyMapping::setMapsTo(const QString &mapsTo)
{
    if (m_mapsTo == mapsTo)
        return;

    m_mapsTo = mapsTo;
    emit mapsToChanged();
}

QVariant TiledPropertyMapping::defaultValue() const
{
    return m_defaultValue;
}

void TiledPropertyMapping::setDefaultValue(const QVariant &defaultValue)
{
    if (m_defaultValue == defaultValue)
        return;

    m_defaultValue = defaultValue;
    emit defaultValueChanged();
}
