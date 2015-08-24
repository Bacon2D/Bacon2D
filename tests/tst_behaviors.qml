/**
 * The MIT License (MIT)
 *
 * Copyright (C) 2015 Bacon2D Project
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
 * @author Ken VanDine <ken@vandine.org>
 */

import QtQuick 2.3
import QtTest 1.0
import Bacon2D 1.0

TestCase {
    name: "PhysicsTests"

    function init() {
        game.gameState = Bacon2D.Paused;
        compare(game.currentScene.running, false, "Scene.running was not false");
    }

    function cleanup() {
        game.gameState = Bacon2D.Paused;
    }

    function cleanupTestCase() {
    }

    function test_behavior_scroll_x() {
        game.gameState = Bacon2D.Running;
        square.behavior = sideScrollBehavior;
        wait(100);
        verify(square.x > scene.x, "Square isn't moving on X");
    }

    function test_behavior_scroll_y() {
        game.gameState = Bacon2D.Running;
        square.behavior = verticalScrollBehavior;
        wait(100);
        verify(square.y > scene.y, "Square isn't moving on Y");
    }

    function test_behavior_update_interval() {
        game.gameState = Bacon2D.Running;
        square.x = scene.x;
        square.y = scene.y;
        square.behavior = verticalScrollBehavior;
        square.updateInterval = 50;
        // wait less than expected interval
        wait(25);
        verify(square.y == scene.y, "Square has moved on Y, before the expected interval");
        // wait more than expected interval
        wait(100);
        verify(square.y > scene.y, "Square hasn't moved on Y in the expected interval");
    }

    Game {
        id: game
        width: 800
        height: 600
        currentScene: scene

        ScriptBehavior {
            id: sideScrollBehavior
            script: {
                var newPos = target.x + target.scrollStep
                target.x = newPos > scene.width ? 0 : newPos
                target.x = target.x < 0 ? scene.width : target.x
            }
        }

        ScriptBehavior {
            id: verticalScrollBehavior
            script: {
                var newPos = target.y + target.scrollStep
                target.y = newPos > scene.height ? 0 : newPos
                target.y = target.y < 0 ? scene.height : target.y
            }
        }

        Scene {
            id: scene
            width: parent.width
            height: parent.height

            Entity {
                id: square
                property int scrollStep: 3

                width: 50
                height: 50
                x: scene.x
                y: scene.y

                //updateInterval: 50

                Rectangle {
                    width: 50
                    height: 50

                    color: "red"
                }
            }
        }

    }
}
