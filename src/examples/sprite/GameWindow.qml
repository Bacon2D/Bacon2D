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

            updateInterval: 5000
            sprite.interpolate: true

            updateScript: {
                if (currentSprite == "sliding")
                    currentSprite = "jumping"
                else
                    currentSprite = "sliding"
            }

            sprites: [
                Sprite {
                    name: "sliding"
                    frames: 4
                    duration: 60

                    source: "sliding.png"
                },
                Sprite {
                    name: "jumping"
                    frames: 10
                    duration: 60

                    source: "jumping.png"
                }
            ]
        }
    }
}
