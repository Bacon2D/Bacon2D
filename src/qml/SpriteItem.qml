import QtQuick 2.0
import QtQuick 2.0
import QuasiGame 1.0

GameItem {
    id: spriteItem

    property alias sprite: spriteImage
    property alias sprites: spriteImage.sprites
    property string currentSprite: ""

    SpriteImage {
        id: spriteImage

        anchors.fill: parent
    }

    onCurrentSpriteChanged: spriteImage.jumpTo(currentSprite)
}
