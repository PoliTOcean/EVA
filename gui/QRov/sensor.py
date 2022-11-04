from PyQt5.QtCore import Qt, QObject, pyqtSignal, pyqtSlot, pyqtProperty


class QSensor(QObject):
    updated = pyqtSignal(float)

    def __init__(self, id: str, name: str, units: str) -> None:
        QObject.__init__(self)

        self.__id = id
        self.__name = name
        self.__value = 0
        self.__units = units

    @pyqtProperty(float, notify=updated)
    def value(self):
        return self.__value

    @value.setter
    def value(self, value: float):
        self.__value = value
        self.updated.emit(value)

    @pyqtProperty(str)
    def name(self):
        return self.__name

    @pyqtProperty(str)
    def id(self):
        return self.__id

    @pyqtProperty(str)
    def units(self):
        return self.__units

    def __repr__(self) -> str:
        return f"{self.name}: {self.value} {self.units}"

    def __str__(self) -> str:
        return self.__repr__()
