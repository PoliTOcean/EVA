from typing import Callable
from PyQt5.QtCore import QObject, pyqtSignal, pyqtSlot, pyqtProperty
from .signals import QLoggingSignals

import paho.mqtt.client as mqtt


class MQTTStatus(QObject):
    Disconected = 0
    Connecting = 1
    Connected = 2


class QMQTTClient(QObject):
    MQTTv31 = mqtt.MQTTv31
    MQTTv311 = mqtt.MQTTv311
    MQTTv5 = mqtt.MQTTv5

    connected = pyqtSignal()
    disconnected = pyqtSignal()
    messageArrived = pyqtSignal(str)
    statusChanged = pyqtSignal(int)
    hostnameChanged = pyqtSignal(str)
    portChanged = pyqtSignal(int)
    keepAliveChanged = pyqtSignal(int)
    cleanSessionChanged = pyqtSignal(bool)
    protocolVersionChanged = pyqtSignal(int)

    loggingSignals = QLoggingSignals()

    def __init__(self, client_id, hostname="localhost", port=1883, parent=None) -> None:
        QObject.__init__(self, parent)

        self.__hostname = hostname
        self.__port = port
        self.__keepAlive = 60
        self.__cleanSession = False
        self.__protocolVersion = self.MQTTv311
        self.__status = MQTTStatus.Disconected
        self.__callbacks = {}

        self.__client = mqtt.Client(client_id=client_id,
                                    clean_session=self.__cleanSession, protocol=self.__protocolVersion)
        self.__client.on_connect = self.__on_connect
        self.__client.on_message = self.__on_message
        self.__client.on_disconnect = self.__on_disconnect

    @pyqtProperty(int, notify=statusChanged)
    def status(self) -> int:
        return self.__status

    @status.setter
    def status(self, status: int) -> None:
        if self.__status == status:
            return

        self.__status = status
        self.statusChanged.emit(status)

    @pyqtProperty(str, notify=hostnameChanged)
    def hostname(self) -> str:
        return self.__hostname

    @hostname.setter
    def hostname(self, hostname: str) -> None:
        if self.__hostname == hostname:
            return

        self.__hostname = hostname
        self.hostnameChanged.emit(hostname)

    @pyqtProperty(int, notify=portChanged)
    def port(self) -> int:
        return self.__port

    @port.setter
    def port(self, port: int) -> None:
        if self.__port == port:
            return

        self.__port = port
        self.portChanged.emit(port)

    @pyqtProperty(int, notify=keepAliveChanged)
    def keepAlive(self) -> int:
        return self.__keepAlive

    @keepAlive.setter
    def keepAlive(self, keepAlive: int) -> None:
        if self.__keepAlive == keepAlive:
            return

        self.__keepAlive = keepAlive
        self.keepAliveChanged.emit(keepAlive)

    @pyqtProperty(bool, notify=cleanSessionChanged)
    def cleanSession(self) -> bool:
        return self.__cleanSession

    @cleanSession.setter
    def cleanSession(self, cleanSession) -> None:
        if self.__cleanSession == cleanSession:
            return
        self.__cleanSession = cleanSession
        self.cleanSessionChanged.emit(cleanSession)

    @pyqtProperty(int, notify=protocolVersionChanged)
    def protocolVersion(self) -> int:
        return self.__protocolVersion

    @protocolVersion.setter
    def protocolVersion(self, protocolVersion: int) -> None:
        if self.__protocolVersion == protocolVersion:
            return
        if protocolVersion in (self.MQTTv31, self.MQTTv311, self.MQTTv5):
            self.__protocolVersion = protocolVersion
            self.protocolVersionChanged.emit(protocolVersion)

    @pyqtSlot()
    def connect(self) -> None:
        if self.__hostname:
            self.__client.connect_async(
                self.__hostname, port=self.__port, keepalive=self.__keepAlive)
            self.__client.loop_start()

    @pyqtSlot()
    def disconnect(self) -> None:
        self.__client.disconnect()

    def subscribe(self, topic: str) -> None:
        if self.__status == MQTTStatus.Connected:
            self.__client.subscribe(topic)

    def subscribe(self, topic: str, callback: Callable[[str], None]) -> None:
        if self.__status == MQTTStatus.Connected:
            self.__callbacks[topic] = callback
            self.__client.subscribe(topic)

    def unsubscribe(self, topic: str) -> None:
        self.__client.unsubscribe(topic)
        if topic in self.__callbacks.keys():
            del self.__callbacks[topic]

    def publish(self, topic: str, payload: str) -> None:
        if self.__status == MQTTStatus.Connected:
            self.__client.publish(topic, payload=payload)

    def log(self, msg: str) -> str:
        return str

    """Callbacks"""

    def __on_connect(self, client, userdata, flags, rc):
        self.loggingSignals.info.emit(
            "[MQTT] " + mqtt.connack_string(rc))

        self.status = MQTTStatus.Connected
        self.connected.emit()
        self.__client.loop_start()

    def __on_disconnect(self, client, userdata, rc):
        if rc != 0:
            self.loggingSignals.warn.emit("[MQTT] Unexpected disconnection.")
            self.__client.reconnect()

        self.status = MQTTStatus.Disconected
        self.disconnected.emit()

    def __on_message(self, mqttc, obj, msg: mqtt.MQTTMessage):
        mstr = msg.payload.decode('utf-8')

        if msg.topic in self.__callbacks:
            self.__callbacks[msg.topic](mstr)

        self.messageArrived.emit(mstr)

    def __del__(self):
        self.disconnect()
