from PyQt5.QtCore import pyqtSignal, pyqtSlot, Qt, QThread
from pynput.keyboard import Listener
from rama.core import Mqtt
class KeyboardListenerWorker(QThread):
    keypress_signal = pyqtSignal(str)
    def run(self):
        self.mqtt = Mqtt('127.0.0.1')
        with Listener(on_press=self.on_press, on_release=self.on_release) as self.listener:  # Create an instance of Listener
                self.listener.join()  # Join the listener thread to the main thread to keep waiting for keys 
    def on_press(self,key):  # The function that's called when a key is pressed
            self.keypress_signal.emit(str(key))
            self.publish_controller(str(key))
    
    def on_release(self,key):  # The function that's called when a key is released
            self.publish_controller('STOP')
    
    def publish_controller(self, payload):
        direction = {
            'Key.up' : "{\"dir\":1}",
            'Key.down': "{\"dir\":3}",
            'Key.right': "{\"dir\":2}",
            'Key.left': "{\"dir\":4}",
            'STOP':"{\"dir\":0}"
        }
        try:
            self.mqtt.publish('controller', direction.get(payload,'IDLE'))
        except:
            pass