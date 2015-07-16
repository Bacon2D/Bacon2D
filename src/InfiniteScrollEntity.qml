import QtQuick 2.3

/*!
  \qmltype InfiniteScrollEntity
  \inqmlmodule Bacon2D
  \inherits Item
  \ingroup graphics
  \brief Enable an Item to do a infinite scroll. Good for moving background
*/
Item {
    id: root

    /*!
      \qmlproperty Item InfiniteScrollEntity::target
      \brief \l Item that will used as texture for scrolling effect.
    */
    default property Item target

    /*!
      \qmlproperty Item InfiniteScrollEntity::offsetX
      \brief \l The amount of vertical pixels that will be shifted.
    */
    property real offsetX: 0;
    /*!
      \qmlproperty Item InfiniteScrollEntity::offsetY
      \brief \l The amount of horizontal pixels that will be shifted
    */
    property real offsetY: 0;

    implicitWidth: target.width
    implicitHeight: target.height

    ShaderEffectSource {
        id: shaderSource
        width: target.width; height: target.height
        sourceItem: target
        hideSource: true
        visible: false
    }

    ShaderEffect {
        id:shader
        width: target.width; height: target.height

        property real shaderXStep: target ? offsetX / target.height : 0
        property real shaderYStep: target ? offsetY / target.width : 0

        property Item target: shaderSource

        blending: false
        vertexShader: "
            uniform highp mat4 qt_Matrix;
            attribute highp vec4 qt_Vertex;
            attribute highp vec2 qt_MultiTexCoord0;
            varying highp vec2 coord;
            void main() {
                coord = qt_MultiTexCoord0;
                gl_Position = qt_Matrix * qt_Vertex;
            }"
        fragmentShader: "
            uniform float width;
            uniform lowp float qt_Opacity;
            uniform sampler2D target;
            uniform float shaderXStep;
            uniform float shaderYStep;
            varying  highp vec2 coord;
            void main(void) {
                vec4 texel = texture2D(target, vec2(mod(coord.x + shaderXStep, 1.0), mod(coord.y + shaderYStep, 1.0)));
                gl_FragColor = texel  * qt_Opacity;
            } "
    }
}
