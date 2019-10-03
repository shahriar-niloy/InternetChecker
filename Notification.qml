import QtQuick 2.4
import QtGraphicalEffects 1.0

Rectangle {
    id: box
    color: "red"
    width: 500
    height: 200

    GaussianBlur {
        source: box
        anchors.fill: box
        radius: 5
        samples: 6
    }

}
