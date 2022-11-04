from PyQt5 import QtGui
from PyQt5.QtGui import QImage
import sys
import cv2
from PyQt5.QtCore import pyqtSignal, pyqtSlot, Qt, QThread
import numpy as np

from typing import Any, Tuple
from PyQt5.QtCore import QObject, QTimer, pyqtSignal
from PyQt5.QtGui import QImage

import struct
import cv2
import numpy as np
import socket

from . import QCamera


class QUdpCamera(QCamera):
    MAX_DGRAM = 2 ** 16
    MAX_IMAGE_DGRAM = MAX_DGRAM - 64

    def __init__(self, address: str = "127.0.0.1", port: int = None, fps: int = None, parent=None) -> None:
        QObject.__init__(self, parent)

        self.__socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.__address = address
        self.__port = port
        self.__fps = fps

        self.__streaming = False
        self.__cleaned = False

        self.__timer = QTimer()
        self.__timer.timeout.connect(self.__readImage)

        if self.port is not None:
            self.__socket.bind((self.__address, self.port))

    @property
    def port(self) -> int:
        return self.__port

    @port.setter
    def port(self, port) -> None:
        self.__port = port
        self.__socket.bind((self.__address, self.__port))

    @property
    def address(self) -> str:
        return self.__address.toString()

    @address.setter
    def address(self, addr: str) -> None:
        self.__address = addr

        if self.__port is not None:
            self.__socket.bind((self.__address, self.__port))

    @property
    def fps(self) -> int:
        return self.__fps

    @fps.setter
    def fps(self, fps) -> None:
        self.__fps = fps

        if self.__streaming:
            self.stop()
            self.stream()

    def close(self) -> None:
        self.__socket.close()

    def stop(self) -> None:
        if not self.__streaming:
            return

        self.__timer.stop()
        self.__streaming = False

    def stream(self):
        if self.__streaming:
            return

        self.__socket.settimeout(5 / self.__fps)
        self.__timer.start(1000 // self.__fps)
        self.__streaming = True

    def __readImage(self) -> None:
        data = b''
        i = 2
        try:
            if not self.__cleaned:
                self.__clean()

            while i > 1:
                i, seg = self.__read()
                data += seg

            frame = cv2.imdecode(np.frombuffer(data, dtype=np.uint8), 1)
            image = QImage(
                frame.data, frame.shape[1], frame.shape[0], QImage.Format_RGB888).rgbSwapped()

            self.imageAcquired.emit(image)

            self.connected.emit(True)
        except socket.timeout:
            self.connected.emit(False)

    def __read(self) -> Tuple[int, bytes]:
        seg, _ = self.__socket.recvfrom(self.MAX_DGRAM)

        return struct.unpack("B", seg[0:1])[0], seg[1:]

    def __clean(self) -> None:
        i = 2
        while i > 1:
            i, seg = self.__read()

        print("finish emptying buffer")
        self.__cleaned = True
