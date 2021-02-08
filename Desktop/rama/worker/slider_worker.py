from PyQt5.QtCore import pyqtSignal, pyqtSlot, Qt, QThread
from rama.core import Mqtt
from rama.config import LoadConfig
class SliderWorker(QThread):
    speed = pyqtSignal(str)
    def run(self):
        self.config = LoadConfig()
        self.mqtt = Mqtt(self.config.mqtt_host)
        self.speed.emit(self.config.speed)
        self.publishSpeed(self.config.speed)
    
    def publishSpeed(self, speed):
        self.mqtt.publish("speed", speed)
        self.speed.emit(str(speed))
        self.config.saveSpeed(speed)