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

    width: 800
    height: 400

    currentScene: scene

    function toLeft() {
        shipImage.mirror = true;
        layers.direction = Quasi.ForwardDirection;
    }

    function toRight() {
        shipImage.mirror = false;
        layers.direction = Quasi.BackwardDirection;
    }

    QuasiScene {
        id: scene

        width: parent.width
        height: parent.height

        QuasiLayers {
            id: layers

            // TODO: make 'horizontalStep' a property from QuasiLayers, not QuasiImageLayer?
            anchors.fill: parent
            drawType: Quasi.TiledDrawType // XXX: There are some problems with Quasi.PLaneDrawType
            tileWidth: 40
            tileHeight: 40
            //drawGrid: true // nice for debug; default: false

            property variant direction: Quasi.BackwardDirection

            QuasiImageLayer {
                animated: true
                source: ":/images/space.png"
                factor: 0.3
                order: Quasi.BackgroundLayerOrdering_01

                horizontalStep: 1
                layerType: Quasi.MirroredType
                direction: layers.direction
            }

            QuasiImageLayer {
                animated: true
                source: ":/images/planet.png"
                factor: 0.5
                order: Quasi.BackgroundLayerOrdering_02

                horizontalStep: 1
                layerType: Quasi.InfiniteType
                direction: layers.direction
            }

            QuasiImageLayer {
                animated: true
                source: ":/images/stars.png"
                factor: 1.1
                order: Quasi.ForegroundLayerOrdering_01

                horizontalStep: 1
                layerType: Quasi.InfiniteType
                direction: layers.direction
            }

            QuasiImageLayer {
                animated: true
                source: ":/images/moon.png"
                factor: 1.2
                order: Quasi.ForegroundLayerOrdering_02

                horizontalStep: 1
                layerType: Quasi.InfiniteType
                direction: layers.direction
            }
        }

        QuasiEntity {
            id: ship

            y: (game.height / 2) - (shipImage.height / 2)
            x: 25
            /* layer ordering, set how the layers will be presented when rendering
            * possible values, splited in three main areas:
            * - These enums defines the ordering of the game entities
            EntityOrdering_01 (default), EntityOrdering_02 and EntityOrdering_03
            * Please, bear in mind that you can use as many entities you want to (and that your system can support), but they will be ordered according these values
            * Prefer to keep colliding items on the same ordering
            */
            order: Quasi.EntityOrdering_01

            Image {
                id: shipImage

                source: ":/images/rocketship.png"
            }

            focus: true
            Keys.onPressed: {
                switch (event.key) {
                case Qt.Key_Left:
                    toLeft();
                    ship.x -= 5;
                    break;
                case Qt.Key_Right:
                    toRight();
                    ship.x += 5;
                    break;
                case Qt.Key_Down:
                    ship.y += 5;
                    break;
                case Qt.Key_Up:
                    ship.y -= 5;
                    break;
                }
            }
        }
    }
}
