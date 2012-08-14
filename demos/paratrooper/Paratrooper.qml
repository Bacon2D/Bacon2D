import QtQuick 1.1
import QuasiGame 1.0

QuasiEntity {
    id: trooperBody
    width: paratrooperImage.width
    height: paratrooperImage.height

    entityType: Quasi.DynamicType

    property variant explosionObj: null

    function explode() {
        paratrooperImage.visible = false
        explosionObj = explosionComponent.createObject(trooperBody)
        explosionObj.anchors.horizontalCenter = trooperBody.horizontalCenter
        explosionObj.anchors.bottom = trooperBody.bottom
    }

    function reset() {
        if (explosionObj)
            explosionObj.destroy()

        paratrooperImage.visible = true

        player.x = parent.width / 2 - player.width / 2
        player.y = 0
    }

    QuasiFixture {
        shape: paratrooperImage
        material: QuasiMaterial {
            friction: 0.3
            density: 6
            restitution: 0
        }
    }

    sleepingAllowed: true
    fixedRotation: true

    behavior: trooperBehavior

    property variant center: Qt.point(x + width / 2, y + height / 2)
    property bool isUpPressed: false
    property bool isDownPressed: false
    property bool isLeftPressed: false
    property bool isRightPressed: false

    property bool windReversed: Math.round(Math.random()) ? true : false
    property real playerImpulseFactor: windImpulseFactor + 0.08
    property real windImpulseFactor: minWindImpulseFactor
    property real maxWindImpulseFactor: 0.7
    property real minWindImpulseFactor: 0.4

    function move() {
        var impulse = Qt.point(0, 0)

        if (isUpPressed)
            impulse.y = -height * (playerImpulseFactor / 6)

        if (isDownPressed && useDownKey)
            impulse.y = height * (playerImpulseFactor / 6)

        if (isLeftPressed)
            impulse.x = -width * playerImpulseFactor

        if (isRightPressed)
            impulse.x = width * playerImpulseFactor

        applyLinearImpulse(impulse, center)
    }

    function applyWind() {
        var windImpulse = Qt.point(width * windImpulseFactor, 0)
        if (windReversed)
            windImpulse.x *= -1

        applyLinearImpulse(windImpulse, center)
    }

    QuasiScriptBehavior {
        id: trooperBehavior
        script: {
            applyWind()
            move()
        }
    }

    Rectangle {
        id: rect
        opacity: 0
        anchors.fill: parent
        color: "lightBlue"
        smooth: true
    }

    Image {
        id: paratrooperImage
        width: sourceSize.width / 2
        height: sourceSize.height / 2
        source: ":/paratrooper.png"
        smooth: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -1
    }

    Component {
        id: explosionComponent
        QuasiSprite {
            anchors.centerIn: parent
            animation: "explosion"

            animations: QuasiSpriteAnimation {
                name: "explosion"
                source: ":/explosion.png"
                frames: 5
                duration: 500
            }
        }
    }

    Keys.onUpPressed: isUpPressed = true
    Keys.onDownPressed: isDownPressed = true
    Keys.onLeftPressed: isLeftPressed = true
    Keys.onRightPressed: isRightPressed = true

    Keys.onReleased: {
        switch (event.key) {
        case Qt.Key_Up:
            isUpPressed = false
            break
        case Qt.Key_Down:
            isDownPressed = false
            break
        case Qt.Key_Left:
            isLeftPressed = false
            break
        case Qt.Key_Right:
            isRightPressed = false
            break
        }
    }

    Timer {
        id: windChangeTimer
        running: true
        interval: 3000 + Math.random() * 5000
        repeat: true
        onTriggered: windImpulseFactor = minWindImpulseFactor + (Math.random() * (maxWindImpulseFactor - minWindImpulseFactor))
    }
}

