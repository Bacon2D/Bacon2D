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
                drawType: Quasi.PlaneDrawType

                layers: [
                    StaticLayer {
                        source: "not_so_large.png" // image source
                        factor: 1.0
                        order: Quasi.BackgroundLayerOrdering_01
                    },
                    StaticLayer {
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






