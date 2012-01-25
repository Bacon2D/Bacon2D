#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include <QtQuick/QQuickItem>

#include "gameitem.h"

class Viewport : public GameItem
{
    Q_OBJECT

    Q_PROPERTY(float xOffset READ xOffset WRITE setXOffset NOTIFY xOffsetChanged)
    Q_PROPERTY(float yOffset READ yOffset WRITE setYOffset NOTIFY yOffsetChanged)
    Q_PROPERTY(float contentWidth READ contentWidth WRITE setContentWidth NOTIFY contentWidthChanged)
    Q_PROPERTY(float contentHeight READ contentHeight WRITE setContentHeight NOTIFY contentHeightChanged)

public:
    Viewport(GameScene *parent = 0);

    float xOffset();
    void setXOffset(float xOffset);

    float yOffset();
    void setYOffset(float yOffset);

    float contentWidth() const;
    void setContentWidth(const float &contentWidth);

    float contentHeight() const;
    void setContentHeight(const float &contentHeight);

    void updateMaxOffsets();

    void setScene(GameScene *scene);

    Q_INVOKABLE void hScroll(float step);
    Q_INVOKABLE void vScroll(float step);

signals:
    void xOffsetChanged();
    void yOffsetChanged();
    void contentWidthChanged();
    void contentHeightChanged();

private:
    float m_xOffset;
    float m_yOffset;
    float m_contentWidth;
    float m_contentHeight;
    float m_maxXOffset;
    float m_maxYOffset;
    GameScene *m_scene;
};

#endif /* _VIEWPORT_H_ */
