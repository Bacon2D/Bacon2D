import QtQuick 2.0
import QuasiGame 1.0

QuasiGame {
    id: game

    width: 800
    height: 400
    //height: 500

    currentScene: scene

    fps: 300

    GameScene {
        id: scene

        width: parent.width
        height: parent.height

        gameItems: [
            AnimatedBackground {
                id: backgroundItem

                anchors.fill: parent

                source: "large_enough.png" // image source
                updateInterval: 10 // time between updates; miliseconds
                horizontalOffset: 10 // base horizontal offset, aka 'step'; there are no need of a signed value
                direction: GameAnimatedBackground.Backward // direction of the background animation; Forward or Backward
                type: GameAnimatedBackground.Infinite // type of animation; Infinite or Mirrored

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
