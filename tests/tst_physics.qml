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

    property var ball

    function init() {
        game.gameState = Bacon2D.Paused;
        compare(game.currentScene.running, false, "Scene.running was not false");
        ball = ballComp.createObject(scene, {"x": 5, "y": 100});
    }

    function cleanup() {
        // Reset the ball position and any game states
        game.gameState = Bacon2D.Paused;
    }

    function cleanupTestCase() {
        ball.destroy();
    }

    function test_ball_collides_with_ground() {
        // When the game is running, test the ball collides with the ground
        game.gameState = Bacon2D.Running;
        compare(scene.running, true, "Scene is not running");
        tryCompare(ball, "collidedWith", ground, 2000,
                   "Ball did not collide with ground")
    }

    function test_ball_falls() {
        // When the game is running, test the ball falls
        game.gameState = Bacon2D.Running;
        compare(scene.running, true, "Scene is not running");
        verify((ball.body.linearVelocity.y > 0), "Ball is not falling");

    }

    function test_ball_stationary() {
        // When the game is not running, test the ball remains stationary
        compare(scene.running, false, "Scene is running");
        wait(100);  // wait to check the ball doesn't fall
        compare(ball.body.linearVelocity.y, 0, "Ball is falling");
    }

    Game {
        id: game
        height: 600
        width: 800
        currentScene: scene

        Scene {
            id: scene
            height: 600
            width: 800
            physics: true
            gravity: Qt.point(0, 20)

            Component {
                id: ballComp
                Rectangle {
                    id: ballRect
                    transformOrigin: Item.TopLeft
                    radius: 180
                    width: 50
                    height: 50
                    color: "red"
                    property var collidedWith

                    property Body body: Body {
                        target: parent
                        world: scene.world

                        fixedRotation: false
                        sleepingAllowed: false
                        bodyType: Body.Dynamic

                        Circle {
                            radius: ball.width / 2
                            density: 1
                            friction: 1
                            restitution: 0.3
                            onBeginContact: ballRect.collidedWith = other.getBody().target
                        }
                    }
                }
            }

            PhysicsEntity {
                id: ground
                anchors {
                    bottom: parent.bottom
                    left: parent.left
                    right: parent.right
                }
                height: 2
                fixtures: Box {}
            }
        }
    }
}
