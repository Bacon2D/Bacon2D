import QtQuick 2.0
import Bacon2D 1.0

Entity {
    width: parent.width
    height: parent.height
    entityType: Bacon2D.DynamicType
    sleepingAllowed: false

    Fixture {
        material: Material {
            friction: 0.3
            density: 50
            restitution: 0.35
        }
        shape: Box {
            anchors.fill: parent
        }
    }
    Image {
        source: "qrc:/images/wood.jpg"
        anchors.fill: parent
    }

}
