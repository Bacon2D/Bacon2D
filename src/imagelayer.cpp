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

#include "imagelayer.h"

#include <QImage>
#include <QPainter>

// ImageLayerShader
const char *ImageLayerShader::vertexShader() const
{
    return
        "attribute highp vec4 aVertex;"
        "attribute highp vec2 aTexCoord;"

        "uniform highp mat4 qt_Matrix;"
        "varying highp vec2 texCoord;"

        "void main() {"
        "    texCoord = aTexCoord;"
        "    gl_Position = qt_Matrix * aVertex;"
        "}";
}

const char *ImageLayerShader::fragmentShader() const {
    return
        "uniform lowp float qt_Opacity;"
        "varying highp vec2 texCoord;"

        "uniform sampler2D texture;"
        "uniform highp float xPos;"
        "uniform highp float yPos;"

        "void main() {"
        "   gl_FragColor = texture2D(texture, vec2(texCoord.x + xPos, texCoord.y + yPos)) * qt_Opacity;"
        "}";
}

QList<QByteArray> ImageLayerShader::attributes() const
{
    return QList<QByteArray>() << "aVertex" << "aTexCoord";
}

void ImageLayerShader::initialize()
{
    if (!program()->isLinked())
        return;

    QSGSimpleMaterialShader<ImageLayerState>::initialize();
    program()->bind();

    m_idTexture = program()->uniformLocation("texture");
    m_idXPos = program()->uniformLocation("xPos");
    m_idYPos = program()->uniformLocation("yPos");
}

void ImageLayerShader::updateState(const ImageLayerState *newState, const ImageLayerState *oldState)
{
    if (!oldState)
        newState->texture->bind();

    if (!oldState || oldState->xPos != newState->xPos)
        program()->setUniformValue(m_idXPos, (GLfloat)newState->xPos);
    if (!oldState || oldState->yPos != newState->yPos)
        program()->setUniformValue(m_idYPos, (GLfloat)newState->yPos);

}

void ImageLayerShader::resolveUniforms()
{
    program()->setUniformValue(m_idTexture, 0);
}
// ImageLayerShader

// ImageLayerNode
ImageLayerNode::ImageLayerNode(QQuickWindow *window, const QString file, bool mirroredType)
{
    QImage image(file);

    // NOTE this is a workaround to get the mirrored effect at the end of the image
    // ideally, do it using the shader program
    if (mirroredType) {
        QImage tempImage(image.width() * 2, image.height(), QImage::Format_ARGB32);
        QPainter p(&tempImage);
            p.drawImage(0, 0, image);
            p.drawImage(image.width(), 0, image.mirrored(true, false));
        p.end();

        image = tempImage;
    }

    QSGTexture *texture = window->createTextureFromImage(image);

    texture->setHorizontalWrapMode(QSGTexture::Repeat);
    texture->setVerticalWrapMode(QSGTexture::Repeat);
    texture->setFiltering(QSGTexture::Linear);

    m_width = texture->textureSize().width();
    m_height = texture->textureSize().height();

    QSGSimpleMaterial<ImageLayerState> *m = ImageLayerShader::createMaterial();
    m->state()->texture = texture;
    setMaterial(m);
    setFlag(OwnsMaterial, true);

    updateXPos(0);
    updateYPos(0);

    QSGGeometry *g = new QSGGeometry(QSGGeometry::defaultAttributes_TexturedPoint2D(), 4);
    QSGGeometry::updateTexturedRectGeometry(g, QRect(), QRect());
    setGeometry(g);

    setFlag(OwnsGeometry, true);
}

void ImageLayerNode::setRect(const QRectF &bounds)
{
    QSGGeometry::updateTexturedRectGeometry(geometry(), bounds, QRectF(0, 0, 1, 1));
    markDirty(QSGNode::DirtyGeometry);
}

