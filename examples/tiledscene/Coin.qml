import QtQuick 2.4
import Bacon2D 1.0

PhysicsEntity {
    id: coin
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

        onBeginContact: picked = true;
    }

    AnimatedSprite {
        animation: "spin"
        width: parent.width
        height: parent.height
        source: "images/coin.png"

        animations: SpriteAnimation {
            name: "spin"
            frames: 10
            duration: 1000
            loops: Animation.Infinite
        }
    }

    SequentialAnimation {
        running: coin.picked

        ParallelAnimation {
            NumberAnimation { target: coin; property: "scale"; to: 6 }
            NumberAnimation { target: coin; property: "opacity"; to: 0 }
        }

        ScriptAction { script: coin.destroy(); }
    }
}

