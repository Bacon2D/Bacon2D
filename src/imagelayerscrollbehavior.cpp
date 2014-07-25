#include "imagelayerscrollbehavior.h"

#include "imagelayer.h"

ImageLayerScrollBehavior::ImageLayerScrollBehavior(QObject *parent)
    : ScrollBehaviorImpl(parent)
{
}

void ImageLayerScrollBehavior::update(const int &delta)
{
    Q_UNUSED(delta);

	ImageLayer *target = 0;
	if (!(target = dynamic_cast<ImageLayer*>(m_target)))
		return;

	target->setHorizontalOffset(target->horizontalOffset() + m_horizontalStep);
	target->setVerticalOffset(target->verticalOffset() + m_verticalStep);

	if (target->horizontalOffset() <= -target->imageWidth())
		target->setHorizontalOffset(0);
	else if (target->horizontalOffset() >= 0)
		target->setHorizontalOffset(-target->imageWidth());

	if (target->verticalOffset() <= -target->imageHeight())
		target->setVerticalOffset(0);
	else if (target->verticalOffset() >= 0)
		target->setVerticalOffset(-target->imageHeight());
}
