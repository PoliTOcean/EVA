from app import app
from flask import jsonify, request
from utils_rov.task3 import crea_grafico, leggi_csv

# ! TASK 2024

@app.route("/TASK_1/file", methods = ['POST'])
def file():
    if 'file' not in request.files:
        return jsonify({'error': 'Bad Request'}), 400

    file = request.files['file']
    if file.filename == '':
        return jsonify({'error': 'File field empty'}), 400


    rec1, rec2, rec3 = leggi_csv(file)
    data = crea_grafico(rec1, rec2, rec3)
         
    return jsonify({"success": "success", "data": data}), 200 