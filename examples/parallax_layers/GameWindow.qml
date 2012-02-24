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
                // TODO: make 'horizontalStep' a property from QuasiLayers, not QuasiAnimatedLayer?
                anchors.fill: parent
                drawType: Quasi.TiledDrawType // XXX: There are some problems with Quasi.PLaneDrawType
                tileWidth: 40
                tileHeight: 40

                layers: [
                    QuasiAnimatedLayer {
                        source: "images/space.png"
                        factor: 0.3
                        order: Quasi.BackgroundLayerOrdering_01

                        horizontalStep: 1
                        type: Quasi.MirroredType
                    },
                    QuasiAnimatedLayer {
                        source: "images/planet.png"
                        factor: 0.5
                        order: Quasi.BackgroundLayerOrdering_02

                        horizontalStep: 1
                        type: Quasi.InfiniteType
                    },
                    QuasiAnimatedLayer {
                        source: "images/stars.png"
                        factor: 1.1
                        order: Quasi.ForegroundLayerOrdering_01

                        horizontalStep: 1
                        type: Quasi.InfiniteType
                    },
                    QuasiAnimatedLayer {
                        source: "images/moon.png"
                        factor: 1.2
                        order: Quasi.ForegroundLayerOrdering_02

                        horizontalStep: 1
                        type: Quasi.InfiniteType
                    }
                ]
            },
            QuasiEntity {
                id: ship

                y: (game.height / 2) - (shipImage.height / 2)
                x: 25
                /* layer ordering, set how the layers will be presented when rendering
                 * possible values, splited in three main areas:
                 * - These enums defines the ordering of the game entities
                      EntityOrdering_01 (default), EntityOrdering_02 and EntityOrdering_03
                 * Please, bear in mind that you can use as many entities you want to (and that your system can support), but they will be ordered according these values
                 * Prefer to keep colliding items on the same ordering
                 */
                order: Quasi.EntityOrdering_01

                Image {
                    id: shipImage

                    source: "images/rocketship.png"
                }

                focus: true
                Keys.onPressed: {
                    switch (event.key) {
                        case Qt.Key_Left:
                            ship.x -= 5;
                            break;
                        case Qt.Key_Right:
                            ship.x += 5;
                            break;
                        case Qt.Key_Down:
                            ship.y += 5;
                            break;
                        case Qt.Key_Up:
                            ship.y -= 5;
                            break;
                    }
                }
            }
        ]
    }
}
