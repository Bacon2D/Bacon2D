import QtQuick 2.0
import QuasiGame 1.0

GameItem {
    id: backgroundItem

    objectName: "background"

    property alias source: animatedBackground.source
    property alias direction: animatedBackground.direction
    property alias type: animatedBackground.type

    property int horizontalOffset: 0

   updateScript: {
       animatedBackground.horizontalOffset += horizontalOffset;
   }

    GameAnimatedBackground {
        id: animatedBackground

        width: parent.width
        height: parent.height
    }
}
