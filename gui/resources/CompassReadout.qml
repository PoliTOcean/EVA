import MyWidgets 1.0
import QtQuick 2.0

CompassReadout {
    id: self

    Rectangle {
        id: currentHeadingRectangle
        z:1
        color: "#000000"
        radius: 3
        border.width: 2
        border.color: "#2A82DA"
        width: parent.width
        height: parent.height

        Text {
            id: currentHeadingReadout
            color: "#ffffff"
            z:1
            text: self.text
            font.pixelSize: 12
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
        }
    }
}