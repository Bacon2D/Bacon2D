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

    width: 1024
    height: 768

    currentScene: scene
    focus: true

    property int wallHeight: 1
    property bool useDownKey: false
    property int maxLandingImpulse: 35
    property int score: 0

    function win() {
        console.log("You Win")
    }

    function lose() {
        console.log("You Lose")
        player.explode()
    }

    function calcPrecision() {
        var landingAreaCenter = landingArea.x + landingArea.width / 2
        var playerCenter = player.x + player.width / 2
        var distance = Math.abs(landingAreaCenter - playerCenter)
        var max = landingArea.width / 2
        var score = (max - distance) * 100 / max

        return Math.round(score)
    }

    function done(impulse, body) {
        scene.running = false

        var precision = calcPrecision()

        console.log("landing impulse: " + impulse + " -- precision: " + precision)

        if (impulse > maxLandingImpulse || body != landingArea || precision < 0)
            lose()
        else
            win()

        resetTimer.running = true
    }

    function reset() {
        console.log("reset game")

        player.reset()

        // reset target
        landingArea.x = Math.round(Math.random() * (scene.width - landingArea.width))

        scene.running = true
    }

    function togglePauseResume() {
        scene.running = !scene.running
    }

    QuasiScene {
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

        QuasiImageLayer {
            width: 1350
            height: 900
            animated: true
            source: ":/background_clouds.png"
            horizontalStep: player.windReversed ? -1 : 1
            layerType: Quasi.MirroredType
            tileWidth: 90
            tileHeight: 90
        }

        Image {
            id: sun
            source: ":/sun.png"
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.margins: -sun.height / 2
        }

        QuasiImageLayer {
            width: 1350
            height: 900
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

        QuasiEntity {
            id: topWall

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

        QuasiEntity {
            id: leftWall

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
                    restitution: 0.1
                }
            }
        }

        QuasiEntity {
            id: rightWall

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
                    restitution: 0.1
                }
            }
        }

        QuasiEntity {
            id: ground

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
                    restitution: 0.1
                }
            }
        }

        QuasiEntity {
            id: landingArea

            width: target.width
            height: 2
            anchors.verticalCenter: ground.top
            x: Math.round(Math.random() * (scene.width - landingArea.width))

            Rectangle {
                color: "lightBlue"
                anchors.fill: parent
            }

            QuasiFixture {
                material: QuasiMaterial {
                    density: 100
                    restitution: 0
                    friction: 50
                }

                shape: Item {
                    width: target.width
                    height: 2
                }
            }

            Image {
                id: target
                source: ":/target.png"
                width: sourceSize.width / 2
                height: sourceSize.height / 2
                anchors.centerIn: parent
                smooth: true
            }
        }

        Paratrooper {
            id: player
            focus: true
            x: parent.width / 2 - width / 2
        }

        onContactPostSolve: {
            var fixtureA = contact.fixtureA
            var fixtureB = contact.fixtureB
            var impulse = contact.maxImpulse

            if (fixtureA.entity == landingArea || fixtureB.entity == landingArea)
                done(impulse, landingArea)
            else if (fixtureA.entity == ground || fixtureB.entity == ground)
                done(impulse, ground)
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
