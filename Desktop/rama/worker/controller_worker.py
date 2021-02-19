from PyQt5.QtCore import pyqtSignal, QThread
from pynput.keyboard import Listener
from rama.core import Mqtt
from rama.config import LoadConfig
import json

class ControllerWorker(QThread):
    keypress_signal = pyqtSignal(str)
    speed = 0
    def run(self):
        self.config = LoadConfig()
        self.speed = self.config.speed
        self.mqtt = Mqtt(self.config.mqtt_host)
        with Listener(on_press=self.on_press, on_release=self.on_release) as self.listener:
            self.listener.join()

    def on_press(self, key):
        self.publish_controller(str(key))

    def on_release(self, key):
        self.publish_controller('STOP')

    def change_speed(self, speed):
        self.speed = speed
        self.config.saveSpeed(speed)

    def publish_controller(self, payload):
        direction = {
            'Key.up': 1,
            'Key.down': 3,
            'Key.right': 2,
            'Key.left': 4,
            'STOP': 0
        }
        directionText = {
            'Key.up': "FORWARD",
            'Key.down': "REVERSE",
            'Key.right': "RIGHT",
            'Key.left': "LEFT"
        }
        try:
            self.keypress_signal.emit(directionText.get(payload, 'STOP'))
            # self.mqtt.publish('rama/controller', direction.get(payload, 'STOP'))
            data = json.dumps({
                'dir':direction.get(payload, 0),
                'speed':int(self.speed)
            })
            self.mqtt.publish('rama/controller', data)
        except:
            pass
