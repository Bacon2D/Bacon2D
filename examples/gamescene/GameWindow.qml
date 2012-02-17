import QtQuick 2.0
import QuasiGame 1.0

QuasiGame {
    id: game

    width: 400
    height: 250

    currentScene: scene

    QuasiScene {
        id: scene

        entities: QuasiEntity {
            updateScript: {
                console.log("update")
            }
        }
    }
}
