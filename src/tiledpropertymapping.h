#ifndef TILEDPROPERTYMAPPING_H
#define TILEDPROPERTYMAPPING_H

#include <QObject>
#include <QVariant>

class TiledPropertyMapping : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString property READ property WRITE setProperty NOTIFY propertyChanged)
    Q_PROPERTY(QString mapsTo READ mapsTo WRITE setMapsTo NOTIFY mapsToChanged)
    Q_PROPERTY(QVariant defaultValue READ defaultValue WRITE setDefaultValue NOTIFY defaultValueChanged)
public:
    explicit TiledPropertyMapping(QObject *parent = nullptr);

    QString property() const;
    void setProperty(const QString &property);

    QString mapsTo() const;
    void setMapsTo(const QString &mapsTo);

    QVariant defaultValue() const;
    void setDefaultValue(const QVariant &defaultValue);
signals:
    void propertyChanged();
    void mapsToChanged();
    void defaultValueChanged();
private:
    QString m_property;
    QString m_mapsTo;
    QVariant m_defaultValue;
};

#endif // TILEDPROPERTYMAPPING_H
