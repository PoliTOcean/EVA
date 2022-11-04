import sys

from PyQt5.QtCore import Qt, QUrl, pyqtProperty, pyqtSignal, pyqtSlot
from PyQt5.QtGui import QColor
from PyQt5.QtQml import QQmlApplicationEngine, QQmlComponent, QQmlProperty
from PyQt5.QtQuick import QQuickItem, QQuickView
from PyQt5.QtWidgets import QApplication, QWidget


class QCompass(QWidget):
    heightChanged = pyqtSignal()

    def __init__(self, parent=None) -> None:
        QWidget.__init__(self, parent)

        self.tickList = []
        self.lastHeading = 0

        self.viewer = QQuickView()
        self.container = QWidget.createWindowContainer(self.viewer)
        self.container.setMinimumSize(100, 35)
        self.container.setMaximumHeight(35)
        self.container.setFocusPolicy(Qt.TabFocus)
        self.viewer.setColor(QColor(53, 53, 53))

        self.viewer.setSource(QUrl("resources/Compass.qml"))
        self.viewer.setResizeMode(QQuickView.SizeRootObjectToView)

        self.__initTicks()
        self.viewer.heightChanged.connect(self.resetGraphics)
        self.viewer.widthChanged.connect(self.resetGraphics)

        self.container.show()

    def show(self) -> None:
        return self.container.show()

    @pyqtSlot(int)
    def updateHeading(self, heading: int):
        self.readoutItem.text = str(heading)

        change = heading * 10
        for tickItem in self.tickList:
            tickItem.setX(tickItem.x() - change)

        self.lastHeading = heading

    def resetGraphics(self) -> None:
        self.readoutItem.setX(self.viewer.width()/2 -
                              self.readoutItem.width()/2)
        self.readoutItem.setY(self.viewer.height() -
                              self.readoutItem.height() + 5)

        multiplier = 100
        numberOfExtraTicksPerSide = self.viewer.width() // multiplier
        indexOfZeroTick = numberOfExtraTicksPerSide + 1

        for i, tickItem in enumerate(self.tickList, start=0):
            tickItem.setY(self.viewer.height() - tickItem.height())
            tickItem.setX(self.viewer.width()/2 - tickItem.width() /
                          2 + multiplier * (i - indexOfZeroTick))

            if i == indexOfZeroTick:
                tickItem.text = "N"
            elif i > indexOfZeroTick and i <= indexOfZeroTick + 35:
                tickItem.setHeading((i - indexOfZeroTick) * 10)
            elif i > indexOfZeroTick and i > indexOfZeroTick + 35:
                tickItem.setHeading((i - (indexOfZeroTick + 36)) * 10)
            elif i < indexOfZeroTick:
                tickItem.setHeading((36 - (indexOfZeroTick - i)) * 10)

        self.updateHeading(self.lastHeading)

    def __initTicks(self) -> None:
        self.numberOfTicks = 36

        self.readoutComponent = QQmlComponent(
            self.viewer.engine(), QUrl("resources/CompassReadout.qml"))
        self.readoutItem = self.readoutComponent.create()
        self.readoutItem.setParentItem(self.viewer.rootObject())

        self.readoutItem.setWidth(50)
        self.readoutItem.setHeight(30)
        self.readoutItem.setZ(5)

        for _ in range(self.numberOfTicks):
            tickComponent = QQmlComponent(
                self.viewer.engine(), QUrl("resources/CompassTick.qml"))
            tickItem = tickComponent.create()
            tickItem.setParentItem(self.viewer.rootObject())

            self.tickList.append(tickItem)

        self.resetGraphics()


class QCompassTick(QQuickItem):
    textChanged = pyqtSignal(str)

    def __init__(self, parent=None):
        QQuickItem.__init__(self, parent)
        self._text = "N"

    @pyqtProperty(str, notify=textChanged)
    def text(self):
        return self._text

    @text.setter
    def text(self, text):
        self._text = text
        self.textChanged.emit(text)

    def setHeading(self, tick):
        heading = str(tick)
        if tick == 0:
            heading = "N"
        elif tick == 90:
            heading = "E"
        elif tick == 180:
            heading = "S"
        elif tick == 270:
            heading = "W"

        self.text = heading


class QCompassReadout(QQuickItem):
    textChanged = pyqtSignal(str)

    def __init__(self, parent=None):
        QQuickItem.__init__(self, parent)
        self._text = "0"

    @pyqtProperty(str, notify=textChanged)
    def text(self):
        return self._text

    @text.setter
    def text(self, text):
        self._text = text
        self.textChanged.emit(text)
