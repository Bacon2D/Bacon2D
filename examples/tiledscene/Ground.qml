import QtQuick 2.0
import Bacon2D 1.0

PhysicsEntity {
    entityType: "ground"

    fixtures: Box {
        density: 1
        restitution: 0
        friction: 1
    }
}
