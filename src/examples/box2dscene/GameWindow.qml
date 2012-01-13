import QtQuick 2.0
import QuasiGame 1.0

QuasiGame {
    id: game

    width: 800
    height: 600

    currentScene: scene

    Box2DScene {
        id: scene

        anchors.fill: parent

        gameItems: [
            Box2DItem {
                id: mouseItem

                width: 60
                height: 60

                friction: 0.3
                density: 50
                restitution: 0.6
                sleepingAllowed: false

                Rectangle {
                    color: "green"
                    anchors.fill: parent
                }

                x: 200
                y: 160
            },
            Box2DItem {
                id: box2ditem1

                width: 50
                height: 50

                friction: 0.3
                density: 50
                restitution: 0.6
                sleepingAllowed: false

                Rectangle {
                    color: "red"
                    anchors.fill: parent
                }

                x: 250
                y: 0
            },
            Box2DDistanceJointItem {
                box2ditemA: mouseItem
                box2ditemB: box2ditem1
            },
            Box2DItem {
                id: box2ditem2

                width: 100
                height: 100

                friction: 0.3
                density: 50
                restitution: 0.6
                sleepingAllowed: false

                Rectangle {
                    color: "blue"
                    anchors.fill: parent
                }

                x: 400
                y: 300
            },
            Box2DMouseJointItem {
                target: mouseItem
            },
            Box2DItem {
                id: ground

                bodyType: Box2DItem.Static

                width: 790
                height: 1

                friction: 0.3
                density: 5
                restitution: 0.6

                Rectangle {
                    color: "green"
                    anchors.fill: parent
                }

                x: 0
                y: 500
            },
            Box2DItem {
                bodyType: Box2DItem.Static

                width: 10
                height: 10

                Rectangle {
                    color: "black"
                    anchors.fill: parent
                }

                x: 0
                y: 0
            },
            Box2DItem {
                bodyType: Box2DItem.Static

                width: 10
                height: 10

                Rectangle {
                    color: "black"
                    anchors.fill: parent
                }

                x: 790
                y: 0
            },
            Box2DItem {
                bodyType: Box2DItem.Static

                width: 10
                height: 10

                Rectangle {
                    color: "black"
                    anchors.fill: parent
                }

                x: 0
                y: 590
            },
            Box2DItem {
                bodyType: Box2DItem.Static

                width: 10
                height: 10

                Rectangle {
                    color: "black"
                    anchors.fill: parent
                }

                x: 790
                y: 590
            }
        ]
    }

   /* MouseArea {
        anchors.fill: parent
        onClicked: {
            box2ditem2.applyLinearImpulse(
            Qt.point(100 * (mouseX - box2ditem2.x),
            100 * (mouseY - box2ditem2.y)),
            Qt.point(box2ditem2.x, box2ditem2.y))
        }
    }*/

}
