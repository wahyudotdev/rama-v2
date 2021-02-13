from PyQt5.QtCore import pyqtSignal, pyqtSlot, Qt, QThread
from rama.core import VideoStream, UdpStream
from rama.config import LoadConfig
import numpy as np

class VideoWorker(QThread):
    change_pixmap_signal = pyqtSignal(np.ndarray)
    is_started = False
    is_started_signal = pyqtSignal(bool)
    def run(self):
        self.config = LoadConfig()
        self.frame = UdpStream("192.168.43.44")
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