#include "layerscrollbehavior.h"

LayerScrollBehavior::LayerScrollBehavior(QObject *parent)
    : ScrollBehaviorImpl(parent)
{
}

void LayerScrollBehavior::update(const int &delta)
{
    Q_UNUSED(delta);

    QQuickItem *child;
    foreach (child, m_target->childItems()) {
        if (QQuickItem *item = dynamic_cast<QQuickItem*>(child)) {
            item->setX(item->x() + m_horizontalStep);
            item->setY(item->y() + m_verticalStep);
        }
    }
}
