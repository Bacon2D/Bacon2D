import QtQuick 2.4
import Bacon2D 1.0
import QtQml.StateMachine 1.0 as DSM

PhysicsEntity {
    id: dog

    readonly property Scene scene: parent
    readonly property bool facingLeft: !sprite.horizontalMirror
    readonly property int groundSensorRoom: -7
    readonly property int xStep: 10
    property bool airborne: false

    function handleEvent(name, type) {
        if(scene.game.gameState === Bacon2D.Paused)
            return;

        switch (name) {
        case "left":
            actions.goLeft(type);
            break;
        case "right":
            actions.goRight(type);
            break;
        case "up":
            actions.goUp(type);
            break;
        }
    }

    sleepingAllowed: false
    width: 80
    height: 64
    bodyType: Body.Dynamic
    fixedRotation: true

    fixtures: [
        Box {
            x: 15
            width: target.width - 40
            height: target.height - groundSensorRoom
            density: .01
            restitution: .1
            friction: .01
            categories: Box.Category1
        },

        // ground sensor
        Box {
            sensor: true
            x: target.width / 2 - width / 2
            y: target.height - groundSensorRoom
            width: 30
            height: 2

            onBeginContact: dog.airborne = false;
            onEndContact: dog.airborne = true;
        }
    ]

    AnimatedSprite {
        id: sprite
        animation: "idle"
        anchors.centerIn: parent
        spriteSheet: SpriteSheet {
            source: "images/sprite.png"
            horizontalFrameCount: 10
            verticalFrameCount: 3
        }

        animations: [
            SpriteAnimation {
                name: "idle"
                duration: 500
                loops: Animation.Infinite
            },

            SpriteAnimation {
                name: "run"
                duration: 500
                loops: Animation.Infinite
                spriteStrip: SpriteStrip {
                    finalFrame: 7
                    frameY: 2 * frameHeight
                }
            },

            SpriteAnimation {
                name: "jump"
                duration: 1000
                loops: 1
                spriteStrip: SpriteStrip {
                    frameY: frameHeight
                    finalFrame: 7
                }

                onFinished: {
                    if(dog.airborne && sprite.animation == name)
                        sprite.animation = "freefall"
                }
            },

            SpriteAnimation {
                name: "freefall"
                duration: 500
                loops: Animation.Infinite
                spriteStrip: SpriteStrip {
                    frameY: frameHeight
                    initialFrame: 6
                    finalFrame: 7
                }
            }
        ]
    }

    Item {
        id: actions

        property QtObject keys: QtObject {
            property bool upPressed: false
            property bool leftPressed: false
            property bool rightPressed: false
        }

        signal goLeft(string eventType)
        signal goRight(string eventType)
        signal goUp(string eventType)

        Connections {
            onGoLeft: {
                actions.keys.leftPressed = eventType === "press";
                if (eventType === "press")
                    sprite.horizontalMirror = true;
            }
            onGoRight: {
                actions.keys.rightPressed = eventType === "press";
                if (eventType === "press")
                    sprite.horizontalMirror = false;
            }
            onGoUp: actions.keys.upPressed = eventType === "press";
        }
    }

    DSM.StateMachine {
        id: stateMachine
        running: true
        childMode: DSM.State.ParallelStates

        DSM.State {
            id: directionState
            initialState: actions.keys.leftPressed ? leftDirectionState
                                                     : actions.keys.rightPressed ? rightDirectionState
                                                                                   : noDirectionState

            DSM.State {
                id: leftDirectionState
                onEntered: dog.linearVelocity.x = -dog.xStep;

                DSM.SignalTransition {
                    targetState: rightDirectionState
                    signal: actions.goRight
                    guard: eventType === "press"
                }

                DSM.SignalTransition {
                    targetState: noDirectionState
                    signal: actions.goLeft
                    guard: eventType === "release"
                }
            }

            DSM.State {
                id: rightDirectionState
                onEntered: dog.linearVelocity.x = dog.xStep;

                DSM.SignalTransition {
                    targetState: leftDirectionState
                    signal: actions.goLeft
                    guard: eventType === "press"
                }

                DSM.SignalTransition {
                    targetState: noDirectionState
                    signal: actions.goRight
                    guard: eventType === "release"
                }
            }

            DSM.State {
                id: noDirectionState
                onEntered: dog.linearVelocity.x = 0;

                DSM.SignalTransition {
                    targetState: leftDirectionState
                    signal: actions.goLeft
                    guard: eventType === "press"
                }

                DSM.SignalTransition {
                    targetState: rightDirectionState
                    signal: actions.goRight
                    guard: eventType === "press"
                }
            }
        }

        DSM.State {
            id: spriteState
            initialState: !dog.airborne ? idleState : freefallState

            DSM.State {
                id: idleState

                onEntered: {
                    console.log("IDLE");
                    sprite.animation = "idle";
                }

                DSM.SignalTransition {
                    targetState: runState
                    signal: actions.goLeft
                    guard: eventType === "press"
                }

                DSM.SignalTransition {
                    targetState: runState
                    signal: actions.goRight
                    guard: eventType === "press"
                }

                DSM.SignalTransition {
                    targetState: jumpState
                    signal: actions.goUp
                    guard: eventType === "press"
                }
            }

            DSM.State {
                id: runState
                onEntered: {
                    console.log("RUN");
                    sprite.animation = "run";
                }

                DSM.SignalTransition {
                    targetState: idleState
                    signal: actions.goLeft
                    guard: eventType === "release" && !actions.keys.rightPressed
                }

                DSM.SignalTransition {
                    targetState: idleState
                    signal: actions.goRight
                    guard: eventType === "release" && !actions.keys.leftPressed
                }

                DSM.SignalTransition {
                    targetState: jumpState
                    signal: actions.goUp
                    guard: eventType === "press"
                }

                DSM.SignalTransition {
                    targetState: freefallState
                    signal: dog.onAirborneChanged
                    guard: dog.airborne
                }
            }

            DSM.State {
                id: jumpState
                onEntered: {
                    console.log("JUMP");
                    sprite.animation = "jump";
                    dog.applyLinearImpulse(Qt.point(0, -dog.getMass() * 10), dog.getWorldCenter());
                }

                DSM.SignalTransition {
                    targetState: actions.keys.leftPressed || actions.keys.rightPressed ? runState : idleState
                    signal: dog.onAirborneChanged
                    guard: !dog.airborne
                }
            }

            DSM.State {
                id: freefallState
                onEntered: {
                    console.log("FREEFALL");
                    sprite.animation = "freefall";
                }

                DSM.SignalTransition {
                    targetState: actions.keys.leftPressed || actions.keys.rightPressed ? runState : idleState
                    signal: dog.onAirborneChanged
                    guard: !dog.airborne
                }
            }
        }
    }
}

