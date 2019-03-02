import QtQuick 2.0
import Bacon2D 1.0

PhysicsEntity {
    entityType: "levelBoundaries"

    fixtures: Chain {
        density: 1
        restitution: 1
        friction: 1
    }
}
