from PyQt5.QtCore import Qt, QUrl, pyqtProperty, pyqtSlot
from PyQt5.QtWidgets import QWidget
from PyQt5.QtQuick import QQuickView


class QLedIndicator(QWidget):
    def __init__(self, title: str, parent=None) -> None:
        QWidget.__init__(self, parent)

        self.viewer = QQuickView()
        self.viewer.setSource(QUrl("resources/LedIndicator.qml"))
        self.viewer.setResizeMode(QQuickView.SizeRootObjectToView)

        self.container = QWidget.createWindowContainer(self.viewer)
        self.container.setFocusPolicy(Qt.TabFocus)

        self.title = title

        self.refreshPalette()

    @pyqtProperty(str)
    def title(self) -> None:
        return self.viewer.rootObject().property("indicatorTitle")

    @title.setter
    def title(self, title: str) -> None:
        self.viewer.rootObject().setProperty("indicatorTitle", title)

    @pyqtProperty(bool)
    def status(self) -> bool:
        return self.viewer.rootObject().property("isStatusOn")

    @status.setter
    def status(self, on: bool) -> None:
        self.viewer.rootObject().setProperty("isStatusOn", on)

    @pyqtSlot()
    def enable(self) -> None:
        self.status = True

    @pyqtSlot()
    def disable(self) -> None:
        self.status = False

    def refreshPalette(self) -> None:
        p = self.palette()

        self.viewer.setColor(p.window().color())
        self.viewer.rootObject().setProperty("textColor", p.text().color())
        self.viewer.rootObject().setProperty("borderColor", p.text().color())

        backgroundColor = p.highlight().color()
        backgroundColor.setAlpha(90)
        self.viewer.rootObject().setProperty("backgroundColor", backgroundColor)

        titleColor = p.highlight().color()
        self.viewer.rootObject().setProperty("titleColor", titleColor)
