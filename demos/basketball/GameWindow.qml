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
    property int scale: 180
    property real freethrow: 5.80 * game.scale

    width: 7.60 * game.scale
    height: 768

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
            id: backboardHandler
            anchors.bottom: parent.bottom
            source: ":/images/backboardhandler.png"
        }

        QuasiMaterial {
            id: boardMaterial
            friction: 1.0
            density: 0.1
            restitution: 0.0
        }

        QuasiBody {
            id: backboard

            bodyType: Quasi.StaticBodyType

            anchors.top: backboardHandler.top
            anchors.right: backboardHandler.right

            width: 4
            height: 203

            QuasiFixture {
                material: boardMaterial
                shape: Rectangle {
                    color: "white"
                    anchors.fill: parent
                }
            }
        }

        QuasiBody {
            id: basketHandler

            bodyType: Quasi.StaticBodyType

            anchors.left: backboard.right
            anchors.bottom: backboard.bottom
            anchors.bottomMargin: backboard.height * 0.2

            width: 20
            height: 8

            QuasiFixture {
                material: boardMaterial
                shape: Rectangle {
                    color: "white"
                    anchors.fill: parent
                }
            }
        }

        Image {
            id: basket
            anchors.left: basketHandler.right
            anchors.top: basketHandler.top
            z: 10
            source: ":/images/basket.png"
        }

        QuasiBody {
            id: basketRight

            bodyType: Quasi.StaticBodyType

            anchors.right: basket.right
            anchors.top: basket.top

            width: 4
            height: ball.height / 2

            QuasiFixture {
                material: boardMaterial
                shape: Item { anchors.fill: parent }
            }
        }

        QuasiBody {
            id: basketLeft

            bodyType: Quasi.StaticBodyType

            anchors.left: basket.left
            anchors.top: basket.top

            width: 4
            height: ball.height / 2

            QuasiFixture {
                material: boardMaterial
                shape: Item { anchors.fill: parent }
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

                shape: QuasiCircle { anchors.fill: parent }
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
                        && centerX < basketRight.x
                        && centerY > basketRight.y
                        && centerY < basketRight.y + basket.height) {

                    if (!scored && centerY < basketRight.y + (ball.height / 2)) {
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
