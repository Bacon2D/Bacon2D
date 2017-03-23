import QtQuick 2.4
import Bacon2D 1.0

PhysicsEntity {
    id: root
    width: 100
    height: 62
    sleepingAllowed: false
    bodyType: Body.Static
    transformOrigin: Item.Center

    property bool picked: false

    fixtures: Box {
        width: target.width
        height: target.height
        sensor: true
        collidesWith: Box.Category1

        onBeginContact: {
            if(!picked) {
                root.opacity = 0
                scale = 4
                picked = true
            }
        }
    }

    Sprite {
        animation: "spin"
        width: parent.width
        height: parent.height
        animations: SpriteAnimation {
            name: "spin"
            source: "images/coin.png"
            frames: 10
            duration: 1000
            loops: Animation.Infinite
        }
    }

    onOpacityChanged: {
        if(opacity == 0)
            destroy()
    }

    Behavior on opacity { NumberAnimation {} }
    Behavior on scale { NumberAnimation {} }
}

