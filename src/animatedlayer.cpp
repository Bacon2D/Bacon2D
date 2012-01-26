#include "animatedlayer.h"

AnimatedLayer::AnimatedLayer(Layer *parent)
    : Layer(parent)
      , m_horizontalStep(0)
      , m_currentHorizontalStep(0)
      , m_direction((Quasi::LayerDirection)-1) // Backward
{
}

AnimatedLayer::~AnimatedLayer()
{
}

void AnimatedLayer::setHorizontalStep(const int &step)
{
    int temp = step;
    if (temp < 0)
        temp *= -1;

    if (temp != m_horizontalStep){
        m_horizontalStep = temp;

        emit horizontalStepChanged();
    }
}

void AnimatedLayer::updateHorizontalStep()
{
    m_currentHorizontalStep += m_horizontalStep;

    if (m_currentHorizontalStep >= boundingRect().width()){
        drawPixmap();
        m_currentHorizontalStep = 0;
    }

    //update(); // XXX with this we get super velocity plus no flick, but more CPU consumption too =/
}

void AnimatedLayer::setDirection(const Quasi::LayerDirection &direction)
{
    if (direction != m_direction){
        if (direction == Quasi::BackwardDirection)
            m_direction = (Quasi::LayerDirection)-1; // insane black magic
        else
            m_direction = direction;


        emit directionChanged();
    }
}

void AnimatedLayer::paint(QPainter *painter)
{
    updateHorizontalStep();
    painter->drawPixmap(m_currentHorizontalStep * m_direction * m_factor, 0, *m_currentPixmap);
}
