import QtQuick 2.2
import Bacon2D 1.0

Game {
    id: game
    width: 800
    height: 600
    focus: true
    currentScene: scene

    Scene {
        id: scene
        anchors.fill: parent
        physics: true

        Wall {
            id: ground
            height: 20
            anchors { left: parent.left; right: parent.right; top: parent.bottom }
        }
        Wall {
            id: ceiling
            height: 20
            anchors { left: parent.left; right: parent.right; bottom: parent.top }
        }
        Wall {
            id: leftWall
            width: 20
            anchors { right: parent.left; bottom: ground.top; top: ceiling.bottom }
        }
        Wall {
            id: rightWall
            width: 20
            anchors { left: parent.right; bottom: ground.top; top: ceiling.bottom }
        }

        Ball {
            id: ball
            x: parent.width /2
            y: parent.height /2
            rotation: 0
            width: 100
            height: 100
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                ball.applyLinearImpulse(
                            Qt.point((mouseX - ball.x),
                                     (mouseY - ball.y)),
                            Qt.point(ball.x, ball.y))
            }
        }

        Rectangle {
            id: debugButton
            x: 50
            y: 10
            width: 120
            height: 30
            Text {
                id: debugButtonText
                text: scene.debug ? "Debug view: on" : "Debug view: off"
                anchors.centerIn: parent
            }
            color: "#DEDEDE"
            border.color: "#999"
            radius: 5
            MouseArea {
                anchors.fill: parent
                onClicked: scene.debug = !scene.debug
            }
        }
    }
}

