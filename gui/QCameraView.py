from PyQt5.QtWidgets import QLabel
from PyQt5.QtCore import Qt, pyqtSlot
from PyQt5.QtGui import QImage, QPixmap

from QRov.QCamera import QFlirCamera


class QCameraView(QLabel):
    def __init__(self, camera: QFlirCamera = None, parent=None):
        QLabel.__init__(self, parent)

        self.setAlignment(Qt.AlignCenter)

        self.__camera = camera

    def stop(self):
        if self.__camera is None:
            return

        self.__camera.stop()

    def play(self):
        if self.__camera is None:
            return

        self.__camera.stream()

    def setCamera(self, camera: QFlirCamera) -> None:
        self.__camera = camera
        self.__camera.imageAcquired.connect(self.setImage)

    @pyqtSlot(QImage)
    def setImage(self, img):
        self.setPixmap(QPixmap.fromImage(img).scaled(
            self.width(), self.height()))
