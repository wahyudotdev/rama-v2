from PyQt5.QtCore import pyqtSignal, QThread
from rama.core import Mqtt
from rama.config import LoadConfig
import json
class SliderWorker(QThread):
    speed = pyqtSignal(str)
    def run(self):
        self.config = LoadConfig()
        self.mqtt = Mqtt(self.config.mqtt_host)
        self.speed.emit(self.config.speed)
        self.publishSpeed(self.config.speed)
    
    def publishSpeed(self, speed):
        s = int(float(speed)/100 * 255)
        self.mqtt.publish("controller", "{\"speed\":"+str(s)+"}" )
        self.speed.emit(str(speed))
        self.config.saveSpeed(speed)