/**
 * The MIT License (MIT)
 *
 * Copyright (C) 2014-2015 Bacon2D Project
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
    name: "SceneTests"

    function init() {
        game.gameState = Bacon2D.Running;
        compare(game.currentScene.running, true, "Scene.running was false");
    }

    function cleanup() {
        game.gameState = Bacon2D.Paused;
    }

    function test_currentScene() {
        game.currentScene = scene;
        compare(game.currentScene, scene, "Current scene")
    }

    function test_runningScene() {
        game.currentScene = scene;
        compare(scene.running, true, "Running scene")
    }

    function test_nonRunningScene() {
        game.currentScene = scene2;
        compare(scene.running, false, "Non-running scene")
    }

    function test_runningScene2() {
        game.currentScene = scene2;
        compare(scene2.running, true, "Non-running scene")
    }

    function test_gameStatePaused() {
        game.currentScene = scene;
        game.gameState = Bacon2D.Paused;
        compare(scene.running, false, "Game paused")
    }

    function test_gameStateRunning() {
        game.currentScene = scene;
        game.gameState = Bacon2D.Running;
        compare(scene.running, true, "Game running")
    }

    Game {
        id: game
        currentScene: scene

        Scene {
            id: scene
        }

        Scene {
            id: scene2
        }
    }
}
