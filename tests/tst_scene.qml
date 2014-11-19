/**
 * Copyright (C) 2014-2015 Bacon2D Project
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
