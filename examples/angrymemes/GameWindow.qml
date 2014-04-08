import QtQuick 2.0
import Bacon2D 1.0

Game {
    id: game
    width: 2048
    height: 800
    currentScene: scene
    property int initialPos: 1500

    Scene {
        id: scene
        width: 2048
        height: 800
        Image {
            id: background
            source: "qrc:/images/background.png"
        }

        TrollFace {
            id: projectile
            x: parent.width * 0.1
            y: parent.height * 0.8
        }

        Entity {
            id: ground
            anchors.bottom: parent.bottom
            entityType: Bacon2D.StaticType
            sleepingAllowed: false
            width: scene.width
            height: 20

            Fixture {
                material: Material {
                    friction: 0.3
                    density: 50
                    restitution: 0.35
                }
                shape: Box {
                    anchors.fill: parent
                    fill: ColorFill {
                        brushColor: "brown"
                    }
                }
            }
        }

        Wood {
            id: wood01
            x: initialPos
            y: ground.y - height
            width: 15
            height: 110            
        }

        Enemy {
            id: enemy01
            x: initialPos + wood01.width + 10
            y: ground.y - height                
        }

        Wood {
            id: wood02
            x: initialPos + wood01.width + enemy01.width + 20
            y: ground.y - height
            width: 15
            height: 110            
        }
        Wood {
            id: wood011
            x: initialPos + 55
            y: ground.y - (1.6 * height)
            width: 15
            height: 110
            rotation: 90            
        }

        Wood {
            id: wood022
            x: initialPos + 175
            y: ground.y - (1.6 * height)
            width: 15
            height: 110
            rotation: 90
        }

        Enemy {
            id: enemy02
            x: initialPos + wood01.width + enemy01.width + wood02.width + 30
            y: ground.y - height            
        }

        Wood {
            id: wood03
            x: initialPos + wood01.width + enemy01.width + wood02.width + enemy02.width + 40
            y: ground.y - height
            width: 15
            height: 110            
        }

        Wood {
            id: wood04
            x: initialPos + 60
            y: 500
            width: 15
            height: 110            
        }

        Wood {
            id: wood044
            x: initialPos + 115
            y: 430
            width: 15
            height: 110
            rotation: 90            
        }

        Enemy {
            id: enemy03
            x: initialPos + wood04.width + 60
            y: ground.y - height - 300        
        }

        Wood {
            id: wood05
            x: initialPos + wood04.width + enemy03.width + 70
            y: 500
            width: 15
            height: 110            
        }

        // forever alone
        Wood {
            id: woodf
            x: initialPos + 400
            y: ground.y - height
            width: 15
            height: 110            
        }

        Enemy {
            id: enemyf
            x: initialPos + 400 + woodf.width + 10
            y: ground.y - height            
        }

        Wood {
            id: woodf2
            x: initialPos + 400 + woodf.width + enemyf.width + 10
            y: ground.y - height
            width: 15
            height: 110            
        }

        Wood {
            id: woodff
            x: initialPos + 450
            y: ground.y - (1.6 * height)
            width: 15
            height: 110
            rotation: 90            
        }
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            var xLaunch = 800 * (game.mouse.x - projectile.x);
            var yLaunch = 800 * (game.mouse.y - projectile.y);

            xLaunch = xLaunch > 150000 ? 150000 : xLaunch
            yLaunch = yLaunch < -150000 ? -150000 : yLaunch

            print (xLaunch, yLaunch)

            projectile.applyLinearImpulse(Qt.point(xLaunch, yLaunch),
                                          Qt.point(projectile.x + projectile.width / 2.0, projectile.y + projectile.height / 2.0)) // XXX expose b2pos

        }
    }
}
