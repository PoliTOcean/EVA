import RPi.GPIO as GPIO  # import the libraries for GPIO
import paho.mqtt.client as mqtt  # import the libraries for MQTT Client

# Pin Definitions
# LOOK AT THE SCHEME IN THE FOLDER
LedPinOut = 16  # LOOK AT THE SCHEME IN THE FOLDER
syringePinOut = 17  # LOOK AT THE SCHEME IN THE FOLDER
# LOOK AT THE SCHEME IN THE FOLDER


def GPIO_Controll(cmd, client):  # Dedicated method for setting state on pins
    CurrValue = GPIO.LOW  # convenience variable
    if cmd == "ledON":  # condition to check the command
        CurrValue = GPIO.HIGH  # alter the dummy variable to with the desired state
        # I print an alert to notify you of the alteration of the pin status
        print("Outputting {} to pin {}".format(CurrValue, LedPinOut))
        # set the pin related to the command and set it with the desired status
        GPIO.output(LedPinOut, CurrValue)
        # I publish on the "Status/" topic the new status of the pin
        client.publish("status/Led", CurrValue)
    elif cmd == "ledOFF":
        CurrValue = GPIO.LOW  # alter the dummy variable to with the desired state
        # I print an alert to notify you of the alteration of the pin status
        print("Outputting {} to pin {}".format(CurrValue, LedPinOut))
        # set the pin related to the command and set it with the desired status
        GPIO.output(LedPinOut, CurrValue)
        # I publish on the "Status/" topic the new status of the pin
        client.publish("status/Led", CurrValue)

    if cmd == "MotorON":
        CurrValue = GPIO.HIGH  # alter the dummy variable to with the desired state
        # I print an alert to notify you of the alteration of the pin status
        print("Outputting {} to pin {}".format(CurrValue, LedPinOut))
        # set the pin related to the command and set it with the desired status
        GPIO.output(LedPinOut, CurrValue)
        # I publish on the "Status/" topic the new status of the pin
        client.publish("status/Motor", CurrValue)
    elif cmd == "MotorOFF":
        CurrValue = GPIO.LOW  # alter the dummy variable to with the desired state
        # I print an alert to notify you of the alteration of the pin status
        print("Outputting {} to pin {}".format(CurrValue, LedPinOut))
        # set the pin related to the command and set it with the desired status
        GPIO.output(LedPinOut, CurrValue)
        # I publish on the "Status/" topic the new status of the pin
        client.publish("status/Motor", CurrValue)


def on_connect(mqttc, obj, flags, rc):
    print("rc: " + str(rc))  # print return code after connection


def on_message(client, userdata, message):
    cmd = str(message.payload.decode("utf-8"))
    print("message received ", str(message.payload.decode("utf-8")))
    print("message topic=", message.topic)
    print("message qos=", message.qos)
    print("message retain flag=", message.retain)

    GPIO_Controll(cmd, client)  # Call the pin setting method


def on_publish(mqttc, obj, mid):
    print("mid: " + str(mid))  # print the message ID after pubblishig


def on_subscribe(mqttc, obj, mid, granted_qos):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))


def on_log(mqttc, obj, level, string):
    print(string)


def main():
    print("boot")
    brokerMqttAddress = "127.0.0.1"  # IP Address of MQTT Broker
    broketMqttPort = 1883  # Port
    brokerMqttTimeOut = 60
    SubTopic = "commands/"  # subscribe topic, in this case "Commands/"
    PubTopic = "status/"  # Pubblisher Topic for GPIO status
    mqttc = mqtt.Client("JETSON_GPIO_CLIENT")  # instance for Client Object
    # create the functions for the MQTT Client
    mqttc.on_message = on_message
    mqttc.on_connect = on_connect
    mqttc.on_publish = on_publish
    mqttc.on_subscribe = on_subscribe
    # I connect the MQTT client with the 3 parameters
    mqttc.connect(brokerMqttAddress, broketMqttPort, brokerMqttTimeOut)
    # subscribe the client to the topic "Commands/"
    mqttc.subscribe(SubTopic, 0)
    print("MQTT initialization complete \n")

    try:
        print("GPIO initialization...")
        # Pin Setup:
        # Board pin-numbering scheme
        GPIO.setmode(GPIO.BCM)
        # set pin as an output pin with optional initial state of LOW
        # setupping LedPinOut for Outyput signal
        GPIO.setup(LedPinOut, GPIO.OUT, initial=GPIO.LOW)
        GPIO.setup(syringePinOut, GPIO.OUT, initial=GPIO.LOW)
        print("GPIO Initialized successfully")
    except:
        print("GPIO Error")

    mqttc.loop_forever()


if __name__ == "__main__":
    main()

# Monticciolo Matteo
# 08/02/2023 v 1.0.0
