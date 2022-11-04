from enum import Enum
from PyQt5.QtQml import qmlRegisterType

from QDepthTape import QDepthTick, QDepthCurrentReading
from QCompass import QCompassTick, QCompassReadout
qmlRegisterType(QDepthTick, 'MyWidgets', 1, 0, 'DepthTick')
qmlRegisterType(QDepthCurrentReading, 'MyWidgets', 1, 0, 'DepthCurrentReading')
qmlRegisterType(QCompassTick, 'MyWidgets', 1, 0, 'CompassTick')
qmlRegisterType(QCompassReadout, 'MyWidgets', 1, 0, 'CompassReadout')


class Message(Enum):
    INFO = 0
    GOOD = 1
    WARN = 2
    ERROR = 3
