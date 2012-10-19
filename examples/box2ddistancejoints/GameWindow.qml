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

    width: 300
    height: 300

    currentScene: scene

    Rectangle {
        anchors.fill: parent
        color: "black"
    }

    QuasiScene {
        id: scene

        width: parent.width
        height: parent.height

        QuasiEntity {
            id: static1

            width: 30
            height: 30

            y: 100
            x: 100

            QuasiFixture {
                material: randomMaterial

                anchors.fill: parent

                shape: Rectangle {
                    color: "white"
                    anchors.fill: parent
                }
            }
        }

        QuasiDistanceJoint {
            entityA: static1
            entityB: dynamic1

            width: 1

            Rectangle {
                anchors.fill: parent
                color: "green"
                radius: 5
            }
        }

        QuasiEntity {
            id: dynamic1

            property int centerX: x + (width / 2)
            property int centerY: y + (height / 2)

            entityType: Quasi.DynamicType

            width: 30
            height: 30

            y: 200
            x: 100

            QuasiFixture {
                material: randomMaterial

                anchors.fill: parent

                shape: QuasiCircle {
                    anchors.fill: parent
                    fill: QuasiColorFill {
                        brushColor: "red"
                    }
                }
            }
        }

        QuasiEntity {
            id: static2

            width: 30
            height: 30

            y: 100
            x: 135

            QuasiFixture {
                material: randomMaterial

                anchors.fill: parent

                shape: Rectangle {
                    color: "white"
                    anchors.fill: parent
                }
            }
        }

        QuasiDistanceJoint {
            entityA: static2
            entityB: dynamic2

            width: 1

            Rectangle {
                anchors.fill: parent
                color: "green"
                radius: 5
            }
        }

        QuasiEntity {
            id: dynamic2

            entityType: Quasi.DynamicType

            width: 30
            height: 30

            y: 200
            x: 135

            QuasiFixture {
                material: randomMaterial

                anchors.fill: parent

                shape: QuasiCircle {
                    anchors.fill: parent
                    fill: QuasiColorFill {
                        brushColor: "red"
                    }
                }
            }
        }

        QuasiEntity {
            id: static3

            width: 30
            height: 30

            y: 100
            x: 170

            QuasiFixture {
                material: randomMaterial

                anchors.fill: parent

                shape: Rectangle {
                    color: "white"
                    anchors.fill: parent
                }
            }
        }

        QuasiDistanceJoint {
            entityA: static3
            entityB: dynamic3

            width: 1

            Rectangle {
                anchors.fill: parent
                color: "green"
                radius: 5
            }
        }

        QuasiEntity {
            id: dynamic3

            entityType: Quasi.DynamicType

            width: 30
            height: 30

            y: 200
            x: 170

            QuasiFixture {
                material: randomMaterial

                anchors.fill: parent

                shape: QuasiCircle {
                    anchors.fill: parent
                    fill: QuasiColorFill {
                        brushColor: "red"
                    }
                }
            }
        }

        QuasiEntity {
            id: static4

            width: 30
            height: 30

            y: 100
            x: 205

            QuasiFixture {
                material: randomMaterial

                anchors.fill: parent

                shape: Rectangle {
                    color: "white"
                    anchors.fill: parent
                }
            }
        }

        QuasiDistanceJoint {
            entityA: static4
            entityB: dynamic4

            width: 1

            Rectangle {
                anchors.fill: parent
                color: "green"
                radius: 5
            }
        }

        QuasiEntity {
            id: dynamic4

            entityType: Quasi.DynamicType

            width: 30
            height: 30

            y: 200
            x: 205

            QuasiFixture {
                material: randomMaterial

                anchors.fill: parent

                shape: QuasiCircle {
                    anchors.fill: parent
                    fill: QuasiColorFill {
                        brushColor: "red"
                    }
                }
            }
        }

        Component.onCompleted: dynamic1.applyLinearImpulse(Qt.point(-1000, 0), Qt.point(dynamic1.centerX, dynamic1.centerY))
    }

    QuasiMaterial {
        id: randomMaterial

        friction: 0.3 + Math.random() * 1.0
        density: 5 + Math.random() * 10
        restitution: 0.5 + Math.random() * 0.5
    }
}
