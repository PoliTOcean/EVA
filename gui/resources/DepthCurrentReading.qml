import MyWidgets 1.0
import QtQuick 2.0

DepthCurrentReading {
    id: self

    width: 60
    height: 45

    Rectangle {
        z: 1
        width: parent.width
        height: parent.height
        color: "#000000"
        radius: 3
        border.width: 2
        border.color: "#2A82DA"

        Text {
            color: "#ffffff"
            z:1
            text: self.text
            //font.family: "Alfphabet"
            font.pixelSize: 12
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
        }
    }
}