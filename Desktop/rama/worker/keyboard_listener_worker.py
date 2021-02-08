from PyQt5.QtCore import pyqtSignal, pyqtSlot, Qt, QThread
from pynput.keyboard import Listener
from rama.core import Mqtt
from rama.config import LoadConfig

class KeyboardListenerWorker(QThread):
    keypress_signal = pyqtSignal(str)

    def run(self):
        self.config = LoadConfig()
        self.mqtt = Mqtt(self.config.mqtt_host)
        # Create an instance of Listener
        with Listener(on_press=self.on_press, on_release=self.on_release) as self.listener:
            # Join the listener thread to the main thread to keep waiting for keys
            self.listener.join()

    def on_press(self, key):  # The function that's called when a key is pressed
        self.publish_controller(str(key))

    def on_release(self, key):  # The function that's called when a key is released
        self.publish_controller('STOP')

    def publish_controller(self, payload):
        direction = {
            'Key.up': "{\"dir\":1}",
            'Key.down': "{\"dir\":3}",
            'Key.right': "{\"dir\":2}",
            'Key.left': "{\"dir\":4}",
            'STOP': "{\"dir\":0}"
        }
        directionText = {
            'Key.up': "MAJU",
            'Key.down': "MUNDUR",
            'Key.right': "KANAN",
            'Key.left': "KIRI"
        }
        try:
            self.keypress_signal.emit(directionText.get(payload, 'STOP'))
            self.mqtt.publish('controller', direction.get(payload, 'STOP'))
        except:
            pass
