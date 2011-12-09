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

        gameItems: [
            GameItem {
                id: item

                width: rect.width
                height: rect.height
                x: 0

                updateInterval: 10

                updateScript: {
                    var newPos = item.x + 2
                    item.x = newPos > parent.width ? 0 : newPos
                }

                Rectangle {
                    id: rect
                    width: 50
                    height: 50

                    color: item.collided ? "green" : "red"
                }

                //onCollidedChanged: if (collided) console.log("red collided")
            },
            GameItem {
                id: item2

                width: rect2.width
                height: rect2.height
                x: parent.width

                updateInterval: 10

                updateScript: {
                    var newPos = item2.x - 2
                    item2.x = newPos < 0 ? parent.width : newPos
                }

                Rectangle {
                    id: rect2
                    width: 50
                    height: 50

                    color: item2.collided ? "green" : "blue"
                }

                //onCollidedChanged: if (collided) console.log("blue collided")
            },
            GameItem {
                id: item3

                width: rect3.width
                height: rect3.height
                x: parent.width / 2
                y: 0

                updateInterval: 10

                updateScript: {
                    var newPos = item3.y + 2
                    item3.y = newPos > parent.height ? 0 : newPos
                }

                Rectangle {
                    id: rect3
                    width: 50
                    height: 50

                    color: item3.collided ? "green" : "yellow"
                }

                //onCollidedChanged: if (collided) console.log("yellow collided")
            },
            GameItem {
                id: item4

                width: rect4.width
                height: rect4.height
                x: parent.width / 2
                y: parent.height

                updateInterval: 10

                updateScript: {
                    var newPos = item4.y - 2
                    item4.y = newPos < 0 ? parent.height : newPos
                }

                Rectangle {
                    id: rect4
                    width: 50
                    height: 50

                    color: item3.collided ? "green" : "gray"
                }

                //onCollidedChanged: if (collided) console.log("gray collided")
            }
        ]
    }
}
