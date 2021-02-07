from PyQt5.QtCore import pyqtSignal, pyqtSlot, Qt, QThread
from rama.core import Mqtt, Test

class SensorWorker(QThread):
    
    # def on_connect(self):
    #     print('connected from sensor worker')
    
    def run(self):
        pass
    def __init__(self, host):
        super().__init__()
