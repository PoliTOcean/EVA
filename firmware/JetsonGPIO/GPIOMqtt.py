# import RPi.GPIO as GPIO
import time
import paho.mqtt.client as mqtt

# Pin Definitions
output_pin = 18  # BOARD pin 12, BCM pin 18


def on_connect(mqttc, obj, flags, rc):
    print("rc: " + str(rc))


def on_message(mqttc, obj, msg):
    print(msg.topic + " " + str(msg.qos) + " " + str(msg.payload))


def on_publish(mqttc, obj, mid):
    print("mid: " + str(mid))


def on_subscribe(mqttc, obj, mid, granted_qos):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))


def on_log(mqttc, obj, level, string):
    print(string)


def main():
    print("boot")
    brokerMqttAddress = "127.0.0.1"  # IP Address of MQTT Broker
    broketMqttPort = 1883
    brokerMqttTimeOut = 60
    SubTopic = "commands/"  # subscribe topic, in this case "Commands/"
    PubTopic = "status/"  # Pubblisher Topic for GPIO status
    mqttc = mqtt.Client()  # instance for Client Object
    mqttc.on_message = on_message
    mqttc.on_connect = on_connect
    mqttc.on_publish = on_publish
    mqttc.on_subscribe = on_subscribe

    mqttc.connect(brokerMqttAddress, broketMqttPort, brokerMqttTimeOut)
    mqttc.subscribe("components/", 0)

    mqttc.loop_forever()
    # Pin Setup:
    # Board pin-numbering scheme
    #    GPIO.setmode(GPIO.BCM)
    # set pin as an output pin with optional initial state of HIGH
    #   GPIO.setup(output_pin, GPIO.OUT, initial=GPIO.HIGH)

    print("Starting demo now! Press CTRL+C to exit")
    #  curr_value = GPIO.HIGH
    try:
        while True:
            time.sleep(2)
            # Toggle the output every second
    #       print("Outputting {} to pin {}".format(curr_value, output_pin))
    #         GPIO.output(output_pin, curr_value)
    #        curr_value ^= GPIO.HIGH
    finally:
          print()

if __name__ == "__main__":
    main()
