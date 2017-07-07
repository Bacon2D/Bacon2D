import QtQuick 2.4
import Bacon2D 1.0

PhysicsEntity {
    id: dog
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
                dog.airborne = false
                sprite.animation = "idle"
            }

            onEndContact: {
                dog.airborne = true
            }
        }
    ]

    Sprite {
        id: sprite
        animation: "idle"
        horizontalMirror: dog.facingLeft
        source: "images/sprite.png"

        animations: [
            SpriteAnimation {
                name: "idle"
                frames: 10
                frameHeight: sprite.sourceSize.height / 3
                duration: 500
                loops: Animation.Infinite
            },

            SpriteAnimation {
                name: "run"
                frames: 10
                finalFrame: 7
                duration: 500
                frameY: 2 * frameHeight
                frameHeight: sprite.sourceSize.height / 3
                loops: Animation.Infinite
                inverse: dog.facingLeft
            },

            SpriteAnimation {
                name: "jump"
                frames: 10
                finalFrame: 7
                frameY: frameHeight
                frameHeight: sprite.sourceSize.height / 3
                duration: 1000
                loops: 1

                onFinished: {
                    dog.jumping = false

                    if(dog.airborne && sprite.animation == name)
                        sprite.animation = "freefall"
                }
            },

            SpriteAnimation {
                name: "freefall"
                frames: 10
                initialFrame: 6
                finalFrame: 7
                frameY: frameHeight
                duration: 500
                frameHeight: sprite.sourceSize.height / 3
                loops: Animation.Infinite
                inverse: dog.facingLeft
            }
        ]
    }

    /*********************** TIMERS ********************************/
    Timer {
        id: rMoveLeftTimer
        interval: 50
        repeat: true
        triggeredOnStart: true

        onTriggered: dog.rMoveLeft()
    }

    Timer {
        id: rMoveRightTimer
        interval: 50
        repeat: true
        triggeredOnStart: true

        onTriggered: dog.rMoveRight()
    }

    /***************************************************************/

    /************************ ACTIONS *****************************/
    function moveLeft() {
        if(scene.game.gameState != Bacon2D.Running)
            return

        rMoveLeftTimer.start()
        rMoveRightTimer.stop()
        dog.facingLeft = true

        if(dog.airborne && sprite.animation != "jump")
            sprite.animation = "freefall"
        else
            sprite.animation = "run"
    }

    // Repeat move left
    function rMoveLeft() {
        if(scene.game.gameState != Bacon2D.Running)
            return

        dog.x -= dog.xStep
        dog.facingLeft = true

        if(dog.airborne && sprite.animation != "jump")
            sprite.animation = "freefall"
        else
            sprite.animation = "run"
    }

    function stopMovingLeft() {
        if(scene.game.gameState != Bacon2D.Running)
            return

        rMoveLeftTimer.stop()
        dog.facingLeft = true

        if(dog.airborne && sprite.animation != "jump")
            sprite.animation = "freefall"
        else
            sprite.animation = "idle"
    }

    function moveRight() {
        if(scene.game.gameState != Bacon2D.Running)
            return

        rMoveLeftTimer.stop()
        rMoveRightTimer.start()
        dog.facingLeft = false

        if(dog.airborne && sprite.animation != "jump")
            sprite.animation = "freefall"
        else
            sprite.animation = "run"
    }

    // Repeat move right
    function rMoveRight() {
        if(scene.game.gameState != Bacon2D.Running)
            return

        dog.x += dog.xStep
        dog.facingLeft = false

        if(dog.airborne && sprite.animation != "jump")
            sprite.animation = "freefall"
        else
            sprite.animation = "run"
    }

    function stopMovingRight() {
        if(scene.game.gameState != Bacon2D.Running)
            return

        rMoveRightTimer.stop()
        dog.facingLeft = false

        if(dog.airborne && sprite.animation != "jump")
            sprite.animation = "freefall"
        else
            sprite.animation = "idle"
    }

    function jump() {
        if(scene.game.gameState != Bacon2D.Running)
            return
        if(dog.airborne)
            return

        if(sprite.animation == "idle" || sprite.animation == "run")
            sprite.animation = "jump"
        else
            return

        dog.applyLinearImpulse(Qt.point(0, -dog.getMass() * 10), dog.getWorldCenter());
    }
    /**************** END ACTIONS ********************************/
}

