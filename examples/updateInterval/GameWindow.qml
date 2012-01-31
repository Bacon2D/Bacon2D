import QtQuick 2.0
import QuasiGame 1.0

QuasiGame {
    id: game

    width: 400
    height: 250

    currentScene: scene


    GameScene {
        id: scene

        gameItems: GameItem {
            updateInterval: 1000

            updateScript: {
                console.log("update")
            }

            Rectangle {
                width: 50
                height: 50

                color: "red"
            }
        }
    }
}
