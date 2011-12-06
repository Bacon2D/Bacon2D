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

        gameItems: SpriteItem {
            width: 230
            height: 230

            sprite.sprites: Sprite {
                name: "default"
                frames: 4
                duration: 60

                source: "sprite.png"
            }
        }
    }
}
