import QtQuick 2.0
import QuasiGame 1.0

QuasiGame {
    id: game

    width: 800
    height: 400
    //height: 500

    currentScene: scene

    fps: 300

    QuasiScene {
        id: scene

        width: parent.width
        height: parent.height

        entities: [
            AnimatedBackground {
                id: backgroundItem

                anchors.fill: parent

                source: "large_enough.png" // image source
                updateInterval: 10 // time between updates; miliseconds
                horizontalOffset: 10 // base horizontal offset, aka 'step'; there are no need of a signed value
                direction: GameAnimatedBackground.Backward // direction of the background animation; Forward or Backward
                type: GameAnimatedBackground.Infinite // type of animation; Infinite or Mirrored

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
