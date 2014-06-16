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

    width: 800
    height: 385

    currentScene: scene

    Scene {
        id: scene

        focus: true
        width: parent.width
        height: parent.height

        enterAnimation: NumberAnimation{ target:scene;properties: "x"; to: 500}
        exitAnimation: ColorAnimation{ target:rect; properties: "color"; to: "yellow"; duration: 500}
        Rectangle{
            id:rect
            color:"red"
            anchors.fill: parent
        }

        Component.onCompleted: {
           console.log("calling exit animation")
            scene.callExitAnimation()
        }
    }
}
