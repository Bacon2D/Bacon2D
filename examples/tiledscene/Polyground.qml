import QtQuick 2.0
import Bacon2D 1.0

PhysicsEntity {
    entityType: "polyground"

    fixtures: Polygon {
        density: 1
        restitution: 0
        friction: 1
    }
}
