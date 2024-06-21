from app import app
from flask import jsonify, request
import serial
from utils_float.float import start_communication, send, msg_status, listen, reset

s = serial.Serial(timeout = 2)

data = {'code': "FLOAT", 'status': 0, 'text': "" }

@app.route('/FLOAT/msg')
def float_msg():
    if (not s.is_open):
        data['status'] = False
        data['text'] = "SERIAL NOT OPENED"
        return jsonify(data), 400
    msg = request.args.get('msg')
    send(s, msg)
    data['status'] = True
    data['text'] = 'SUCCESS'
    return jsonify(data), 201
    

@app.route('/FLOAT/start')
def float_start():
    status = start_communication(s)
    data['status'] = status['status']
    data['text'] = status['text']
    return jsonify(data), 201


@app.route('/FLOAT/status')
def float_status():
    if (not s.is_open):
        data['status'] = False
        data['text'] = 'SERIAL NOT OPENED'
        return jsonify(data), 200
    msg = request.args.get('msg')
    sts = msg_status(s, msg)
    data['status'] = sts['status']
    data['text'] = sts['text']
    return jsonify(data), 201

@app.route('/FLOAT/listen')
def float_listen():
    sts = listen(s)
    imgdata = {
            'code': data['code'],
            'status': sts['status'],
            'data': sts['data'],
            'text': sts['text']   
        }
    if sts['text'] == "FINISHED":
        reset()
    return jsonify(imgdata), 201