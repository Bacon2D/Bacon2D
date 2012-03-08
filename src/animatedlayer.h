#ifndef _ANIMATEDLAYER_H_
#define _ANIMATEDLAYER_H_

#include <QtGui/QPixmap>
#include <QtGui/QPainter>

#include "layer.h"

class AnimatedLayer : public Layer
{
    Q_OBJECT

    Q_PROPERTY(qreal horizontalStep READ horizontalStep WRITE setHorizontalStep NOTIFY horizontalStepChanged)

public:
    AnimatedLayer(Layer *parent = 0);
    ~AnimatedLayer();

    qreal horizontalStep() const { return m_horizontalStep; };
    void setHorizontalStep(const qreal &step);

    void paint(QPainter *painter);

signals:
    void horizontalStepChanged();

private:
    void updateHorizontalStep();

    qreal m_horizontalStep;
    qreal m_currentHorizontalStep;
};

#endif /* _ANIMATEDLAYER_H_ */
