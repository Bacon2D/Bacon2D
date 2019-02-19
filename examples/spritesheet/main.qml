import QtQuick 2.9
import QtQuick.Controls 2.2
import Bacon2D 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 640
    title: qsTr("Bacon2D - Spritesheet")

    Game {
        id: game
        anchors.fill: parent
        currentScene: scene

        Scene {
            id: scene

            width: parent.width
            height: parent.height
            focus: true

            property int currentIndex: 0

            Keys.onPressed: {
                switch(event.key) {
                case Qt.Key_Left:
                    if (currentIndex > 0) {
                        --currentIndex;
                        sprite.animation = sprite.animations[currentIndex].name;
                    }
                    break;
                case Qt.Key_Right:
                    if (currentIndex < sprite.spriteSheet.verticalFrameCount - 1) {
                        ++currentIndex;
                        sprite.animation = sprite.animations[currentIndex].name;
                    }
                    break;
                case Qt.Key_Space:
                    sprite.horizontalMirror = !sprite.horizontalMirror;
                    break;
                }
            }

            Text {
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 40
                color: "crimson"
                text: sprite.animation
            }

            AnimatedSprite {
                id: sprite
                anchors.centerIn: parent
                animation: "run"
                spriteSheet: SpriteSheet {
                    id: spriteSheet
                    source: "images/sprite.png"
                    horizontalFrameCount: 10
                    verticalFrameCount: 3
                }

                animations: [
                    SpriteAnimation {
                        name: "idle"
                        duration: 500
                        loops: Animation.Infinite
                    },

                    SpriteAnimation {
                        name: "run"
                        duration: 500
                        loops: Animation.Infinite
                        spriteStrip: SpriteStrip {
                            finalFrame: 7
                            frameY: 2 * frameHeight
                        }
                    },

                    SpriteAnimation {
                        name: "jump"
                        duration: 1000
                        loops: Animation.Infinite
                        spriteStrip: SpriteStrip {
                            frameY: frameHeight
                            finalFrame: 7
                        }
                    }
                ]
            }
        }
    }
}
