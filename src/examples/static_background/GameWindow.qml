import QtQuick 2.0
import QuasiGame 1.0

QuasiGame {
    id: game

    width: 800
    height: 400

    currentScene: scene

    fps: 300

    GameScene {
        id: scene

        width: parent.width
        height: parent.height

        gameItems: [
            StaticBackground {
                id: backgroundItem

                anchors.fill: parent

                source: "not_so_large.png" // image source
            },
            SpriteItem {
                id: spriteItem

                y: 175

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
        ]
    }
}
