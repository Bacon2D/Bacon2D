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

Game {
    id: game

    width: 400
    height: 250

    currentScene: scene

    ScriptBehavior {
        id: sideScrollBehavior

        script: {
            var newPos = target.x + target.scrollStep
            target.x = newPos > scene.width ? 0 : newPos
            target.x = target.x < 0 ? scene.width : target.x
        }
    }

    ScriptBehavior {
        id: verticalScrollBehavior

        script: {
            var newPos = target.y + target.scrollStep
            target.y = newPos > scene.height ? 0 : newPos
            target.y = target.y < 0 ? scene.height : target.y
        }
    }

    Scene {
        id: scene

        width: parent.width
        height: parent.height

        Entity {
            id: square
            property int scrollStep: 3

            width: 50
            height: 50

            updateInterval: 50

            behavior: sideScrollBehavior

            Rectangle {
                width: 50
                height: 50

                color: "red"
            }
        }
    }

    MouseArea {
        anchors.fill: parent

        onClicked: square.behavior = square.behavior == sideScrollBehavior ? verticalScrollBehavior : sideScrollBehavior
    }
}
