#ifndef SPRITEALIAS_H
#define SPRITEALIAS_H

#include <QObject>

class SpriteAlias : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(qreal frameX READ frameX WRITE setFrameX NOTIFY frameXChanged)
    Q_PROPERTY(qreal frameY READ frameY WRITE setFrameY NOTIFY frameYChanged)
    Q_PROPERTY(qreal frameWidth READ frameWidth WRITE setFrameWidth NOTIFY frameWidthChanged)
    Q_PROPERTY(qreal frameHeight READ frameHeight WRITE setFrameHeight NOTIFY frameHeightChanged)
public:
    explicit SpriteAlias(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    qreal frameX() const;
    void setFrameX(qreal);

    qreal frameY() const;
    void setFrameY(qreal);

    qreal frameWidth() const;
    void setFrameWidth(qreal);

    qreal frameHeight() const;
    void setFrameHeight(qreal);
signals:
    void nameChanged();
    qreal frameXChanged();
    qreal frameYChanged();
    qreal frameWidthChanged();
    qreal frameHeightChanged();
private:
    QString m_name;
    qreal m_frameX;
    qreal m_frameY;
    qreal m_frameWidth;
    qreal m_frameHeight;
};

#endif // SPRITEALIAS_H
