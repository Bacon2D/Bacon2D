/**
 * The MIT License (MIT)
 *
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
 * @author Paulo Pinheiro <paulovictor.pinheiro@gmail.com>
 */

import QtQuick 2.2
import QtQuick.Window 2.0
import QtQuick.Controls 1.1
import Bacon2D 1.0

Window {
    width: 800
    height: 600
    visible: true

    Game {
        id: game
        anchors.fill: parent

        currentScene: scene1

        onStackLevelChanged: {
            console.log("Scene StackLevel: " + stackLevel)
        }

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
                    id:text
                    anchors.centerIn: parent
                    color: "blue"
                    text:"Scene 1"
                }
                Row{
                    anchors.top: text.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    Button{
                        text:"pop"
                        onClicked: game.popScene()
                    }
                    Button{
                        text:"push"
                        onClicked: game.pushScene(scene2)
                    }
                    Button{
                        text:"switch"
                        onClicked: game.currentScene = scene2
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
            exitAnimation: NumberAnimation{  target:scene2; properties: "x"; to: scene2.width; from:0; easing.type: Easing.InBounce; duration: 500}
            Rectangle{
                id:rect2
                color:"blue"
                anchors.fill: parent

                Text{
                    id:text_2
                    anchors.centerIn: parent
                    color: "white"
                    text:"Scene 2"
                }
                Row{
                    anchors.top: text_2.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    Button{
                        text:"pop"
                        onClicked: game.popScene()
                    }
                    Button{
                        text:"push"
                        onClicked: game.pushScene(scene3)
                    }
                    Button{
                        text:"switch"
                        onClicked: game.currentScene = scene3
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
                    id:text_3
                    anchors.centerIn: parent
                    color: "black"
                    text:"Scene 3"
                }
                Row{
                    anchors.top: text_3.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    Button{
                        text:"pop"
                        onClicked: game.popScene()
                    }
                    Button{
                        text:"push"
                        onClicked: game.pushScene(scene4)
                    }
                    Button{
                        text:"switch"
                        onClicked: game.currentScene = scene4
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
                    id:text_4
                    anchors.centerIn: parent
                    color: "green"
                    text:"Scene 4"
                }
                Row{
                    anchors.top: text_4.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    Button{
                        text:"pop"
                        onClicked: game.popScene()
                    }
                    Button{
                        text:"push"
                        onClicked: game.pushScene(scene5)
                    }
                    Button{
                        text:"switch"
                        onClicked: game.currentScene = scene5
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

            onRunningChanged: {
                console.log("scene5 running: " + running)
            }

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

            Text{
                id:text_5
                anchors.left: parent.left
                anchors.leftMargin: 150
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 20
                text: "Scene 5"
                color: "white"
            }

            Row{
                anchors.top: text_5.bottom
                anchors.horizontalCenter: text_5.horizontalCenter
                Button{
                    text:"pop"
                    onClicked: game.popScene()
                }
                Button{
                    text:"push"
                    onClicked: game.pushScene(scene1)
                }
                Button{
                    text:"switch"
                    onClicked: game.currentScene = scene1
                }
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
}
