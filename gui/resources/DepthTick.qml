import MyWidgets 1.0
import QtQuick 2.0

DepthTick {
    id: self

    width: 72
    height: 2

    property int textX: depthText.x

    Rectangle {
        width: parent.width
        height: parent.height
        color: "#2a82da"

        Text {
            id: depthText
            color: "#2a82da"
            text: self.text
            font.pixelSize: 12
            y: -1 * depthText.paintedHeight / 2;
            x: -1 * depthText.paintedWidth - 4;
        }
    }
}