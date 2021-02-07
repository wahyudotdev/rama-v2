from PyQt5.QtCore import pyqtSignal, pyqtSlot, Qt, QThread
from rama.core import Mqtt, Test

class SensorWorker(QThread):
    rForward    = pyqtSignal(str)
    rBack       = pyqtSignal(str)
    rRight      = pyqtSignal(str)
    rLeft       = pyqtSignal(str)

    def on_message(self,client, userdata, msg):
        payload = msg.payload.decode('utf-8')
        data = str(payload).split(',')
        if(data[0] == 'r'):
            self.rForward.emit(f'{data[1]} cm')
            self.rBack.emit(f'{data[2]} cm')
            self.rRight.emit(f'{data[3]} cm')
            self.rLeft.emit(f'{data[4]} cm')
    
    def run(self):
        self.mqtt = Mqtt('127.0.0.1', self.on_message)