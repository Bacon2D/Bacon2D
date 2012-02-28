import QtQuick 2.0
import QuasiGame 1.0

QuasiGame {
    id: game

    width: 800
    height: 600

    currentScene: scene

    QuasiPhysicsScene {
        id: scene

        anchors.fill: parent

        entities: [
            QuasiBody {
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
            QuasiBody {
                id: box2ditem1

                width: 50
                height: 50

                friction: 0.3
                density: 50
                restitution: 0.6
                sleepingAllowed: false

                shape: Quasi.PolygonBodyShape // It can be RectangleBodyShape (default), PolygonBodyShape or CircleBodyShape
                // define vertices in the following format (in counter clockwise, only needed if shape == Rectangle):
                // [[x0, y0], [x1, y1], [x2, y2], ..]
                vertices: [[0, 0], [width, 0], [width / 2, height]]

                Image {
                    source: "triangle.png"
                    anchors.fill: parent
                }

                x: 250
                y: 0
            },
            QuasiDistanceJoint {
                box2ditemA: mouseItem
                box2ditemB: box2ditem1
            },
            QuasiBody {
                id: box2ditem2

                width: 100
                height: 100

                friction: 0.3
                density: 50
                restitution: 0.6
                sleepingAllowed: false

                shape: Quasi.CircleBodyShape // It can be RectangleBodyShape (default), PolygonBodyShape or CircleBodyShape

                Image {
                    source: "ball.png"
                    anchors.fill: parent
                }

                x: 400
                y: 300
            },
            QuasiMouseJoint {
                target: mouseItem
            },
            QuasiBody {
                id: ground

                bodyType: Quasi.StaticBodyType

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
            QuasiBody {
                bodyType: Quasi.StaticBodyType

                width: 10
                height: 10

                Rectangle {
                    color: "black"
                    anchors.fill: parent
                }

                x: 0
                y: 0
            },
            QuasiBody {
                bodyType: Quasi.StaticBodyType

                width: 10
                height: 10

                Rectangle {
                    color: "black"
                    anchors.fill: parent
                }

                x: 790
                y: 0
            },
            QuasiBody {
                bodyType: Quasi.StaticBodyType

                width: 10
                height: 10

                Rectangle {
                    color: "black"
                    anchors.fill: parent
                }

                x: 0
                y: 590
            },
            QuasiBody {
                bodyType: Quasi.StaticBodyType

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
