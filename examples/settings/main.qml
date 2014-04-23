import QtQuick 2.2
import Bacon2D 1.0
import QtQuick.Controls 1.1

Game {
    id: game
    width: 800
    height: 600
    focus: true
    currentScene: scene
    gameName: "some.example.game"

    Settings {
        id: settings
        property int highScore: 0
        property bool noSound: false
    }

    Scene {
        id: scene
        anchors.fill: parent

        Column {
            anchors.fill: parent
            Text {
                id: disp
                text: settings.highScore
            }

            SpinBox {
                width: 200
                value: settings.highScore
                onValueChanged: settings.highScore = value
            }
        }
    }
}
