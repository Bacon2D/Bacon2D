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

    focus: true
    clip: true
    width: 800
    height: 400

    currentScene: scene

    function toLeft() {
        scene.scrollFactor -= 0.05;
        if (scene.scrollFactor <= 0)
            shipImage.mirror = true;
    }

    function toRight() {
        scene.scrollFactor += 0.05;
        if (scene.scrollFactor >= 0)
            shipImage.mirror = false;
    }

    QuasiScene {
        id: scene

        width: parent.width
        height: parent.height

        property real scrollFactor: 1

        QuasiImageLayer {
            id: layer1
            anchors.fill: parent
            animated: true
            source: ":/images/space.png"
            horizontalStep: -10 * scene.scrollFactor
            layerType: Quasi.MirroredType
            tileWidth: 40
            tileHeight: 40
        }

        QuasiImageLayer {
            id: layer2
            anchors.fill: parent
            animated: true
            source: ":/images/planet.png"
            horizontalStep: -15 * scene.scrollFactor
            layerType: Quasi.InfiniteType
            tileWidth: 40
            tileHeight: 40
        }

        QuasiEntity {
            id: ship
            y: (game.height / 2) - (shipImage.height / 2)
            x: (game.width / 2) - (shipImage.width / 2)

            Image {
                id: shipImage
                source: "qrc:/images/rocketship.png"
            }

            Behavior on y { SmoothedAnimation {}}
        }

        QuasiImageLayer {
            id: layer3
            anchors.fill: parent
            animated: true
            source: ":/images/stars.png"
            horizontalStep: -20 * scene.scrollFactor
            layerType: Quasi.InfiniteType
            tileWidth: 40
            tileHeight: 40
        }

        QuasiImageLayer {
            id: layer4
            anchors.fill: parent
            animated: true
            source: ":/images/moon.png"
            horizontalStep: -23 * scene.scrollFactor
            layerType: Quasi.InfiniteType
            tileWidth: 40
            tileHeight: 40
        }
    }

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
        case Qt.Key_1:
            layer1.animated = !layer1.animated
            break;
        case Qt.Key_2:
            layer2.animated = !layer2.animated
            break;
        case Qt.Key_3:
            layer3.animated = !layer3.animated
            break;
        case Qt.Key_4:
            layer4.animated = !layer4.animated
            break;
        }
    }
}
