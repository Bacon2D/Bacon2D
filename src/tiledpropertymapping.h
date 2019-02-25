#ifndef TILEDPROPERTYMAPPING_H
#define TILEDPROPERTYMAPPING_H

#include <QObject>

class TiledPropertyMapping : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString property READ property WRITE setProperty NOTIFY propertyChanged)
    Q_PROPERTY(QString mapsTo READ mapsTo WRITE setMapsTo NOTIFY mapsToChanged)
public:
    explicit TiledPropertyMapping(QObject *parent = nullptr);

    QString property() const;
    void setProperty(const QString &property);

    QString mapsTo() const;
    void setMapsTo(const QString &mapsTo);
signals:
    void propertyChanged();
    void mapsToChanged();
private:
    QString m_property;
    QString m_mapsTo;
};

#endif // TILEDPROPERTYMAPPING_H
