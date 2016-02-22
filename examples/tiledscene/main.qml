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
            //debug: true
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
                    objects: TiledObject {
                        id: playerObject
                    }
                },

                TiledLayer {
                    name: "Ground"
                    objects: [
                        TiledObject {
                            id: groundObject

                            fixtures: Box {
                                width: groundObject.width
                                height: groundObject.height
                                density: 1
                                restitution: 0
                                friction: 1
                            }
                        },

                        TiledObject {
                            name: "polyground"

                            fixtures: Polygon {
                                density: 1
                                restitution: 0
                                friction: 1
                            }
                        }
                    ]
                },

                TiledLayer {
                    id: coinLayer
                    name: "Coins"
                    objects: TiledObject { }
                },

                TiledLayer {
                    id: boundariesLayer
                    name: "Boundaries"
                    objects: TiledObject {
                        fixtures: Chain {
                            density: 1
                            restitution: 1
                            friction: 1
                        }
                    }
                }
            ]


            Dog { id: player }

            Component {
                id: coinComponent
                Coin {}
            }

            /**************************** INPUT HANDLING ***************************/
            // Key handling
            Keys.onPressed: {
                switch(event.key) {
                case Qt.Key_Left:
                    player.moveLeft()
                    break;
                case Qt.Key_Right:
                    player.moveRight()
                    break;
                case Qt.Key_Up:
                    player.jump()
                    break
                }

                event.accepted = true
            }

            Keys.onReleased: {
                switch(event.key) {
                case Qt.Key_Left:
                    if(!event.isAutoRepeat)
                        player.stopMovingLeft();
                    break;
                case Qt.Key_Right:
                    if(!event.isAutoRepeat)
                        player.stopMovingRight();
                    break;
                }

                event.accepted = true
            }
            /*************************** END OF INPUT HANDLING ************************/

            Component.onCompleted: {
                player.x = playerObject.x;
                player.y = playerObject.y

                // Create coins
                // Loop through every "collision" of the coin object layer
                for(var i = 0; i < coinLayer.objects.length; ++i)
                {
                    var collision = coinLayer.objects[i];
                    while(collision.next())
                    {
                        var coin = coinComponent.createObject(scene);
                        coin.x = collision.x;
                        coin.y = collision.y
                        coin.width = collision.width
                        coin.height = collision.height
                    }
                }
            }
        }
    }
}
