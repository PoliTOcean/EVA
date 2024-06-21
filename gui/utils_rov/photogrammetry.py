import requests
import time
import os
import subprocess
from .main import contr
import threading


STOP_SIGNAL = threading.Event()
URL = "http://10.0.0.254:8079/snapshot"
SAVE_PATH = os.path.join(os.path.dirname(__file__), "captures")
STATUS = {
    "status": "STOPPED",
    "data": ""
}
COUNTER = 0

def on_message(command):
    global COUNTER
    if "SNAP" not in command:
        return 
    try:
        response = requests.get(URL)
        response.raise_for_status()  

        file_path = os.path.join(SAVE_PATH, f"image_{COUNTER}.jpg")

        with open(file_path, "wb") as file:
            file.write(response.content)
        print(f"Saved {file_path}")

    except requests.RequestException as e:
        print(f"Error: {e}")

    COUNTER = COUNTER + 1

    


def fetch_image():
    print("THREAD PHOTO STARTED")
    global STATUS, COUNTER
    COUNTER = 0
    STATUS["status"] = "STARTED"


    if not os.path.exists(SAVE_PATH):
        os.makedirs(SAVE_PATH)

    STATUS["status"] = "CAPTURING"

    contr.mqttClient().subscribe("state_commands/", on_message)

    while (not STOP_SIGNAL.is_set()):
        time.sleep(0.1)

    contr.mqttClient().unsubscribe("state_commands/")
    
    STATUS["status"] = "ELABORATING_IMAGES"


    # codice per la finocchiogrammetria
    time.sleep(3)



    STATUS["status"] = "FINISHED"
    # ? Che risultato in output restituisco in interfaccia?
    STATUS["data"] = "boh"
    
    return