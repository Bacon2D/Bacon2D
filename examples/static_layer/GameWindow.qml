import QtQuick 2.0
import QuasiGame 1.0

QuasiGame {
    id: game

    width: 800
    height: 385

    currentScene: scene

    fps: 300

    QuasiScene {
        id: scene

        width: parent.width
        height: parent.height

        entities: [
            QuasiLayers {
                anchors.fill: parent
                drawType: Quasi.PlaneDrawType // draiwing type; PlaneDrawType or TiledDrawType (default)

                layers: [
                    QuasiStaticLayer {
                        source: "not_so_large.png" // image source
                        //factor: 1.0 // updating factor of this layer, useful when using multiple layers; default: 1.0
                        /* layer ordering, set how the layers will be presented when rendering
                         * possible values, splited in three main areas:
                         * - These enums defines the ordering of the background layers
                         *    BackgroundLayerOrdering_01, BackgroundLayerOrdering_02 and BackgroundLayerOrdering_03
                         * - These enums defines the ordering of the interaction layers (where the characters, enemies, objects, etc, live)
                         *    InteractionLayerOrdering_01 (default for every layer), InteractionLayerOrdering_02 and InteractionLayerOrdering_03
                         * - These enums defines the orderin of the foreground layers
                         *    ForegroundLayerOrdering_01, ForegroundLayerOrdering_02 and ForegroundLayerOrdering_03
                         * Please, bear in mind that you can use as many layers you want to (and that your system can support), but they will ordered according these values
                         */
                        order: Quasi.BackgroundLayerOrdering_01
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






