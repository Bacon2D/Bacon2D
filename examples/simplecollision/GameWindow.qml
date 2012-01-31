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

                property string name: "RED"

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

                onCollidedChanged: {
                    if (collided) {
                        console.log("red collided with:")
                        var collidedList = item.collidedItems()
                        console.log(collidedList)
                        for (var i=0; i< collidedList.length; ++i) {
                            var gameItem = collidedList[i]
                            console.log(gameItem)
                            console.log(gameItem.name)
                        }
                    }
                }
            },
            GameItem {
                id: item2

                property string name: "BLUE"

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
            },
            GameItem {
                id: item3

                property string name: "YELLOW"

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
            },
            GameItem {
                id: item4

                property string name: "GRAY"

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

                    color: item4.collided ? "green" : "gray"
                }
            }
        ]
    }
}
