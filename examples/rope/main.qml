import QtQuick 2.2
import Bacon2D 1.0
import QtQuick.Controls 1.1

Game {
    id: game
    width: 800
    height: 600
    currentScene: scene

    Slider {
        id: lengthSlider
        x: 180
        y: 50
        width: 100
        height: 50
        maximumValue: 50
        minimumValue: 20
        value: 30
    }

    Component {
        id: linkComponent
        Entity {
            width: 20
            height:20
            sleepingAllowed: true
			bodyType: Entity.Dynamic;
            property color color: "#EFEFEF"
            fixtures: Circle {
                radius: parent.width / 2
                anchors.centerIn: parent
                density: 0.5
            }
            Rectangle {
                radius: parent.width / 2
                border.color: "blue"
                color: parent.color
                width: parent.width
                height: parent.height
                smooth: true
            }
        }
    }

    Component {
        id: jointComponent
        RopeJoint {
            localAnchorA: Qt.point(10,10)
            localAnchorB: Qt.point(10,10)
            maxLength: lengthSlider.value
            collideConnected: true
        }
    }

    Scene {
        id: scene
        anchors.fill: parent
        physics: true

        onInitialized: {
            var prev = leftWall;
            for(var i = 60;i < 740;i += 20) {
                var newLink = linkComponent.createObject(scene.world);
                newLink.color = "orange";
                newLink.x = i;
                newLink.y = 100;
                var newJoint = jointComponent.createObject(scene.world);
                if(i === 60) newJoint.localAnchorA = Qt.point(40,100);
                newJoint.bodyA = prev;
                newJoint.bodyB = newLink;
                prev = newLink;
            }
            newJoint = jointComponent.createObject(scene.world);
            newJoint.localAnchorB = Qt.point(0,100);
            newJoint.bodyA = prev;
            newJoint.bodyB = rightWall;
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

        Rectangle {
            id: debugButton
            x: 50
            y: 50
            width: 120
            height: 30
            Text {
                id: debugButtonText
                text: "Debug view: " + (debugDraw.visible ? "on" : "off")
                anchors.centerIn: parent
            }
            color: "#DEDEDE"
            border.color: "#999"
            radius: 5
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    debugDraw.visible = !debugDraw.visible;
                    debugButtonText.text = debugDraw.visible ? "Debug view: on" : "Debug view: off";
                }
            }
        }

        DebugDraw {
            id: debugDraw
            anchors.fill: parent
            world: scene.world
            opacity: 1
            visible: false
        }

        Timer {
            id: ballsTimer
            interval: 500
            running: true
            repeat: true
            onTriggered: {
                var newBox = linkComponent.createObject(scene.world);
                newBox.x = 40 + (Math.random() * scene.width - 80);
                newBox.y = 50;
            }
        }
    }
}
