import QtQuick 2.0
import Bacon2D 1.0

Entity {
    width: enemy1.width
    height: enemy1.height
    entityType: Bacon2D.DynamicType
    sleepingAllowed: false

    Fixture {
        material: Material {
            friction: 0.3
            density: 50
            restitution: 0.35
        }
        shape: Circle {
            anchors.fill: parent
        }
    }

    Image {
        id: enemy1
        source: "qrc:/images/enemy.png"
    }
}
