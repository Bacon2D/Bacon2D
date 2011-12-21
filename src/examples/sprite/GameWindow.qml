import QtQuick 2.0
import QuasiGame 1.0

QuasiGame {
    id: game

    width: 400
    height: 250

    currentScene: scene

    fps: 300


    GameScene {
        id: scene

        width: parent.width
        height: parent.height

        gameItems: SpriteItem {
            id: spriteItem


            animation: "sliding"

            animations: [
                SpriteAnimationItem {
                    name: "sliding"

                    sprite: GameSprite {
                        source: "sliding.png"
                        frames: 4
                    }

                    spriteAnimation: SpriteAnimation {
                        duration: 450
                        loops: Animation.Infinite
                    }
                },
                SpriteAnimationItem {
                    name: "jumping"

                    sprite: GameSprite {

                        source: "jumping.png"
                        frames: 10
                    }

                    spriteAnimation: SpriteAnimation {
                        id: jumpingAnimation

                        duration: 600
                        loops: 2

                        onFinished: {
                            spriteItem.animation = "sliding"
                        }
                    }
                }
            ]
        }
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            spriteItem.animation = spriteItem.animation == "sliding" ? "jumping"
                                                                     : "sliding"
        }
    }
}
