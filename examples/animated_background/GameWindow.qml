import QtQuick 2.0
import QuasiGame 1.0

QuasiGame {
    id: game

    width: 800
    height: 400

    currentScene: scene

    fps: 300

    QuasiScene {
        id: scene

        width: parent.width
        height: parent.height

        entities: [
            GameLayers {
                anchors.fill: parent
                tiled: true
                tileWidth: 32
                tileHeight: 32
                //drawGrid: true // good for debug; default: false
                gridColor: "green" // good for debug; default: red

                layers: [
                    AnimatedLayer {
                        source: "large_enough.png" // image source
                        factor: 1.0
                        order: 1

                        horizontalStep: 5 // base horizontal offset, aka 'step'; there are no need of a signed value
                        direction: AnimatedLayer.Backward // direction of the background animation; Forward or Backward
                        type: AnimatedLayer.Infinite // type of animation; Infinite or Mirrored
                    },
                    StaticLayer {
                        source: "not_so_large2.png"
                        factor: 1.0
                        order: 2
                    }
                ]
            },
            QuasiSprite {
                id: spriteItem

                y: 175

                animation: "sliding"

                animations: QuasiAnimation {
                    name: "sliding"

                    source: "sliding.png"
                    frames: 4
                    duration: 450
                    loops: Animation.Infinite
                }
            }
        ]
    }
}
