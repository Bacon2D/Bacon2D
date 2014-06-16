import QtQuick 2.2
import QtQuick.Controls 1.1
import Bacon2D 1.0
import QtMultimedia 5.0

Game {
    id: game
    width: 800
    height: 600
    currentScene: scene

    Component {
        id: link
        Entity {
            width: 20
            height: 20
            x: 400
            bodyType: Entity.Dynamic
            fixtures: Circle {
                radius: 10
                anchors.centerIn: parent
                friction: 0.9
                density: 0.8
            }
            Rectangle {
                anchors.fill: parent
                color: "orange"
                radius: 10
            }
        }

    }

    Component {
        id: linkJoint
        RevoluteJoint {
            localAnchorA: Qt.point(10, 30)
            localAnchorB: Qt.point(10, 5)
            collideConnected: true
        }
    }

    Component {
        id: ball
        Entity {
            width: 10
            height: 10
            bullet: true
            bodyType: Entity.Dynamic
            fixtures: Circle {
                radius: 5
                density: 0.9
                friction: 0.9
                restitution: 0.2
            }
            Rectangle {
                anchors.centerIn: parent
                radius: 5
                width: 10
                height: 10
                color: "black"
                smooth: true
            }
        }
    }

    Component {
        id: dominoComponent
        Entity {
            width: 10
            height:50
            x: 0
            y: 510
            bodyType: Entity.Dynamic
            fixtures: Box {
                anchors.fill: parent
                density: 1
                friction: 0.3
                restitution: 0.5
            }

            Rectangle {
                anchors.fill: parent
                color: "black"
            }
        }
    }

    Scene {
        id: scene
        anchors.fill: parent
        physics: true

        onInitialized: {
            createDominos();
            createChain();
        }

        function createDominos() {
            for(var i = 0;i < 5;i ++) {
                var newDomino = dominoComponent.createObject(scene.world);
                newDomino.x = 500 + 50 * i;
                newDomino.y = 510
            }
            for(i = 0;i < 4;i ++) {
                newDomino = dominoComponent.createObject(scene.world);
                newDomino.x = 555 + 50 * i;
                newDomino.y = 500
                newDomino.rotation = 90;
            }
            for(var i = 0;i < 4;i ++) {
                newDomino = dominoComponent.createObject(scene.world);
                newDomino.x = 525 + 50 * i;
                newDomino.y = 450
            }
            for(i = 0;i < 3;i ++) {
                newDomino = dominoComponent.createObject(scene.world);
                newDomino.x = 580 + 50 * i;
                newDomino.y = 440
                newDomino.rotation = 90;
            }
        }

        function createChain()
        {
            var prev = chainAnchor;
            for(var i = 0;i < 12;i ++)
            {
                var y = 300 + i * 20 - 5;
                var newLink = link.createObject(scene.world);
                newLink.y = y;
                var newJoint = linkJoint.createObject(scene.world);
                newJoint.bodyA = prev;
                newJoint.bodyB = newLink;
                prev = newLink;
            }
        }

        Entity {
            id: ground
            height: 40
            bodyType: Entity.Static
            anchors {
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
            fixtures: Box {
                anchors.fill: parent
                friction: 1
                density: 1
            }
            Rectangle {
                anchors.fill: parent
                color: "#DEDEDE"
            }
        }

        Wall {
            id: topWall
            height: 40
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
            }
        }

        Wall {
            id: leftWall
            width: 40
            anchors {
                left: parent.left
                top: parent.top
                bottom: parent.bottom
                bottomMargin: 40
            }
        }

        Wall {
            id: rightWall
            width: 40
            anchors {
                right: parent.right
                top: parent.top
                bottom: parent.bottom
                bottomMargin: 40
            }

        }

        Entity {
            id: canon
            bodyType: Entity.Dynamic
            width: 98
            height: 37
            x: 150
            y: 443
            fixtures: Box {
                id: canonFixtire
                anchors.fill: parent
                density: 0.5
            }
            Image {
                source: "images/cannon.png"
                anchors.fill: parent
            }
        }

        Entity {
            id: canonBase
            bodyType: Entity.Static
            width: 130
            height: 67
            x: 50
            y: 493
            fixtures: Box {
                anchors.fill: parent
                density: 0.5
            }
            Image {
                source: "images/cannon_base.png"
                anchors.fill: parent
            }
        }

        RevoluteJoint {
            id: joint
            bodyA: canonBase
            bodyB: canon
            localAnchorA: Qt.point(75, 18)
            localAnchorB: Qt.point(36, 19)
            collideConnected: false
            motorSpeed: 0
            enableMotor: false
            maxMotorTorque: 100
            enableLimit: true
            lowerAngle: 0
            upperAngle: -60
        }

        Entity {
            id: chainAnchor
            width: 20
            height: 20
            x: 400
            y: 230
            bodyType: Entity.Static
            Rectangle {
                anchors.fill: parent
                color: "black"
            }
        }

        Rectangle {
            id: debugButton
            x: 50
            y: 50
            width: 120
            height: 30
            Text {
                id: debugButtonText
                text: scene.debug ? "Debug view: on" : "Debug view: off"
                anchors.centerIn: parent
            }
            color: "#DEDEDE"
            border.color: "#999"
            radius: 5
            MouseArea {
                anchors.fill: parent
                onClicked: scene.debug = !scene.debug;
            }
        }

        Rectangle {
            id: upButton
            x: 50
            y: 90
            width: 50
            height: 50
            Text {
                id: upButtonText
                text: "up"
                anchors.centerIn: parent
            }
            color: "#DEDEDE"
            border.color: "#999"
            radius: 5
            MouseArea {
                acceptedButtons: Qt.LeftButton
                anchors.fill: parent
                onPressed: {
                    canonFixtire.density = 0.5;
                    joint.motorSpeed = -15;
                    joint.enableMotor = true;
                    upButton.color = "#AAA";
                    gearSound.play();
                }
                onReleased: {
                    joint.motorSpeed = 0;
                    upButton.color = "#DEDEDE";
                    gearSound.stop()
                }
            }
        }

        Rectangle {
            id: downButton
            x: 110
            y: 90
            width: 50
            height: 50
            Text {
                id: downButtonText
                text: "down"
                anchors.centerIn: parent
            }
            color: "#DEDEDE"
            border.color: "#999"
            radius: 5
            MouseArea {
                acceptedButtons: Qt.LeftButton
                anchors.fill: parent
                onPressed: {
                    joint.motorSpeed = 15;
                    joint.enableMotor = true;
                    downButton.color = "#AAA";
                    gearSound.play();
                }
                onReleased: {
                    joint.motorSpeed = 0;
                    downButton.color = "#DEDEDE";
                    gearSound.stop();
                }
            }
        }

        Rectangle {
            id: shotButton
            x: 170
            y: 90
            width: 50
            height: 50

            Text {
                id: shotButtonText
                text: "shoot!"
                anchors.centerIn: parent
            }
            color: "#DEDEDE"
            border.color: "#999"
            radius: 5
            MouseArea {
                acceptedButtons: Qt.LeftButton
                anchors.fill: parent
                onClicked: {
                    var angle = Math.abs(joint.getJointAngle());
                    var offsetX = 65 * Math.cos(angle * Math.PI / 180);
                    var offsetY = 65 * Math.sin(angle * Math.PI / 180);
                    var newBall = ball.createObject(scene.world);
                    newBall.x = 125 + offsetX;
                    newBall.y = 500 - offsetY;
                    var impulse = power.value;
                    var impulseX = impulse * Math.cos(angle * Math.PI / 180);
                    var impulseY = impulse * Math.sin(angle * Math.PI / 180);
                    newBall.applyLinearImpulse(Qt.point(impulseX,-impulseY),newBall.getWorldCenter());
                    shotSound.play();
                }
            }
        }

        Slider {
            id: power
            minimumValue: 0.01
            maximumValue: 5
            value: 3
            width: 200
            height: 30
            x: 230
            y: 100
        }

        SoundEffect {
            id: shotSound
            source: "sounds/cannon.wav"
        }
        SoundEffect {
            id: gearSound
            source: "sounds/gear.wav"
        }
    }
}
