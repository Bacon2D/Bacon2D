/**
 * Copyright (C) 2014 by Bacon2D
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
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

import QtQuick 2.2
import Bacon2D 1.0

Game {
    id: game

    width: 512
    height: 512

    currentScene: scene
    focus: true
    clip: true

    Scene {
        id: scene

        anchors.fill: parent

        Image {
            anchors.fill: parent
            source: "sky.png"
        }

        Component {
            id: astronautComponent

            Entity {
                id: spriteItem

                x: parent.scene.width / 2 - spriteItem.width / 2
                y: parent.scene.height / 2 - spriteItem.height / 2

                Sprite {
                    anchors.fill: parent
                    animation: "falling"
                    animations: SpriteAnimation {
                        name: "falling"
                        source: "astronaut.png"
                        frames: 3
                        duration: 450
                        loops: Animation.Infinite
                    }
                }

                NumberAnimation on rotation {
                    from: 0
                    to: 360
                    running: true
                    loops: Animation.Infinite
                    duration: 1800
                }

                behavior: ScriptBehavior {
                    script: {
                        if (target.y > parent.scene.height)
                            target.destroy();
                    }
                }
            }
        }

        Layer {
            id: astronautsLayer
            anchors.fill: parent

            behavior: ScrollBehavior {
                verticalStep: 5
            }
        }

        Timer {
            id: spawnTimer

            interval: 800
            running: true
            repeat: true

            onTriggered: {
                var astronaut = astronautComponent.createObject(astronautsLayer);
                astronaut.y = -astronaut.height * 2;
                astronaut.x = Math.random() * (scene.width - astronaut.width);
            }
        }
    }
}
