import QtQuick 2.0
import Bacon2D 1.0

/*
  This body places 2-pixel wide invisible static bodies around the screen,
  to avoid stuff getting out.
*/

Item {
    id: item

    transformOrigin: Item.TopLeft
    property alias body: itemBody

    // Body properties
    property alias world: itemBody.world
    property alias target: itemBody.target

    // Fixture properties
    property alias density: itemBody.density
    property alias friction: itemBody.friction
    property alias restitution: itemBody.restitution
    property alias sensor: itemBody.sensor
    property alias groupIndex: itemBody.groupIndex
    property alias categories: itemBody.categories
    property var _bounds: item.parent
    property variant fixtures: QtObject {
        property alias bottom: _bottom
        property alias top: _top
        property alias left: _left
        property alias right: _right
    }

    Body {
        id: itemBody
        bodyType: Body.Static
        target: item
        property real density
        property real friction
        property real restitution
        property bool sensor
        property int groupIndex: 1
        property int categories: Fixture.Category1
        
        signal beginContact(Fixture other)
        signal endContact(Fixture other)

        Box {
            id: _bottom
            x: _bounds.x
            y: _bounds.y + _bounds.height
            width: _bounds.width
            height: 2
            density: itemBody.density
            friction: itemBody.friction
            restitution: itemBody.restitution
            sensor: itemBody.sensor
            groupIndex: itemBody.groupIndex
            categories: itemBody.categories
        }
        Box {
            id: _top
            x: _bounds.x
            y: _bounds.y - height
            height: 2
            width: _bounds.width
            density: itemBody.density
            friction: itemBody.friction
            restitution: itemBody.restitution
            sensor: itemBody.sensor
            groupIndex: itemBody.groupIndex
            categories: itemBody.categories
        }
        Box {
            id: _left
            x: _bounds.x - width
            y: _bounds.y
            width: 2
            height: _bounds.height
            density: itemBody.density
            friction: itemBody.friction
            restitution: itemBody.restitution
            sensor: itemBody.sensor
            groupIndex: itemBody.groupIndex
            categories: itemBody.categories
        }
        Box {
            id: _right
            x: _bounds.x + _bounds.width
            y: _bounds.y
            width: 2
            height: _bounds.height
            density: itemBody.density
            friction: itemBody.friction
            restitution: itemBody.restitution
            sensor: itemBody.sensor
            groupIndex: itemBody.groupIndex
            categories: itemBody.categories
        }
    }
}
