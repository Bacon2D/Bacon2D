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

import QtQuick 2.2
import Bacon2D 1.0

Game {
    id: game

    width: 800
    height: 600

    currentScene: scene1

    function startMoving() {
        if (gameSprite.animation != "moving")
            gameSprite.animation = "moving";
    }

    function stopMoving() {
        if (gameSprite.animation != "stopped")
            gameSprite.animation = "stopped";
    }

    Scene {
        id: scene1

        width: parent.width
        height: parent.height

        focus:true
        enterAnimation: NumberAnimation{ target:scene1; properties: "x"; from: scene1.width; to:0; duration: 500}
        exitAnimation: NumberAnimation{ target:scene1; properties: "x";  from: 0; to: scene1.width; duration: 500}
        Rectangle{
            id:rect
            color:"red"
            anchors.fill: parent

            Text{
                anchors.centerIn: parent
                color: "blue"
                text:"Scene 1"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    game.currentScene = scene2
                }
            }
        }
        onRunningChanged: {
            console.log("scene1 running: " + running)
        }
    }

    Scene {
        id: scene2
        width: parent.width
        height: parent.height

        enterAnimation: NumberAnimation{ target:scene2; properties: "x"; to: 0; from: -scene2.width; duration: 500}
        //exitAnimation: NumberAnimation{  target:scene2; properties: "x"; to: scene2.width; from:0; easing.type: Easing.InBounce; duration: 500}
        Rectangle{
            id:rect2
            color:"blue"
            anchors.fill: parent

            Text{
                anchors.centerIn: parent
                color: "white"
                text:"Scene 2"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    game.currentScene = scene3
                }
            }
        }
        onRunningChanged: {
            console.log("scene2 running: " + running)
        }
    }

    Scene {
        id: scene3

        width: parent.width
        height: parent.height

        enterAnimation: ParallelAnimation{
            NumberAnimation{ target: scene3; property:"rotation"; from:-270; to:0; duration: 500}
            NumberAnimation{ target: scene3; property:"scale"; from:0; to:1; duration: 500 }
        }

        exitAnimation: ParallelAnimation{
            NumberAnimation{ target: scene3; property:"rotation"; to:0; duration: 500}
            NumberAnimation{ target: scene3; property:"scale"; from:1; to:0.0; duration: 500 }
        }

        Rectangle{
            id:rect3
            color:"green"
            anchors.fill: parent

            Text{
                anchors.centerIn: parent
                color: "black"
                text:"Scene 3"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    game.currentScene = scene4
                }
            }

        }
        onRunningChanged: {
            console.log("scene3 running: " + running)
        }
    }

    Scene {
        id: scene4

        width: parent.width
        height: parent.height

        exitAnimation: NumberAnimation{ target:scene4; properties: "opacity"; from:1; to:0; duration: 500}
        enterAnimation: NumberAnimation{ target:scene4; properties: "opacity"; from:0; to:1.0; duration: 500}

        Rectangle{
            id:rect4
            color:"pink"
            anchors.fill: parent

            Text{
                anchors.centerIn: parent
                color: "green"
                text:"Scene 4"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    game.currentScene = scene5
                }
            }

        }
        onRunningChanged: {
            console.log("scene4 running: " + running)
        }
    }


    Scene {
        id: scene5

        width: parent.width * 10
        height: parent.height

        exitAnimation: NumberAnimation{ target:scene5; properties: "opacity"; from:1; to:0; duration: 500}
        enterAnimation: NumberAnimation{ target:scene5; properties: "opacity"; from:0; to:1.0; duration: 500}

        Text{
            anchors.left: parent.left
            anchors.leftMargin: 150
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 20
            text: "Scene 5"
            color: "white"
            z:10
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                game.currentScene = scene1
            }
        }

        ImageLayer {
            anchors.fill: parent
            drawType: Layer.PlaneDraw
            source: "images/layer_01.png"
        }

        ImageLayer {
            anchors.fill: parent
            drawType: Layer.PlaneDraw
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
                        if (gameSprite.x + gameSprite.width <= scene5.width)
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
