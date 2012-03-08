#include "animatedlayer.h"

AnimatedLayer::AnimatedLayer(Layer *parent)
    : Layer(parent)
      , m_horizontalStep(0)
      , m_currentHorizontalStep(0)
{
}

AnimatedLayer::~AnimatedLayer()
{
}

void AnimatedLayer::setHorizontalStep(const qreal &step)
{
    int temp = step;
    if (temp < 0)
        temp *= -1;

    if (temp != m_horizontalStep){
        m_horizontalStep = temp;

        emit horizontalStepChanged();
    }
}

#include <QDebug>
void AnimatedLayer::updateHorizontalStep()
{
    m_currentHorizontalStep += m_horizontalStep;

    if (m_currentHorizontalStep * m_factor >= boundingRect().width()){
        drawPixmap();
        m_currentHorizontalStep = 0;
    }

    //update(); // XXX with this we get super velocity plus no flick, but more CPU consumption too =/
}

void AnimatedLayer::paint(QPainter *painter)
{
    updateHorizontalStep();

    if (m_currentPixmap)
        painter->drawPixmap(m_currentHorizontalStep * m_direction * m_factor, 0, *m_currentPixmap);
}
