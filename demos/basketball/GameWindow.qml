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
 * @author
 */

QuasiGame {
    id: game

    property int score: 0
    property int currentBallIndex: ballmodel.count - 1
    property int scale: 200
    property real freethrow: 5.80 * game.scale

    width: 7.60 * game.scale
    height: 900

    currentScene: scene

    QuasiPhysicsScene {
        id: scene

        width: parent.width
        height: parent.height

        gravity: Qt.point(0, -30.0)

        Rectangle {
            id: backgound
            anchors.fill: parent
            color: "darkCyan"
        }

        Image {
            id: backBoardhandler
            anchors.bottom: parent.bottom
            source: ":/images/backboardhandler.png"
        }

        QuasiMaterial {
            id: basketMaterial
            friction: 1.0
            density: 0.1
            restitution: 0.0
        }

        QuasiBody {
            id: backBoard

            bodyType: Quasi.StaticBodyType

            x: 1.2 * game.scale
            y: parent.height - (3.95 * game.scale)

            width: 4
            height: 1.05 * game.scale

            QuasiFixture {
                material: basketMaterial
                shape: Rectangle {
                    color: "white"
                    anchors.fill: parent
                }
            }
        }

        QuasiBody {
            id: basketHandler

            bodyType: Quasi.StaticBodyType

            x: backBoard.x + backBoard.width
            y: parent.height - (3.05 * game.scale)

            width: (1.575 * game.scale) - x - (ball.width / 1.9)
            height: 8

            QuasiFixture {
                material: basketMaterial
                shape: Rectangle {
                    color: "white"
                    anchors.fill: parent
                }
            }
        }

        QuasiBody {
            id: basketRing

            bodyType: Quasi.StaticBodyType

            x: basketHandler.x + basketHandler.width + (ball.width * 1.2)
            y: basketHandler.y

            width: 8
            height: 8

            QuasiFixture {
                material: basketMaterial
                shape: Rectangle {
                    color: "white"
                    anchors.fill: parent
                }
            }
        }

        Image {
            id: basket
            anchors.left: basketHandler.right
            anchors.right: basketRing.left

            y: basketHandler.y
            z: 100

            source: ":/images/basket.png"
        }

        QuasiBody {
            id: basketRight

            bodyType: Quasi.StaticBodyType

            x: basketRing.x
            y: basketRing.y + basketRing.height

            width: 4
            height: ball.height / 2

            QuasiFixture {
                material: basketMaterial
                shape: Item {
                    anchors.fill: parent
                }
            }
        }

        QuasiBody {
            id: basketLeft

            bodyType: Quasi.StaticBodyType

            x: basketHandler.x + basketHandler.width - width
            y: basketHandler.y + basketHandler.height

            width: 4
            height: ball.height / 2

            QuasiFixture {
                material: basketMaterial
                shape: Item {
                    anchors.fill: parent
                }
            }
        }

        QuasiBody {
            id: ground

            bodyType: Quasi.StaticBodyType

            x: 0
            y: parent.height - height

            width: parent.width
            height: 10

            QuasiFixture {
                material: QuasiMaterial {
                    friction: 0.3
                    density: 5
                    restitution: 0.6
                }

                shape: Rectangle {
                    color: "darkGreen"
                    anchors.fill: parent
                }
            }
        }

        QuasiBody {
            id: ball
            property int centerX: x + (width / 2)
            property int centerY: y + (height / 2)
            property bool threw: false
            property bool scored: false

            width: 0.25 * game.scale
            height: 0.25 * game.scale

            sleepingAllowed: false

            QuasiFixture {
                material: QuasiMaterial {
                    friction: 0.3
                    density: 50
                    restitution: 0.6
                }

                shape: QuasiCircle {
                    anchors.fill: parent
                }
            }

            Image {
                id: ballImage
                anchors.fill: parent
                source: ":/images/ball.png"
                smooth: true
            }

            x: game.freethrow
            y: game.height - height

            onYChanged: {

                if (!threw)
                    return;

                if (centerX > basketHandler.x + basketHandler.width
                        && centerX < basketRing.x
                        && centerY > basketRing.y
                        && centerY < basketRing.y + basket.height) {

                    if (!scored && centerY < basketRing.y + (ball.height / 2)) {
                        ballmodel.get(currentBallIndex).type = "score";
                        scored = true;
                        score++;
                        console.log("score = " + score);
                    }
                    basket.source = ":/images/scorebasket.png"
                } else {
                    basket.source = ":/images/basket.png"
                }
            }
        }

        MouseArea {
            anchors.fill: parent

            onClicked: {
                if (currentBallIndex < 0) {
                    // Reset demo
                    var i = 0;
                    currentBallIndex = ballmodel.count - 1
                    for (i = 0; i <= currentBallIndex; i++) {
                        ballmodel.get(i).type = "blank";
                    }
                    score = 0;
                    return;
                }

                if (ball.centerX > game.freethrow
                        && ball.centerX < game.freethrow + ball.width) {
                    var xLaunch = 2 * game.scale * (game.mouse.x - ball.centerX);
                    var yLaunch = 2 * game.scale * (game.mouse.y - ball.centerY);

                    ball.applyLinearImpulse(Qt.point(xLaunch, yLaunch), Qt.point(ball.centerX, ball.centerY));

                    ball.threw = true;
                } else {
                    ball.setLinearVelocity(Qt.point(0, 0));
                    ball.setAngularVelocity(0);
                    ball.x = game.freethrow
                    ball.y = parent.height - 3 * ball.height;

                    if (ball.threw) {
                        if (!ball.scored) {
                            ballmodel.get(currentBallIndex).type = "fail";
                        }

                        currentBallIndex --;
                    }

                    ball.threw = false;
                }

                ball.scored = false;
            }
        }
    }

    ListModel {
        id: ballmodel
        ListElement { type: "blank" }
        ListElement { type: "blank" }
        ListElement { type: "blank" }
        ListElement { type: "blank" }
        ListElement { type: "blank" }
        ListElement { type: "blank" }
        ListElement { type: "blank" }
        ListElement { type: "blank" }
        ListElement { type: "blank" }
        ListElement { type: "blank" }
    }

    Row {
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
        spacing: 10

        Repeater {
            model: ballmodel

            Image {
                id: scoreview
                width: 50
                height: 50

                source: ":/images/" + type + "ball.png"
            }
        }
    }
}
