import QtQuick 2.4
import Bacon2D 1.0

PhysicsEntity {
    id: root
    sleepingAllowed: false
    width: 100
    height: 75
    bodyType: Body.Dynamic
    fixedRotation: true

    readonly property Scene scene: parent
    property bool facingLeft: false
    property bool airborne: false
    property bool running: false
    property bool jumping: false
    readonly property int groundSensorRoom: -7
    property int xStep: 10

    fixtures: [
        Box {
            x: 15
            width: target.width - 40
            height: target.height - groundSensorRoom
            density: .3
            restitution: 0
            friction: .7
            categories: Box.Category1
        },

        // ground sensor
        Box {
            sensor: true
            x: 30
            y: target.height - groundSensorRoom
            width: 30
            height: 2

            onBeginContact: {
                root.airborne = false
                sprite.animation = "idle"
            }

            onEndContact: {
                root.airborne = true
            }
        }

    ]

    Sprite {
        id: sprite
        animation: "idle"
        horizontalMirror: root.facingLeft

        animations: [
            SpriteAnimation {
                name: "idle"
                source: "images/dog_idle.png"
                frames: 10
                duration: 500
                loops: Animation.Infinite
            },

            SpriteAnimation {
                name: "run"
                source: "images/dog_run.png"
                frames: 8
                duration: 500
                loops: Animation.Infinite
                inverse: root.facingLeft
            },

            SpriteAnimation {
                name: "jump"
                source: "images/dog_jump.png"
                frames: 8
                duration: 1000
                loops: 1

                onFinished: {
                    root.jumping = false

                    if(root.airborne && sprite.animation == name)
                        sprite.animation = "freefall"
                }
            },

            SpriteAnimation {
                name: "freefall"
                source: "images/dog_freefall.png"
                frames: 2
                duration: 2000
                loops: Animation.Infinite
                inverse: root.facingLeft
            }
        ]
    }

    /*********************** TIMERS ********************************/
    Timer {
        id: rMoveLeftTimer
        interval: 50
        repeat: true
        triggeredOnStart: true

        onTriggered: root.rMoveLeft()
    }

    Timer {
        id: rMoveRightTimer
        interval: 50
        repeat: true
        triggeredOnStart: true

        onTriggered: root.rMoveRight()
    }

    /***************************************************************/

    /************************ ACTIONS *****************************/
    function moveLeft() {
        if(scene.game.gameState != Bacon2D.Running)
            return

        rMoveLeftTimer.start()
        rMoveRightTimer.stop()
        root.facingLeft = true

        if(root.airborne && sprite.animation != "jump")
            sprite.animation = "freefall"
        else
            sprite.animation = "run"
    }

    // Repeat move left
    function rMoveLeft() {
        if(scene.game.gameState != Bacon2D.Running)
            return

        root.x -= root.xStep
        root.facingLeft = true

        if(root.airborne && sprite.animation != "jump")
            sprite.animation = "freefall"
        else
            sprite.animation = "run"
    }

    function stopMovingLeft() {
        if(scene.game.gameState != Bacon2D.Running)
            return

        rMoveLeftTimer.stop()
        root.facingLeft = true

        if(root.airborne && sprite.animation != "jump")
            sprite.animation = "freefall"
        else
            sprite.animation = "idle"
    }

    function moveRight() {
        if(scene.game.gameState != Bacon2D.Running)
            return

        rMoveLeftTimer.stop()
        rMoveRightTimer.start()
        root.facingLeft = false

        if(root.airborne && sprite.animation != "jump")
            sprite.animation = "freefall"
        else
            sprite.animation = "run"
    }

    // Repeat move right
    function rMoveRight() {
        if(scene.game.gameState != Bacon2D.Running)
            return

        root.x += root.xStep
        root.facingLeft = false

        if(root.airborne && sprite.animation != "jump")
            sprite.animation = "freefall"
        else
            sprite.animation = "run"
    }

    function stopMovingRight() {
        if(scene.game.gameState != Bacon2D.Running)
            return

        rMoveRightTimer.stop()
        root.facingLeft = false

        if(root.airborne && sprite.animation != "jump")
            sprite.animation = "freefall"
        else
            sprite.animation = "idle"
    }

    function jump() {
        if(scene.game.gameState != Bacon2D.Running)
            return
        if(root.airborne)
            return

        if(sprite.animation == "idle" || sprite.animation == "run")
            sprite.animation = "jump"
        else
            return

        root.applyLinearImpulse(Qt.point(0, -root.getMass() * 10), root.getWorldCenter());
    }
    /**************** END ACTIONS ********************************/
}

