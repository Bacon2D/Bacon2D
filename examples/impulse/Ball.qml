import QtQuick 2.2
import Bacon2D 1.0

PhysicsEntity {
    id: ent
    bodyType: Body.Dynamic
    fixedRotation: false

    fixtures: Circle {
        id: circle
        radius: ent.width / 2
        density: 1
        friction: 0
        restitution: 0.5
    }
    Rectangle {
        anchors.fill: parent
        color: "green"
        radius: circle.radius
    }
}
