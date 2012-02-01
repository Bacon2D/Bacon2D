#ifndef _BOX2DDEBUGDRAWITEM_H_
#define _BOX2DDEBUGDRAWITEM_H_

#include <QtCore/qglobal.h>
#include <QtQuick/QQuickPaintedItem>

#include <Box2D/Box2D.h>

class QPainter;
class Box2DScene;

class Box2DDebugDrawItem : public QQuickPaintedItem, public b2Draw
{
    Q_OBJECT

public:
    Box2DDebugDrawItem(Box2DScene *parent = 0);

    void paint(QPainter *painter);

    void DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color);
    void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color);
    void DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color);
    void DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color);
    void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color);
    void DrawTransform(const b2Transform &xf);

    void step();

private:
    void draw();

private:
    QPainter *m_painter;
    Box2DScene *m_scene;
};

#endif /* _BOX2DDEBUGDRAWITEM_H_ */
