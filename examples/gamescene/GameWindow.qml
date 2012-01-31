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
            updateScript: {
                console.log("update")
            }
        }
    }
}
