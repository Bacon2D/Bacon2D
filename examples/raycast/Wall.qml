import QtQuick 2.2
import Bacon2D 1.0

PhysicsEntity {
    bodyType: Body.Static
    signal beginContact (variant other)
    fixtures: Box {
        friction: 1
        density: 1
        onBeginContact: {
            parent.beginContact(other)
        }
    }
    Image {
        source: "images/wall.jpg"
        fillMode: Image.Tile
        anchors.fill: parent
    }
}
