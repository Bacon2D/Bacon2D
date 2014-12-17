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
 * @author Paulo Victor de Almeida Pinheiro <paulovap.os@gmail.com>
 */

import QtQuick 2.2
import Bacon2D 1.0

/*
  Same example as InfiniteFall, but using InfiniteScollItem instead of ImageLayer
 */
Game {
    id: game

    width: 512
    height: 512

    currentScene: scene

    Scene {
        id: scene

        focus: true
        width: parent.width
        height: parent.height

        InfiniteScrollEntity {
            id: scroller
            anchors.centerIn: parent

            Image{
                width: scene.width; height: scene.height
                fillMode: Image.Tile
                source: "sky.png"
                Timer{
                    interval: 15
                    repeat: true
                    running: true
                    onTriggered: scroller.offsetY +=1
                }
            }
        }
        Sprite {
            id: spriteItem

            x: scene.width / 2 - spriteItem.width / 2
            y: scene.height / 2 - spriteItem.height / 2

            animation: "falling"

            animations: SpriteAnimation {
                name: "falling"
                source: "astronaut.png"
                frames: 3
                duration: 450
                loops: Animation.Infinite
            }

            NumberAnimation on rotation {
                from: 0
                to: 360
                running: true
                loops: Animation.Infinite
                duration: 1800
            }
        }
    }
}
