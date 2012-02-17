import QtQuick 2.0
import QuasiGame 1.0

QuasiGame {
    id: game

    width: 400
    height: 250

    currentScene: scene

    fps: 300

    QuasiScene {
        id: scene

        width: parent.width
        height: parent.height

        entities: QuasiSprite {
            id: spriteItem


            animation: "sliding"

            animations: [
                QuasiAnimation {
                    name: "sliding"

                    source: "sliding.png"
                    frames: 4
                    duration: 400
                    loops: Animation.Infinite
                },
                QuasiAnimation {
                    name: "jumping"

                    source: "jumping.png"
                    frames: 10
                    duration: 600
                    loops: 2

                    onFinished: {
                        spriteItem.animation = "sliding"
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
