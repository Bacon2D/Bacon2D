import QtQuick 2.0
import Bacon2D 1.0

PhysicsEntity {
    bodyType: Body.Static
    fixtures: Box { 
        density: 10
        restitution: 0.1
    }
}
