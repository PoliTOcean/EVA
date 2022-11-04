import paho.mqtt.client as mqtt
import json

import random


def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))


def on_publish(client, userdata, result):
    print(f"data published \nresult {result}")


def random_sensors():
    data = {}
    data['temperature'] = round(random.uniform(40,60),2)
    data['depth'] = round(random.uniform(0,10),2)
    data['voltage'] = random.random()*10
    data['current'] = random.random()*10

    return data


if __name__ == '__main__':
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_publish = on_publish

    client.connect("localhost", 1883, 60)

    try:
        while True:
            input("Press Enter to continue...")
            client.publish("sensors/", json.dumps(random_sensors()))

    except KeyboardInterrupt:
        pass
