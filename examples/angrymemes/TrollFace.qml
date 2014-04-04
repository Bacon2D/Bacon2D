import QtQuick 2.0
import Bacon2D 1.0

Entity {
    width: trollface.width
    height: trollface.height
    sleepingAllowed: false
    entityType: Bacon2D.DynamicType
    bullet: true

    Fixture {
        material: Material {
            friction: 0.3
            density: 50
            restitution: 0.35
        }
        shape: Circle {
            anchors.fill: parent
        }

        Image {
            id: trollface
            source: "qrc:/images/trollface.png"
        }
    }
}
