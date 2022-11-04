import custom_types as t

from datetime import datetime

from PyQt5.QtCore import QObject, QTime, pyqtSlot
from PyQt5.QtWidgets import QTextEdit
from PyQt5.QtGui import QTextCursor


class QActivityMonitor(QObject):
    def __init__(self, textEdit: QTextEdit, parent=None) -> None:
        super(QObject, self).__init__(parent)
        self.__textEdit = textEdit
        self.autoscroll = True

    def display(self, type: t.Message, msg: str):
        time = datetime.now().strftime("%H:%M:%S")
        msg = f"({time}) {type.name}: {msg}"

        self.__textEdit.append(msg)
        if (self.autoscroll):
            cursor = self.__textEdit.textCursor()
            cursor.movePosition(QTextCursor.End)
            self.__textEdit.setTextCursor(cursor)

    @pyqtSlot(str)
    def displayInfo(self, msg: str):
        self.display(t.Message.INFO, msg)

    @pyqtSlot(str)
    def displayWarn(self, msg: str):
        self.display(t.Message.WARN, msg)

    @pyqtSlot(str)
    def displayError(self, msg: str):
        self.display(t.Message.ERROR, msg)

    def clear(self):
        self.__textEdit.clear()
