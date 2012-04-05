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

    width: 400
    height: 250

    currentScene: scene

    QuasiScene {
        id: scene

        width: parent.width
        height: parent.height

        entities: [
            QuasiEntity {
                id: item

                property string name: "RED"

                width: rect.width
                height: rect.height
                x: 0

                updateInterval: 10

                updateScript: {
                    var newPos = item.x + 2
                    item.x = newPos > parent.width ? 0 : newPos
                }

                Rectangle {
                    id: rect
                    width: 50
                    height: 50

                    color: item.collided ? "green" : "red"
                }

                onCollidedChanged: {
                    if (collided) {
                        console.log("red collided with:")
                        var collidedList = item.collidedItems()
                        console.log(collidedList)
                        for (var i=0; i< collidedList.length; ++i) {
                            var gameItem = collidedList[i]
                            console.log(gameItem)
                            console.log(gameItem.name)
                        }
                    }
                }
            },
            QuasiEntity {
                id: item2

                property string name: "BLUE"

                width: rect2.width
                height: rect2.height
                x: parent.width

                updateInterval: 10

                updateScript: {
                    var newPos = item2.x - 2
                    item2.x = newPos < 0 ? parent.width : newPos
                }

                Rectangle {
                    id: rect2
                    width: 50
                    height: 50

                    color: item2.collided ? "green" : "blue"
                }
            },
            QuasiEntity {
                id: item3

                property string name: "YELLOW"

                width: rect3.width
                height: rect3.height
                x: parent.width / 2
                y: 0

                updateInterval: 10

                updateScript: {
                    var newPos = item3.y + 2
                    item3.y = newPos > parent.height ? 0 : newPos
                }

                Rectangle {
                    id: rect3
                    width: 50
                    height: 50

                    color: item3.collided ? "green" : "yellow"
                }
            },
            QuasiEntity {
                id: item4

                property string name: "GRAY"

                width: rect4.width
                height: rect4.height
                x: parent.width / 2
                y: parent.height

                updateInterval: 10

                updateScript: {
                    var newPos = item4.y - 2
                    item4.y = newPos < 0 ? parent.height : newPos
                }

                Rectangle {
                    id: rect4
                    width: 50
                    height: 50

                    color: item4.collided ? "green" : "gray"
                }
            }
        ]
    }
}
