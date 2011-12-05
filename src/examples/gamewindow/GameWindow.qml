import QtQuick 2.0
import QuasiGame 1.0

QuasiGame {
    id: game

    width: 400
    height: 250

    onUpdate: console.log("update", delta)

    Component.onCompleted: {
        console.log("fps", game.fps)
    }
}
