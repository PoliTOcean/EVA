from app import app
from flask import render_template, send_file

@app.route("/")
def main():
    return render_template('GUI.html')

@app.route("/ROV")
def gui():
    return render_template("ROV.html")

@app.route("/FLOAT")
def float():
    return render_template("FLOAT.html")

@app.route("/PID")
def pid():
    return render_template("PID.html")

@app.route("/TASK_1")
def task_1():
    return render_template("TASK_1.html")

@app.route("/TASK_2")
def task_2():
    return render_template("TASK_2.html")


# ! TO REMOVE
@app.route("/test")
def test():
    return send_file("./static/po.png", mimetype='image/gif')


@app.route("/flaskwebgui-keep-server-alive", methods=["GET"])
def responde():
    return '{"content": "Nothing"}'
