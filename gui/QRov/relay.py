from PyQt5.QtCore import QObject
from PyQt5.QtWidgets import QPushButton, QSizePolicy


class QRelay(QObject):
    def __init__(self, name: str, enabled: bool, parent=None) -> None:
        QObject.__init__(self, parent)
        self.name = name
        self.enabled = enabled

        self.button = QPushButton()
        self.button.setText(self.name)
        self.button.setSizePolicy(QSizePolicy.Preferred, QSizePolicy.Expanding)

    def __repr__(self) -> str:
        return f"{self.name}: Enabled" if self.enabled else f"{self.name}: Disabled"

    def __str__(self) -> str:
        return self.__repr__()
