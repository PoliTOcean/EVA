from app import app
from flask import jsonify, request, make_response
import threading
from utils_rov.photogrammetry import fetch_image, STATUS, STOP_SIGNAL

# ! TASK 2024

@app.route('/PHOTO/stop')
def task2_stop():
    global STOP_SIGNAL
    STOP_SIGNAL.set()
    return jsonify(STATUS), 200

@app.route('/PHOTO/status')
def task2_status():
    return jsonify(STATUS), 200

@app.route('/PHOTO/start')
def task2_start():
    global STOP_SIGNAL
    if (STATUS["status"] == "STOPPED" or STATUS["status"] == "FINISHED"):
        STOP_SIGNAL.clear()
        thread = threading.Thread(target=fetch_image)
        thread.start()
        return jsonify({"status": "OK"}), 200
    return jsonify({"error": "Conflict"}), 409

