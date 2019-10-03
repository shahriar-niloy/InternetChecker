import QtQuick 2.4
import QtGraphicalEffects 1.0

Item {
    width: 400
    height: 200

    Rectangle {
        id: box
        x: 73
        y: 150
        width: 255
        height: 100
        color: "#8c94d3"
        opacity: 1
        antialiasing: true
        border.width: 0
        border.color: "#ffffff"
    }
    FastBlur {
        id: fastBlur1
        anchors.fill: box
        source: box
        radius: 5
        cached: false
        antialiasing: true
        transparentBorder: false
    }
}
