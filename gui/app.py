from flask import Flask
from flask_socketio import SocketIO
from flask.json.provider import DefaultJSONProvider
from datetime import datetime, date
from flask_cors import CORS

# UTC Time provider
class UpdatedJSONProvider(DefaultJSONProvider):
    def default(self, o):
        if isinstance(o, date) or isinstance(o, datetime):
            return o.isoformat()
        return super().default(o)


app = Flask(__name__, template_folder='template')
app.config['TEMPLATES_AUTO_RELOAD'] = True
app.json = UpdatedJSONProvider(app)
cors = CORS(app)


# socketio = SocketIO(app, engineio_logger = True, logger=True, debug=True,cors_allowed_origins='*', cors_credentials=False,async_mode='eventlet')


import utils_float
import utils_rov
import modules