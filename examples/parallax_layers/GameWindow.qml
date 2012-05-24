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
        scene.layerDirection = Quasi.ForwardDirection;
    }

    function toRight() {
        shipImage.mirror = false;
        scene.layerDirection = Quasi.BackwardDirection;
    }

    QuasiScene {
        id: scene

        width: parent.width
        height: parent.height

        property variant layerDirection: Quasi.BackwardDirection

        QuasiImageLayer {
            animated: true
            source: ":/images/space.png"
            factor: 0.3

            horizontalStep: 1
            layerType: Quasi.MirroredType
            direction: scene.layerDirection

            // from QuasiLayers
            drawType: Quasi.TiledDrawType // XXX: There are some problems with Quasi.PLaneDrawType
            tileWidth: 40
            tileHeight: 40

            // TODO: Check if this should be needed
            anchors.fill: parent
        }

        QuasiImageLayer {
            animated: true
            source: ":/images/planet.png"
            factor: 0.5

            horizontalStep: 1
            layerType: Quasi.InfiniteType
            direction: scene.layerDirection

            // from QuasiLayers
            drawType: Quasi.TiledDrawType // XXX: There are some problems with Quasi.PLaneDrawType
            tileWidth: 40
            tileHeight: 40

            anchors.fill: parent
        }

        QuasiEntity {
            id: ship

            y: (game.height / 2) - (shipImage.height / 2)
            x: 25

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

        QuasiImageLayer {
            animated: true
            source: ":/images/stars.png"
            factor: 1.1

            horizontalStep: 1
            layerType: Quasi.InfiniteType
            direction: scene.layerDirection

            // from QuasiLayers
            drawType: Quasi.TiledDrawType // XXX: There are some problems with Quasi.PLaneDrawType
            tileWidth: 40
            tileHeight: 40

            anchors.fill: parent
        }

        QuasiImageLayer {
            animated: true
            source: ":/images/moon.png"
            factor: 1.2

            horizontalStep: 1
            layerType: Quasi.InfiniteType
            direction: scene.layerDirection

            // from QuasiLayers
            drawType: Quasi.TiledDrawType // XXX: There are some problems with Quasi.PLaneDrawType
            tileWidth: 40
            tileHeight: 40

            anchors.fill: parent
        }
    }
}
