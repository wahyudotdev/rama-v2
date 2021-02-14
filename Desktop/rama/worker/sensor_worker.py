from PyQt5.QtCore import pyqtSignal, QThread
from rama.core import Mqtt
from rama.config import LoadConfig

class SensorWorker(QThread):
    rForward    = pyqtSignal(str)
    rBack       = pyqtSignal(str)
    rRight      = pyqtSignal(str)
    rLeft       = pyqtSignal(str)
    def on_message(self,client, userdata, msg):
        payload = msg.payload.decode('utf-8')
        data = str(payload).split(',')
        if(data[0] == 'r'):
            self.rForward.emit(f'{data[2]} cm')
            # self.rBack.emit(f'{data[3]} cm')
            self.rRight.emit(f'{data[1]} cm')
            self.rLeft.emit(f'{data[3]} cm')

    def on_connect(self, client, userdata, flags, rc):
        try:
            print("Connected")
            client.subscribe('rama/sensor')
        except:
            print('gagal')
            pass
    def on_disconnect(self, client, userdata, rc):
        self.is_connected.emit(False)

    def run(self):
        self.config = LoadConfig()
        self.mqtt = Mqtt(self.config.mqtt_host,
                        self.on_message,
                        self.on_connect,
                        self.on_disconnect)