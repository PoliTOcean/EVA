import paho.mqtt.client as mqtt
from enum import Enum

class MQTTStatus(Enum):
    Disconnected = 0
    Connecting = 1
    Connected = 2

class MQTTClient():
    def __init__(self, client_id, hostname="127.0.0.1", port="1883"):
        self.__hostname = hostname
        self.__port = port
        self.__keepAlive = 60
        self.__cleanSession = False
        self.__protocolVersion = mqtt.MQTTv31
        self.__status = MQTTStatus.Disconnected
        self.__callbacks = dict()

        self.__client = mqtt.Client(client_id=client_id, clean_session=self.__cleanSession, protocol=self.__protocolVersion)
        self.__client.on_connect = self.__on_connect
        self.__client.on_message = self.__on_message
        self.__client.on_disconnect = self.__on_disconnect

    @property
    def status(self):
        return self.__status
    
    def connect(self):
        if self.__hostname:
            self.__client.connect_async(self.__hostname, port=self.__port,
                keepalive=self.__keepAlive)
            self.__client.loop_start()
    
    def disconnect(self):
        self.__client.disconnect()

    def subscribe(self, topic, callback):
        if self.__status == MQTTStatus.Connected:
            self.__callbacks[topic] = callback
            self.__client.subscribe(topic)
    
    def unsubscribe(self, topic):
        self.__client.unsubscribe(topic)
        if topic in self.__callbacks.keys():
            del self.__callbacks[topic]
    
    def publish(self, topic, payload):
        if self.__status == MQTTStatus.Connected:
            self.__client.publish(topic, payload=payload)
   
    def __on_connect(self, client, userdata, flags, rc):
        print(f"[MQTT] {mqtt.connack_string(rc)}")
        self.__status = MQTTStatus.Connected
        self.__client.loop_start()
    
    def __on_disconnect(self, client, userdata, rc):
        if rc != 0:
            print("[MQTT] Unexpected disconnection.")
            self.__client.reconnect()

        self.status = MQTTStatus.Disconnected
   
    def __on_message(self, mqttc, obj, msg):
        mstr = msg.payload.decode("utf-8")
        if msg.topic in self.__callbacks:
            self.__callbacks[msg.topic](mstr)

    def __del__(self):
        self.disconnect()
