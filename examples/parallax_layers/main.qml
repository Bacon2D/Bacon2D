/**
 * The MIT License (MIT)
 *
 * Copyright (C) 2012 by INdT
 * Copyright (C) 2014 by Bacon2D
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @author Rodrigo Goncalves de Oliveira <rodrigo.goncalves@openbossa.org>
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

import QtQuick 2.2
import QtQuick.Window 2.0
import Bacon2D 1.0

Window {
    width: 800
    height: 400
    visible: true

    Game {
        id: game
        anchors.fill: parent

        focus: true
        clip: true

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

        Scene {
            id: scene

            width: parent.width
            height: parent.height

            property real scrollFactor: 1

            ImageLayer {
                id: layer1
                anchors.fill: parent
                source: "images/space.png"
                behavior: ScrollBehavior {
                    horizontalStep: -10 * scene.scrollFactor
                }
                layerType: Layer.Mirrored
            }

            ImageLayer {
                id: layer2
                anchors.fill: parent
                source: "images/planet.png"
                behavior: ScrollBehavior {
                    horizontalStep: -15 * scene.scrollFactor
                }
                layerType: Layer.Infinite

            }

            Entity {
                id: ship
                y: (game.height / 2) - (shipImage.height / 2)
                x: (game.width / 2) - (shipImage.width / 2)

                Image {
                    id: shipImage
                    source: "images/rocketship.png"
                }

                Behavior on y { SmoothedAnimation {}}
            }

            ImageLayer {
                id: layer3
                anchors.fill: parent
                source: "images/stars.png"
                behavior: ScrollBehavior {
                    horizontalStep: -20 * scene.scrollFactor
                }
                layerType: Layer.Infinite
            }

            ImageLayer {
                id: layer4
                anchors.fill: parent
                source: "images/moon.png"
                behavior: ScrollBehavior {
                    horizontalStep: -23 * scene.scrollFactor
                }
                layerType: Layer.Infinite
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
            }
        }
    }
}
