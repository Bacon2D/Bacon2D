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

        gameItems: GameItem {
            id: item

            width: parent.width
            height: parent.height

            updateInterval: 50

            updateScript: {
                var newPos = item.x + 5
                item.x = newPos > parent.width ? 0 : newPos

                console.log("update: x -> ", item.x)
            }

            Rectangle {
                width: 50
                height: 50

                color: "red"
            }
        }
    }
}
