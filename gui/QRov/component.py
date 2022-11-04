from PyQt5.QtCore import QObject, pyqtSignal, pyqtProperty

from typing import Optional
from enum import Enum


class ComponentState(Enum):
    Enabled = 0
    Disabled = 1
    Undefined = 2


class QComponent(QObject):
    stateChanged = pyqtSignal(ComponentState)

    def __init__(self, id: str, parent: Optional[QObject] = None) -> None:
        QObject.__init__(self, parent=parent)

        self.__id = id
        self.__state = ComponentState.Undefined

    @pyqtProperty(ComponentState, notify=stateChanged)
    def state(self) -> ComponentState:
        return self.__state

    @state.setter
    def state(self, state: ComponentState) -> None:
        self.__state = state
        self.stateChanged.emit(state)

    @pyqtProperty(str)
    def ID(self) -> str:
        return self.__id

    def toggle(self):
        if self.__state == ComponentState.Disabled:
            self.state = ComponentState.Enabled
        elif self.__state == ComponentState.Enabled:
            self.state = ComponentState.Disabled
