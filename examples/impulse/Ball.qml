import QtQuick 2.2
import Bacon2D 1.0

Entity {
    fixedRotation: false
    sleepingAllowed: false
    bodyType: Entity.Dynamic
    fixtures: Circle {
        id: circleShape
        radius: parent.width / 2
        anchors.fill: parent
        density: 1;
        friction: 1;
        restitution: 0.5;
    }
    
    Rectangle {
        id: itemShape
        color: "green"
        radius: parent.width / 2
        width: parent.width
        height: parent.height
    }
}
