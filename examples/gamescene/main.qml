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

import QtQuick 2.2
import Bacon2D 1.0

Item {
    id: container
    width: 900
    height: 300

    property int currentSceneIndex: 0

    Rectangle {
        anchors.fill: parent
        color: "gray"
    }

    Component {
        id: sceneComponent

        Scene {
            id: scene
            physics: true
            width: container.width/3
            height: container.height

            function applyLinearImpulse() {
                var center = Qt.point(x + width / 2, y + height / 2)
                var impulseX = -width + Math.random() * width
                var impulseY = -height + Math.random() * height
                var impulse = Qt.point(impulseX, impulseY)

                ball.applyLinearImpulse(impulse, center)
            }

            Rectangle {
                anchors.fill: parent
                color: "white"
            }

            Wall {
                anchors.right: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: 1
            }

            Wall {
                anchors.left: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: 1
            }

            Wall {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.top
                height: 1
            }

            Wall {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.bottom
                height: 1
            }

            Entity {
                id: ball
                width: 40
                height: 40
                x: scene.width / 2 - width / 2
                y: scene.height / 3
                fixedRotation: false
                sleepingAllowed: false
                bodyType: Entity.Dynamic
                fixtures: Circle {
                    id: circleShape
                    radius: parent.width / 2
                    anchors.fill: parent
                    density: 1;
                    friction: 1;
                    restitution: 0.5;
                }

                Rectangle {
                    id: itemShape
                    color: {
                        switch (currentSceneIndex) {
                            case 0: return "black"
                            case 1: return "red"
                            case 2: return "blue"
                        }
                    }
                    radius: parent.width / 2
                    width: parent.width
                    height: parent.height
                }
            }
        }
    }
    Timer {
        interval: 2000
        running: true
        repeat: true
        triggeredOnStart: true
        onTriggered: {
            game.currentScene = game.children[currentSceneIndex]
            game.currentScene.applyLinearImpulse()
            currentSceneIndex = (currentSceneIndex + 1) % game.children.length
        }
    }

    Game {
        id: game

        anchors.fill: parent
        focus: true

        Component.onCompleted: {
            var scene
            var prevScene

            for (var i = 0; i < 3; i++) {
                prevScene = game.children[game.children.length - 1]
                scene = sceneComponent.createObject(game)
                if (prevScene)
                    scene.anchors.left = prevScene.right
                else
                    scene.anchors.left = scene.parent.left
            }
        }
    }
}
