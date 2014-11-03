import QtQuick 2.2
import Bacon2D 1.0

PhysicsEntity {
    bodyType: Body.Static
    fixtures: Box {
        height: target.height
        width: target.width
        friction: 1
        density: 1
    }
    Image {
        source: "images/wall.jpg"
        fillMode: Image.Tile
        anchors.fill: parent
    }
}
