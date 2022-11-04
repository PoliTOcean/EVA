from PyQt5.QtCore import QObject, pyqtSignal


class QStateSignals(QObject):
    enabled = pyqtSignal()
    disabled = pyqtSignal()


class QLoggingSignals(QObject):
    info = pyqtSignal(str)
    warn = pyqtSignal(str)
    error = pyqtSignal(str)
