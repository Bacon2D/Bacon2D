/**
 * Copyright (C) 2012 by INdT
 * Copyright (C) 2014 Bacon2D Project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * @author Rodrigo Goncalves de Oliveira <rodrigo.goncalves@openbossa.org>
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

#ifndef _IMAGELAYER_H_
#define _IMAGELAYER_H_

#include "layer.h"

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
};
// ImageLayerShader

// ImageLayerNode
class ImageLayerNode : public QSGGeometryNode
{
public:
    ImageLayerNode(QQuickWindow *window, const QString file, bool mirroredType = false);

    void setRect(const QRectF &bounds);
    void updateXPos(const qreal pos);

    qreal imageWidth() const;
    qreal imageHeight() const;

private:
    qreal m_width;
    qreal m_height;
};
// ImageLayerNode

// ImageLayer (finally ;D)
class ImageLayer : public Layer
{
    Q_OBJECT

    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)

public:
    ImageLayer(Layer *parent = 0);
    ~ImageLayer();

    void setSource(const QUrl &source);
    QUrl source() const;

    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
    void setContentGeometry(const QRectF &geometry);

signals:
    void sourceChanged();

protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

protected:
    void componentComplete();

private:
    void updateHorizontalStep();

    QUrl m_source;
    qreal m_currentHorizontalStep;

    qreal m_imageWidth;
    qreal m_imageHeight;

    bool m_geometryChanged;
};
// ImageLayer

#endif /* _IMAGELAYER_H_ */
