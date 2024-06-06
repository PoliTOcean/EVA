from app import app
from flask import jsonify, request
import json
import os

@app.route("/PID/set", methods = ['POST'])
def setData():
    rq = json.loads(request.get_data().decode())
    file = os.path.join("static", "info.json")

    with open(file) as json_file:
        data = json.load(json_file)

    for profile in rq:
        data["PID"][profile]["enabled"] = rq[profile]["enabled"]
        for key in rq[profile]["settings"]:
            data["PID"][profile]["settings"][key] = rq[profile]["settings"][key]


    with open(file, 'w') as json_file:
        json.dump(data, json_file, indent=4)

    return jsonify({ "text": "file updated" }), 200  