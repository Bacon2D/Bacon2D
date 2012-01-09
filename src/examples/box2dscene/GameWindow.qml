import QtQuick 2.0
import QuasiGame 1.0
import Box2D 1.0

QuasiGame {
    id: game

    width: 400
    height: 250

    currentScene: scene

    Box2DScene {
        id: scene

        anchors.fill: parent

        gameItems: Box2DItem {
            id: box2ditem

            width: 50
            height: 50

            Rectangle {
                color: "red"
                anchors.fill: parent
            }
        }
    }
}
