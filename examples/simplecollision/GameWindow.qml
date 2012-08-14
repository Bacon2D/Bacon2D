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

    QuasiScriptBehavior {
        id: sideScrollBehavior

        script: {
            var newPos = entity.x + entity.scrollStep
            entity.x = newPos > scene.width ? 0 : newPos
            entity.x = entity.x < 0 ? scene.width : entity.x
        }
    }

    QuasiScriptBehavior {
        id: verticalScrollBehavior

        script: {
            var newPos = entity.y + entity.scrollStep
            entity.y = newPos > scene.height ? 0 : newPos
            entity.y = entity.y < 0 ? scene.height : entity.y
        }
    }

    QuasiScene {
        id: scene

        width: parent.width
        height: parent.height

        onContactPreSolve: {
            console.log("preSolve:", contact.fixtureA.entity, "collided with", contact.fixtureB.entity)
        }

        onContactPostSolve: {
            console.log("postSolve:", contact.fixtureA.entity, "collided with", contact.fixtureB.entity)
        }

        onContactBegin: {
            console.log("beginContact:", contact.fixtureA.entity, "collided with", contact.fixtureB.entity)
        }

        onContactEnd: {
            console.log("endContact:", contact.fixtureA.entity, "collided with", contact.fixtureB.entity)
        }

        QuasiEntity {
            id: item

            property string name: "RED"
            property int scrollStep: 2

            width: rect.width
            height: rect.height
            x: 0

            updateInterval: 10

            behavior: sideScrollBehavior

            Rectangle {
                id: rect
                width: 50
                height: 50

                color: "red"
            }
        }

        QuasiEntity {
            id: item2

            property string name: "BLUE"
            property int scrollStep: -2

            width: rect2.width
            height: rect2.height
            x: parent.width

            updateInterval: 10

            behavior: sideScrollBehavior

            Rectangle {
                id: rect2
                width: 50
                height: 50

                color: "blue"
            }
        }

        QuasiEntity {
            id: item3

            property string name: "YELLOW"
            property int scrollStep: 2

            width: rect3.width
            height: rect3.height
            x: parent.width / 2
            y: 0

            updateInterval: 10

            behavior: verticalScrollBehavior

            Rectangle {
                id: rect3
                width: 50
                height: 50

                color: "yellow"
            }
        }

        QuasiEntity {
            id: item4

            property string name: "GRAY"
            property int scrollStep: -2

            width: rect4.width
            height: rect4.height
            x: parent.width / 2
            y: parent.height

            updateInterval: 10

            behavior: verticalScrollBehavior

            Rectangle {
                id: rect4
                width: 50
                height: 50

                color: "gray"
            }
        }
    }
}
