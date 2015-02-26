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
    height: 600
    visible: true

    Game {
        id: game
        width: 800
        height: 600

        currentScene: scene

        function startMoving() {
            if (gameSprite.animation != "moving")
                gameSprite.animation = "moving";
        }

        function stopMoving() {
            if (gameSprite.animation != "stopped")
                gameSprite.animation = "stopped";
        }

        Scene {
            id: scene

            width: parent.width * 10
            height: parent.height

            ImageLayer {
                anchors.fill: parent
                source: "images/layer_01.png"
            }

            ImageLayer {
                anchors.fill: parent
                source: "images/layer_02.png"
            }

            Sprite {
                id: gameSprite

                x: 10
                y: 420

                animation: "stopped"

                animations: [
                    SpriteAnimation {
                        name: "moving"

                        source: "images/moving.png"
                        frames: 20
                        duration: 450
                        loops: Animation.Infinite
                        inverse: gameSprite.horizontalMirror
                    },
                    SpriteAnimation {
                        name: "stopped"

                        source: "images/stopped.png"
                        frames: 7
                        duration: 5000
                        loops: Animation.Infinite
                    }
                ]

            }

            viewport: Viewport {
                id: gameViewport

                animationDuration: 1000
            }

            focus: true
            Keys.onPressed: {
                switch (event.key) {
                    case Qt.Key_Left: {
                        gameSprite.horizontalMirror = true;

                        if (event.isAutoRepeat) {
                            game.startMoving();
                            if (gameSprite.x > 0)
                                gameSprite.x -= 5;
                        }

                        event.accepted = true;

                        if (gameSprite.x == gameViewport.xOffset)
                            gameViewport.hScroll(gameViewport.xOffset - (game.width / 2));

                        break;
                    }
                    case Qt.Key_Right: {
                        gameSprite.horizontalMirror = false;

                        if (event.isAutoRepeat) {
                            game.startMoving();
                            if (gameSprite.x + gameSprite.width <= scene.width)
                                gameSprite.x += 5;
                        }

                        event.accepted = true;

                        if (gameSprite.x + gameSprite.width >= gameViewport.xOffset + game.width)
                            gameViewport.hScroll(gameViewport.xOffset + (game.width / 2));

                        break;
                    }
                }
            }
            Keys.onReleased: {
                switch (event.key) {
                    case Qt.Key_Left:
                    case Qt.Key_Right: {
                        if (!event.isAutoRepeat) {
                            game.stopMoving();
                            event.accepted = true;
                        }
                        break;
                    }
                }
            }
        }
    }
}
