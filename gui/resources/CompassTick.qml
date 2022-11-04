import MyWidgets 1.0
import QtQuick 2.0

CompassTick {
    id: self

    width: 2
    height: 12

    property int paintedWidth: headingText.contentWidth;

    Rectangle {
        id: headingBar
        width: parent.width
        height: parent.height
        color: "#2A82DA"

        Text {
            id: headingText
            color: "#2A82DA"
            text: self.text
            font.pixelSize: 12
            y: -1 * headingText.paintedHeight - 1
            x: -1 * headingText.paintedWidth/2

        }
    }
}