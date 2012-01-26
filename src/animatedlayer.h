#ifndef _ANIMATEDLAYER_H_
#define _ANIMATEDLAYER_H_

#include <QtGui/QPixmap>
#include <QtGui/QPainter>

#include "layer.h"

class AnimatedLayer : public Layer
{
    Q_OBJECT

    Q_PROPERTY(int horizontalStep READ horizontalStep WRITE setHorizontalStep NOTIFY horizontalStepChanged)
    Q_PROPERTY(Quasi::LayerDirection direction READ direction WRITE setDirection NOTIFY directionChanged)

public:
    AnimatedLayer(Layer *parent = 0);
    ~AnimatedLayer();

    int horizontalStep() const { return m_horizontalStep; };
    void setHorizontalStep(const int &step);

    Quasi::LayerDirection direction() const { return m_direction; };
    void setDirection(const Quasi::LayerDirection &direction);

    void paint(QPainter *painter);

signals:
    void horizontalStepChanged();
    void directionChanged();

private:
    void updateHorizontalStep();

    int m_horizontalStep;
    int m_currentHorizontalStep;
    Quasi::LayerDirection m_direction;
};

#endif /* _ANIMATEDLAYER_H_ */
