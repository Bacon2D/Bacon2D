import QtQuick 2.0
import QuasiGame 1.0

GameItem {
    id: backgroundItem

    objectName: "background"

    property alias source: staticBackground.source

    property int horizontalOffset: 0

    GameStaticBackground {
        id: staticBackground

        width: parent.width
        height: parent.height
    }
}
