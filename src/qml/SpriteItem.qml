import QtQuick 2.0
import QtQuick 2.0
import QuasiGame 1.0

GameItem {
    id: spriteItem

    property alias sprite: spriteImage

    SpriteImage {
        id: spriteImage

        anchors.fill: parent
    }
}