void ImageLayerNode::updateXPos(const qreal pos)
{
    QSGSimpleMaterial<ImageLayerState> *m =
        static_cast<QSGSimpleMaterial<ImageLayerState> *>(material());

    m->state()->xPos = -(pos / m_width);
    markDirty(QSGNode::DirtyMaterial);
}

void ImageLayerNode::updateYPos(const qreal pos)
{
    QSGSimpleMaterial<ImageLayerState> *m =
        static_cast<QSGSimpleMaterial<ImageLayerState> *>(material());

    m->state()->yPos = -(pos / m_height);
    markDirty(QSGNode::DirtyMaterial);
}

qreal ImageLayerNode::imageWidth() const
{
    return m_width;
}

qreal ImageLayerNode::imageHeight() const
{
    return m_height;
}
// ImageLayerNode

// ImageLayer
/*!
  \qmltype ImageLayer
  \inqmlmodule Bacon2D
  \inherits Layer
  \brief A layer created from a image

  An ImageLayer can be used to create parallax effects like an infinite 
  scrolling background useful in creating side-scrolling games.
*/
ImageLayer::ImageLayer(Layer *parent)
    : Layer((QQuickItem *)parent)
    , m_imageWidth(0)
    , m_imageHeight(0)
    , m_geometryChanged(false)
{
    setFlag(ItemHasContents, true);
}

ImageLayer::~ImageLayer()
{
}

void ImageLayer::setSource(const QUrl &source)
{
    if (m_source == source)
        return;

    m_source = source;

    emit sourceChanged();
    QQuickItem::update();
}

/*!
  \qmlproperty string ImageLayer::source
  \brief This property represents the source path for the image
*/
QUrl ImageLayer::source() const
{
    return m_source;
}

QSGNode *ImageLayer::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    ImageLayerNode *n = static_cast<ImageLayerNode *>(oldNode);

    if (boundingRect().isEmpty()) {
        delete n;
        return 0;
    }

    if (!n) {
        // thanks to Ken VanDine for the file location fix:
        QString localFile;

        if (m_source.url().startsWith("qrc:/"))
            localFile = m_source.url().replace(QString("qrc:/"), QString(":/"));
        else
            localFile = m_source.toLocalFile();

        n = new ImageLayerNode(window(), localFile,
                (m_type == Layer::Mirrored) ? true : false);

        m_imageWidth = n->imageWidth();
        m_imageHeight = n->imageHeight();
    }

    n->updateXPos(m_horizontalOffset);
    n->updateYPos(m_verticalOffset);

    if (m_geometryChanged) {
        // simple workaround to deal with resizing
        // works when imageWidth > imageHeigth; should test when dealing with vertical scrolling images
        // FAIL: it doesn't work when resizing to a width > that imageWidth :'(
        qreal factor = m_imageWidth / m_imageHeight;
        qreal w = height() * factor;

        QRectF r(0, 0, w, height());

        n->setRect(r);
        m_geometryChanged = false;
    }

    return n;
}

void ImageLayer::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    Layer::geometryChanged(newGeometry, oldGeometry);
    if (newGeometry.isEmpty() || !isComponentComplete())
        return;

    m_geometryChanged = true;

    QQuickItem::update();
}

void ImageLayer::componentComplete()
{
    Layer::componentComplete();
}

void ImageLayer::setContentGeometry(const QRectF &geometry)
{
    setWidth(geometry.width());
    setHeight(geometry.height());
}

void ImageLayer::update(const int &delta)
{
    Layer::update(delta);
    QQuickItem::update();
}

qreal ImageLayer::imageWidth()
{
    return m_imageWidth;
}

qreal ImageLayer::imageHeight()
{
    return m_imageHeight;
}

qreal ImageLayer::horizontalOffset()
{
    return m_horizontalOffset;
}

void ImageLayer::setHorizontalOffset(qreal offset)
{
    m_horizontalOffset = offset;
}


qreal ImageLayer::verticalOffset()
{
    return m_verticalOffset;
}

void ImageLayer::setVerticalOffset(qreal offset)
{
    m_verticalOffset = offset;
}


// ImageLayer
