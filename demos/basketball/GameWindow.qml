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

    width: 1200
    height: 900

    currentScene: scene

    QuasiPhysicsScene {
        id: scene

        width: parent.width
        height: parent.height

        gravity: Qt.point(0, -20.0)

        QuasiBody {
            id: ball
            property int centerX: x + (width / 2)
            property int centerY: y + (height / 2)
            property bool threw: false

            width: 80
            height: 80

            friction: 0.3
            density: 50
            restitution: 0.6
            sleepingAllowed: false

            shapeGeometry: Quasi.CircleBodyShape

            x: parent.width - width
            y: parent.height - height

            Rectangle {
                id: ball01
                anchors.fill: parent
                radius: width / 2
                color: "red"
            }

            onYChanged: {
                if (!threw)
                    return;
                if (centerX > baskethandler.x + baskethandler.width
                        && centerX < basket.x
                        && centerY < basket.y + (ball.height / 2)
                        && centerY > basket.y) {
                    score++;
                    threw = false;
                    console.log("score = " + score);
                }
            }
        }

        QuasiBody {
            id: backboard

            bodyType: Quasi.StaticBodyType

            x: 0
            y: 100

            width: 4
            height: 200

            friction: 1.0
            density: 0.1
            restitution: 0.0

            Rectangle {
                color: "black"
                anchors.fill: parent
            }
        }

        QuasiBody {
            id: baskethandler

            bodyType: Quasi.StaticBodyType

            x: backboard.x + backboard.width
            y: backboard.y + backboard.height

            width: 30
            height: 4

            friction: 1.0
            density: 0.1
            restitution: 0.0

            Rectangle {
                color: "black"
                anchors.fill: parent
            }
        }

        QuasiBody {
            id: basket

            bodyType: Quasi.StaticBodyType

            x: baskethandler.x + baskethandler.width + ball.width + 10
            y: baskethandler.y

            width: 4
            height: 4

            friction: 1.0
            density: 0.1
            restitution: 0.0

            Rectangle {
                color: "black"
                anchors.fill: parent
            }
        }

        QuasiBody {
            id: ground

            bodyType: Quasi.StaticBodyType

            x: 0
            y: parent.height - 10

            width: parent.width
            height: 1

            friction: 0.3
            density: 5
            restitution: 0.6

            Rectangle {
                color: "green"
                anchors.fill: parent
            }
        }

        MouseArea {
            anchors.fill: parent

            onClicked: {

                if (ball.centerX > parent.width - ball.width
                        && ball.centerX < parent.width
                        && ball.centerY > parent.height - ball.height) {
                    var xLaunch = 800 * (game.mouse.x - ball.centerX);
                    var yLaunch = 800 * (game.mouse.y - ball.centerY);

                    ball.applyLinearImpulse(Qt.point(xLaunch, yLaunch), Qt.point(ball.centerX, ball.centerY));
                    ball.threw = true;
                } else {
                    ball.setLinearVelocity(Qt.point(0, 0));
                    ball.x = parent.width - ball.width;
                    ball.y = parent.height - ball.height;
                    ball.threw = false;
                }
            }
        }
    }
}
