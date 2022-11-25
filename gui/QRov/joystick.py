import json
import sdl2
import sdl2.ext
import time

import os

from PyQt5.QtCore import QObject, QTimer, pyqtSignal, pyqtSlot, pyqtProperty


class QJoystickElement(QObject):
    def __init__(self, id, value, parent=None) -> None:
        QObject.__init__(self, parent)

        self.id = id
        self.value = value


class QJoystickAxis(QJoystickElement):
    def __init__(self, id, value, parent=None) -> None:
        super().__init__(id, value, parent=parent)


class QJoystickButton(QJoystickElement):
    def __init__(self, id, value, parent=None) -> None:
        super().__init__(id, value, parent=parent)


class JoystickSignals(QObject):
    connected = pyqtSignal()
    disconnected = pyqtSignal()
    axisChanged = pyqtSignal(QJoystickAxis)
    buttonChanged = pyqtSignal(QJoystickButton)


class QJoystick(QObject):
    __location__ = os.path.realpath(
        os.path.join(os.getcwd(), os.path.dirname(__file__)))

    signals = JoystickSignals()

    def __init__(self, commands, parent=None) -> None:
        QObject.__init__(self, parent)

        self.__timer = QTimer()
        self.__timer.timeout.connect(self.__update)
        self.__timer.start(10)

        self.__commands = commands

        sdl2.SDL_Init(sdl2.SDL_INIT_JOYSTICK)

    @property
    def name(self):
        return sdl2.SDL_JoystickName(self.__joystick).decode('utf8')

    @property
    def commands(self):
        return self.__commands

    def __open(self):
        self.__joystick = sdl2.SDL_JoystickOpen(0)
        print("Loading mappings")
        with open(os.path.join(self.__location__, "mappings/XboxOneController.json")) as jmaps:
            mappings = json.load(jmaps)

            if self.name in mappings:
                self.__mapping = mappings[self.name]

    def __close(self):
        sdl2.SDL_JoystickClose(self.__joystick)

    def __update(self):
        for event in sdl2.ext.get_events():
            
            if event.type == sdl2.SDL_JOYAXISMOTION:
                self.signals.axisChanged.emit(QJoystickAxis(
                    self.__mapping['axes'][event.jaxis.axis], event.jaxis.value))
            elif event.type == sdl2.SDL_JOYBUTTONDOWN:
                self.signals.buttonChanged.emit(QJoystickButton(
                    self.__mapping['buttons'][event.jbutton.button], event.jbutton.state))
            elif event.type == sdl2.SDL_JOYBUTTONUP:
                self.signals.buttonChanged.emit(QJoystickButton(
                    self.__mapping['buttons'][event.jbutton.button], event.jbutton.state))
            elif event.type == sdl2.SDL_JOYDEVICEADDED:
                self.__open()
                self.signals.connected.emit()
            elif event.type == sdl2.SDL_JOYDEVICEREMOVED:
                self.__close()
                self.signals.disconnected.emit()

            print(self.__mapping['axes'][event.jaxis.axis], event.jaxis.value)
            # wait before read another event
            time.sleep(0.05)
            #clear the current events queue
            sdl2.ext.get_events().clear()

    def __del__(self):
        self.__close()
