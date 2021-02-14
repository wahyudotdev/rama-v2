from PyQt5.QtCore import pyqtSignal, QThread
from cv2 import data
from rama.core import UdpStream, Mqtt
from rama.config import LoadConfig
import numpy as np
import socket

class VideoWorker(QThread):
    change_pixmap_signal = pyqtSignal(np.ndarray)
    is_started = False
    is_started_signal = pyqtSignal(bool)
    def on_message(self,client, userdata, msg):
        data = str(msg.payload.decode('utf-8'))
    def on_connect(self, client, userdata, flags, rc):
        client.publish('basestation', self.ip)
    def run(self):
        self.config = LoadConfig()
        hostname = socket.gethostname()
        self.ip = socket.gethostbyname(hostname)
        self.frame = UdpStream(str(self.ip))
        self.mqtt = Mqtt(self.config.mqtt_host, on_message=self.on_message, on_connect=self.on_connect)
        while True:
            if(self.is_started):
                capture = self.frame.capture()
                try:
                    self.change_pixmap_signal.emit(capture)
                except Exception as e:
                    pass
            else:
                try:
                    self.frame.stop()
                except:
                    pass

    def toggleVideo(self):
        self.is_started = not self.is_started
        self.is_started_signal.emit(self.is_started)
        self.mqtt.publish('basestation', self.ip)