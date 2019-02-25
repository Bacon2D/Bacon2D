import QtQuick 2.4
import Bacon2D 1.0

PhysicsEntity {
    id: coin

    property bool picked: false

    EntityManager { id: entityManager }

    width: 100
    height: 62
    sleepingAllowed: false
    bodyType: Body.Static
    transformOrigin: Item.Center


    fixtures: Box {
        width: target.width
        height: target.height
        sensor: true
        collidesWith: Box.Category1

        onBeginContact: picked = true;
    }

    AnimatedSprite {
        animation: "spin"
        width: 30
        height: 30
        spriteSheet: SpriteSheet {
            source: "images/coin.png"
            horizontalFrameCount: 10
            verticalFrameCount: 1
        }

        animations: SpriteAnimation {
            name: "spin"
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

        ScriptAction { script: entityManager.destroyEntity(coin.entityId); }
    }
}

