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
            QuasiLayers {
                anchors.fill: parent
                drawType: Quasi.TiledDrawType
                tileWidth: 32
                tileHeight: 32
                //drawGrid: true // nice for debug; default: false
                gridColor: "green" // nice for debug; default: red

                layers: [
                    QuasiAnimatedLayer {
                        source: "large_enough.png" // image source
                        factor: 1.0
                        order: Quasi.BackgroundLayerOrdering_01

                        horizontalStep: 5 // base horizontal offset, aka 'step'; there are no need of a signed value as it will always get the positive value
                        direction: Quasi.BackwardDirection // direction of the background animation; Forward or Backward
                        type: Quasi.InfiniteType // type of animation; Infinite or Mirrored
                    },
                    QuasiStaticLayer {
                        source: "not_so_large2.png"
                        factor: 1.0
                        order: Quasi.ForegroundLayerOrdering_01
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
