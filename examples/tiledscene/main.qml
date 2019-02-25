import QtQuick 2.4
import QtQuick.Window 2.2
import Bacon2D 1.0

Window {
    id: mainWindow
    width: 800
    height: 600
    visible: true

    Game {
        id: gameWindow
        anchors.fill: parent
        currentScene: scene

        TiledScene {
            id: scene
            physics: true
            source: "levels/example.tmx"
            viewport: Viewport {
                yOffset: scene.height - gameWindow.height
                width: gameWindow.width
                height: gameWindow.height
            }

            layers: [
                TiledLayer {
                    name: "Player"

                    TiledObject {
                        id: player
                        entity: Dog { }

                        TiledPropertyMapping { property: "x" }
                        TiledPropertyMapping { property: "y" }
                    }
                },

                TiledLayer {
                    name: "Ground"

                    TiledObject {
                        entity: Ground { }

                        TiledPropertyMapping { property: "x" }
                        TiledPropertyMapping { property: "y" }
                        TiledPropertyMapping { property: "width" }
                        TiledPropertyMapping { property: "height" }
                    }

                    TiledObject {
                        name: "polyground"

                        entity: Polyground { }

                        TiledPropertyMapping { property: "x" }
                        TiledPropertyMapping { property: "y" }
                    }
                },

                TiledLayer {
                    name: "Coins"

                    TiledObject {
                        entity: Coin { }

                        TiledPropertyMapping { property: "x" }
                        TiledPropertyMapping { property: "y" }
                        TiledPropertyMapping { property: "width" }
                        TiledPropertyMapping { property: "height" }
                    }
                },

                TiledLayer {
                    name: "Boundaries"

                    TiledObject {
                        entity: LevelBoundaries { }

                        TiledPropertyMapping { property: "x" }
                        TiledPropertyMapping { property: "y" }
                    }
                }
            ]

            // Key handling
            Keys.onPressed: {
                if (!event.isAutoRepeat) {
                    switch (event.key) {
                    case Qt.Key_Left:
                        player.getEntity().handleEvent("left", "press");
                        break;
                    case Qt.Key_Right:
                        player.getEntity().handleEvent("right", "press");
                        break;
                    case Qt.Key_Up:
                        player.getEntity().handleEvent("up", "press");
                        break;
                    }
                }

                event.accepted = true;
            }

            Keys.onReleased: {
                if (!event.isAutoRepeat) {
                    switch (event.key) {
                    case Qt.Key_Left:
                        player.getEntity().handleEvent("left", "release");
                        break;
                    case Qt.Key_Right:
                        player.getEntity().handleEvent("right", "release");
                        break;
                    case Qt.Key_Up:
                        player.getEntity().handleEvent("up", "release");
                        break;
                    }
                }

                event.accepted = true;
            }
        }
    }
}
