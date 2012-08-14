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

import QuasiGame 1.0

QuasiGame {
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

    QuasiScene {
        id: scene

        width: parent.width * 10
        height: parent.height

        QuasiLayers {
            anchors.fill: parent
            drawType: Quasi.PlaneDrawType

            QuasiImageLayer {
                source: ":/images/layer_01.png"
                order: Quasi.BackgroundLayerOrdering_01
            }

            QuasiImageLayer {
                source: ":/images/layer_02.png"
                factor: 1.1
                order: Quasi.ForegroundLayerOrdering_01
            }
        }

        QuasiSprite {
            id: gameSprite

            x: 10
            y: 420

            animation: "stopped"

            animations: [
                QuasiSpriteAnimation {
                    name: "moving"

                    source: ":/images/moving.png"
                    frames: 20
                    duration: 450
                    loops: Animation.Infinite
                    inverse: gameSprite.horizontalMirror
                },
                QuasiSpriteAnimation {
                    name: "stopped"

                    source: ":/images/stopped.png"
                    frames: 7
                    duration: 5000
                    loops: Animation.Infinite
                }
            ]

            order: Quasi.InteractionLayerOrdering_01
        }

        viewport: QuasiViewport {
            id: gameViewport

            animationDuration: 1000
        }

        focus: true
        Keys.onPressed: {
            switch (event.key) {
                case Qt.Key_Left: {
                    gameSprite.horizontalMirror = true;

                    if (event.isAutoRepeat) {
                        startMoving();
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
                        startMoving();
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
                        stopMoving();
                        event.accepted = true;
                    }
                    break;
                }
            }
        }
    }
}
