#ifndef TILEDBACKGROUND_H
#define TILEDBACKGROUND_H

#include <QObject>
#include <QColor>

class TiledBackground : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color NOTIFY colorChanged)
public:
    explicit TiledBackground(QObject *parent = nullptr);

    QColor color() const;
signals:
    void colorChanged();
private:
    void setColor(const QColor &color);
private:
    QColor m_color;
};

#endif // TILEDBACKGROUND_H
