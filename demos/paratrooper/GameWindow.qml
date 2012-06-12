/**
 * Copyright (C) 2012 by INdT
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * @author Rodrigo Goncalves de Oliveira <rodrigo.goncalves@openbossa.org>
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

QuasiGame {
    id: game

    width: 1350
    height: 900

    currentScene: scene
    focus: true

    property int wallHeight: 1

    // game properties
    property bool useDownKey: false
    property int maxLandingImpulse: 50
    property int score: 0

    function win() {
        console.log("You Win")
        var score = getScore()
    }

    function lose() {
        console.log("You Lose")
    }

    function getPrecisionScore() {
        var landingAreaCenter = landingArea.x + landingArea.width / 2
        var playerCenter = player.x + player.width / 2
        var distance = Math.abs(landingAreaCenter - playerCenter)
        var max = landingArea.width / 2
        var score = (max - distance) * 100 / max

        return Math.round(score)
    }

    function getScore() {
        var precisionScore = getPrecisionScore()

        // getImpulseScore
        // getTimeScore

        console.log("Precision: " + getPrecisionScore() + "%")
    }

    function done(impulse) {
        scene.running = false

        if (impulse < maxLandingImpulse)
            win()
        else
            lose()

        resetTimer.running = true
    }

    function reset() {
        console.log("reset game")

        // reset player
        player.x = width / 2 - player.width / 2
        player.y = 0

        // reset target
        landingArea.x = Math.round(Math.random() * (scene.width - landingArea.width))

        scene.running = true
    }

    function togglePauseResume() {
        scene.running = !scene.running
    }

    QuasiPhysicsScene {
        id: scene

        anchors.fill: parent
        gravity: Qt.point(0, -0.5)
        clip: true

        Rectangle {
            id: sky
            anchors.fill: parent
            gradient: Gradient {
                GradientStop { position: 0.0; color: "lightBlue" }
                GradientStop { position: 1.0; color: "white" }
            }
        }

        Item {
            z: 1
            anchors.left: parent.left
            anchors.right: parent.right

            Rectangle {
                id: sunLight1
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "yellow" }
                    GradientStop { position: 1.0; color: "transparent" }
                }

                opacity: 0.25
                anchors.centerIn: sun
                width: 350
                height: 350
                radius: width
            }

            Rectangle {
                id: sunLight2
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "yellow" }
                    GradientStop { position: 1.0; color: "transparent" }
                }
                opacity: 0.2
                anchors.centerIn: sun
                width: 600
                height: 600
                radius: width
            }

            Rectangle {
                id: sunLight3
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "yellow" }
                    GradientStop { position: 1.0; color: "transparent" }
                }
                opacity: 0.1
                anchors.centerIn: sun
                width: 1000
                height: 1000
                radius: width
            }

            Image {
                id: sun
                source: ":/sun.png"
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.margins: -sun.height / 2
            }
        }

        QuasiImageLayer {
            anchors.fill: parent
            animated: true
            source: ":/background_clouds.png"
            horizontalStep: player.windReversed ? -1 : 1
            layerType: Quasi.MirroredType
            tileWidth: 90
            tileHeight: 90
        }

        QuasiImageLayer {
            anchors.fill: parent
            animated: true
            source: ":/foreground_wind.png"
            horizontalStep: {
                if (player.windReversed)
                    -5 * (player.windImpulseFactor / player.playerImpulseFactor)
                else
                    5 * (player.windImpulseFactor / player.playerImpulseFactor)
            }
            layerType: Quasi.MirroredType
            tileWidth: 90
            tileHeight: 90
        }

        QuasiBody {
            id: topWall

            bodyType: Quasi.StaticBodyType

            height: game.wallHeight
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top

            QuasiFixture {
                shape: Rectangle {
                    color: "lightGray"
                    anchors.fill: parent
                }

                material: QuasiMaterial {
                    density: 50
                    restitution: 0
                }
            }
        }

        QuasiBody {
            id: leftWall

            bodyType: Quasi.StaticBodyType

            width: game.wallHeight
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom

            QuasiFixture {
                shape: Rectangle {
                    color: "lightGray"
                    anchors.fill: parent
                }

                material: QuasiMaterial {
                    density: 50
                    restitution: 0.2
                }
            }
        }

        QuasiBody {
            id: rightWall

            bodyType: Quasi.StaticBodyType

            width: game.wallHeight
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom

            QuasiFixture {
                shape: Rectangle {
                    color: "lightGray"
                    anchors.fill: parent
                }

                material: QuasiMaterial {
                    density: 50
                    restitution: 0.2
                }
            }
        }

        QuasiBody {
            id: ground

            bodyType: Quasi.StaticBodyType

            height: 50
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            QuasiFixture {
                shape: Rectangle {
                    anchors.fill: parent
                    gradient: Gradient {
                        GradientStop { position: 0.1; color: "green" }
                        GradientStop { position: 1.0; color: "#003000" }
                    }
                }

                material: QuasiMaterial {
                    density: 50
                    restitution: 0.3
                }
            }
        }

        QuasiBody {
            id: landingArea

            bodyType: Quasi.StaticBodyType

            width: target.width
            height: 2
            anchors.verticalCenter: ground.top
            x: Math.round(Math.random() * (scene.width - landingArea.width))

            QuasiFixture {
                material: QuasiMaterial {
                    density: 100
                    restitution: 0
                    friction: 50
                }

                shape: Item {
                    width: target.width
                    height: 2

                    Image {
                        id: target
                        source: ":/target.png"
                        anchors.centerIn: parent
                        smooth: true
                        transform: Rotation {
                            angle: 75
                            origin.x: target.width / 2
                            origin.y: target.height / 2
                            axis { x: 1; y: 0; z: 0 }
                        }
                    }
                }
            }
        }

        Paratrooper {
            id: player
            focus: true
            x: parent.width / 2 - width / 2
        }

        onContact: {
            if (fixtureA.body == landingArea || fixtureB.body == landingArea)
                done(impulse)
        }
    }

    Timer {
        id: resetTimer
        interval: 2000
        onTriggered: reset()
    }

    Keys.onPressed: {
        if (event.key == Qt.Key_P)
            togglePauseResume()
    }
}
