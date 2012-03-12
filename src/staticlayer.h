#ifndef _STATICLAYER_H_
#define _STATICLAYER_H_

#include <QtGui/QPixmap>
#include <QtGui/QPainter>

#include "layer.h"

class StaticLayer : public Layer
{
    Q_OBJECT

public:
    StaticLayer(Layer *parent = 0);
    ~StaticLayer();

    Q_INVOKABLE void moveX(qreal value);
    // XXX moveY

    void paint(QPainter *painter);

private:
    QList<QPixmap> m_mirroredTiles; // XXX
    qreal m_globalXPos; // global positioning
    qreal m_localXPos; // local positioning
};

#endif /* _STATICLAYER_H_ */
