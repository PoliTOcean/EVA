import json
from PyQt5.QtCore import QObject, pyqtSignal, pyqtProperty, pyqtSlot
from PyQt5.QtGui import QImage

import yaml
from yamlinclude import YamlIncludeConstructor

import os
import sys
import typing

from .sensor import QSensor
from .component import QComponent, ComponentState
from .relay import QRelay
from .mqtt import QMQTTClient, MQTTStatus
from .joystick import QJoystick, QJoystickAxis, QJoystickButton
from .signals import QStateSignals, QLoggingSignals
from QRov import component


__CONFIG_FILENAME__ = "config.yaml"
__CONFIG_SENSORS_KEY__ = "sensors"
__CONFIG_RELAYS_KEY__ = "relays"
__CONFIG_COMPONENTS_KEY__ = "components"
__CONFIG_MQTT_KEY__ = "mqtt"
__CONFIG_JOYSTICK_KEY__ = "joystick"

axes = {} # axes -> {'X': 0, 'Y': 0, 'YAW': 0, 'PITCH': 0, 'Z_DOWN': 0, 'Z_UP': 0}


class QRovController(QObject):
    powerStateSignals = QStateSignals()
    cameraStateSignals = QStateSignals()
    cameraImageAcquired = pyqtSignal(QImage)
    loggingSignals = QLoggingSignals()

    def __init__(self, path: str, parent=None) -> None:
        QObject.__init__(self, parent=parent)
        self.__configured = False

        if not os.path.isdir(path):
            sys.exit("Config path must be a directory")

        configFilePath = os.path.join(path, __CONFIG_FILENAME__)
        if not os.path.isfile(configFilePath):
            sys.exit("Config directory must contain config.yaml")

        YamlIncludeConstructor.add_to_loader_class(
            loader_class=yaml.FullLoader, base_dir=path)

        with open(configFilePath, 'r') as configYaml:
            config = yaml.load(configYaml, Loader=yaml.FullLoader)

            self.__sensors = self.__init_sensors(
                config[__CONFIG_SENSORS_KEY__])
            self.__relays = self.__init_relays(config[__CONFIG_RELAYS_KEY__])
            self.__components = self.__init_components(
                config[__CONFIG_COMPONENTS_KEY__])
            self.__mqttClient = self.__init_mqttClient(
                config[__CONFIG_MQTT_KEY__])
            self.__joystick = self.__init_joystick(
                config[__CONFIG_JOYSTICK_KEY__])

            for axe in self.__joystick.commands['axes'].values():
                axes[axe] = 0
            
#            self.__init_camera()

            self.__configured = True

    def __init_sensors(self, config: typing.List[typing.Dict[str, str]]) -> typing.Dict[str, QSensor]:
        return {s['id']: QSensor(s['id'], s['name'], s['units']) for s in config}

    def __init_relays(self, config: typing.List[typing.Dict[str, str]]) -> typing.Dict[str, QRelay]:
        return {r['name']: QRelay(r['name'], False) for r in config}

    def __init_components(self, config: typing.List[str]) -> typing.Dict[str, QComponent]:
        components = {id: QComponent(id) for id in config}
        if "power" in components:
            components['power'].stateChanged.connect(
                self.__on_powerStateChanged)

        return components

    def __init_joystick(self, config: typing.Dict[str, typing.Dict[str, typing.Union[str, typing.Dict[str, str]]]]) -> QJoystick:
        joystick = QJoystick(config)
        joystick.signals.axisChanged.connect(self.__on_axisChanged)
        joystick.signals.buttonChanged.connect(self.__on_buttonChanged)

        return joystick

    def __init_mqttClient(self, config: typing.Dict[str, typing.Union[str, typing.Dict[str, str]]]) -> QMQTTClient:
        mqttClient = QMQTTClient(
            config['id'], config['address'], config['port'])
        mqttClient.statusChanged.connect(self.__on_mqttStatusChanged)
        mqttClient.loggingSignals.info.connect(self.loggingSignals.info.emit)
        mqttClient.loggingSignals.warn.connect(self.loggingSignals.warn.emit)
        mqttClient.loggingSignals.error.connect(self.loggingSignals.error.emit)

        mqttClient.connect()

        return mqttClient

    # def __init_camera(self):
    #     self.cameraThread = VideoThread()
    #     self.cameraThread.change_pixmap_signal.connect(self.__on_cameraImageAcquired)
    #     self.cameraThread.start()

    @property
    def configured(self) -> bool:
        return self.__configured

    @property
    def sensors(self) -> typing.Optional[typing.List[QSensor]]:
        return self.__sensors.values() if self.configured else None

    def sensor(self, id: str) -> typing.Optional[QSensor]:
        return self.__sensors[id] if id in self.__sensors.keys() else None

    @property
    def relays(self) -> typing.Optional[typing.List[QRelay]]:
        return self.__relays.values() if self.configured else None

    def relay(self, name: str) -> typing.Optional[QRelay]:
        return self.__relays[name] if name in self.__relays.keys() else None

    @property
    def components(self) -> typing.Optional[typing.List[QComponent]]:
        return self.__components.values() if self.configured else None

    def component(self, id: str) -> typing.Optional[QComponent]:
        return self.__components[id] if id in self.__components.keys() else None

    @property
    def mqttClient(self) -> typing.Optional[QMQTTClient]:
        return self.__mqttClient if self.configured else None

    @property
    def joystick(self) -> typing.Optional[QJoystick]:
        return self.__joystick if self.configured else None

    @pyqtSlot(QJoystickAxis)
    def __on_axisChanged(self, axis: QJoystickAxis) -> None:
        #data = {self.__joystick.commands['axes'][axis.id]: axis.value}
        axes[self.__joystick.commands['axes'][axis.id]] = axis.value

        self.__mqttClient.publish('axes/', json.dumps(axes))

    @pyqtSlot(QJoystickButton)
    def __on_buttonChanged(self, button: QJoystickButton) -> None:
        command = self.__joystick.commands['buttons'][button.id][
            'onPress'] if button.value else self.__joystick.commands['buttons'][button.id]['onRelease']
        if command:
            self.__mqttClient.publish('commands/', command)

    @pyqtSlot(int)
    def __on_mqttStatusChanged(self, status: int) -> None:
        if status == MQTTStatus.Connected:
            self.__mqttClient.subscribe(
                "sensors/", self.__on_mqttSensorMessage)
            self.__mqttClient.subscribe(
                "components/", self.__on_mqttComponentMessage)
        elif status == MQTTStatus.Disconected:
            self.__mqttClient.unsubscribe("sensors/")
            self.__mqttClient.unsubscribe("components/")

    @pyqtSlot(str)
    def __on_mqttComponentMessage(self, msg: str) -> None:
        j: typing.Dict[str, str] = json.loads(msg)

        for key, val in j.items():
            if key in self.__components.keys():
                self.__components[key].state = ComponentState.Enabled if val == 'Enabled' else ComponentState.Disabled

    @pyqtSlot(str)
    def __on_mqttSensorMessage(self, msg: str) -> None:
        j: typing.Dict[str, float] = json.loads(msg)

        for key, val in j.items():
            if key in self.__sensors:
                self.__sensors[key].value = val

    @pyqtSlot(ComponentState)
    def __on_powerStateChanged(self, state: ComponentState) -> None:
        if state == ComponentState.Enabled:
            self.powerStateSignals.enabled.emit()
        elif state == ComponentState.Disabled:
            self.powerStateSignals.disabled.emit()

    # @pyqtSlot(QImage)
    # def __on_cameraImageAcquired(self, image: QImage) -> None:
    #     self.cameraImageAcquired.emit(image)
