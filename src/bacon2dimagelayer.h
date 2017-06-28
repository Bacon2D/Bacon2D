/**
 * The MIT License (MIT)
 *
 * Copyright (C) 2012 by INdT
 * Copyright (C) 2014 Bacon2D Project
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @author Rodrigo Goncalves de Oliveira <rodrigo.goncalves@openbossa.org>
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

#ifndef _IMAGELAYER_H_
#define _IMAGELAYER_H_

#include "bacon2dlayer.h"

#include <QSGTexture>
#include <QQuickWindow>
#include <QSGSimpleMaterialShader>
#include <QSGGeometryNode>

// ImageLayerState
struct ImageLayerState
{
    ~ImageLayerState() {
        delete texture;
    }

    QSGTexture *texture;
    qreal xPos;
    qreal yPos;
};
// ImageLayerState

// ImageLayerShader
class ImageLayerShader : public QSGSimpleMaterialShader<ImageLayerState>
{
    QSG_DECLARE_SIMPLE_SHADER(ImageLayerShader, ImageLayerState)

public:
    const char *vertexShader() const;
    const char *fragmentShader() const;
    QList<QByteArray> attributes() const;

    void initialize();
    void updateState(const ImageLayerState *newState, const ImageLayerState *oldState);
    void resolveUniforms();

private:
    int m_idTexture;
    int m_idXPos;
    int m_idYPos;
};
// ImageLayerShader

// ImageLayerNode
class ImageLayerNode : public QSGGeometryNode
{
public:
    ImageLayerNode(QQuickWindow *window, const QString file, bool mirroredType = false);

    void setRect(const QRectF &bounds);
    void updateXPos(const qreal pos);
    void updateYPos(const qreal pos);

    qreal imageWidth() const;
    qreal imageHeight() const;

private:
    qreal m_width;
    qreal m_height;
};
// ImageLayerNode

// ImageLayer (finally ;D)
class Bacon2DImageLayer : public Bacon2DLayer
{
    Q_OBJECT

    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(qreal imageWidth READ imageWidth)
    Q_PROPERTY(qreal imageHeight READ imageHeight)
    Q_PROPERTY(qreal horizontalOffset READ horizontalOffset WRITE setHorizontalOffset)
    Q_PROPERTY(qreal verticalOffset READ verticalOffset WRITE setVerticalOffset)

public:
    Bacon2DImageLayer(Bacon2DLayer *parent = 0);
    ~Bacon2DImageLayer();

    virtual void update(const int &delta);

    void setSource(const QUrl &source);
    QUrl source() const;

    qreal imageWidth();
    qreal imageHeight();

    qreal horizontalOffset();
    void setHorizontalOffset(qreal offset);

    qreal verticalOffset();
    void setVerticalOffset(qreal offset);

    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
    void setContentGeometry(const QRectF &geometry);

signals:
    void sourceChanged();

protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

protected:
    void componentComplete();

private:
    QUrl m_source;

    qreal m_imageWidth;
    qreal m_imageHeight;
    qreal m_horizontalOffset;
    qreal m_verticalOffset;

    bool m_geometryChanged;
};
// ImageLayer

#endif /* _IMAGELAYER_H_ */
