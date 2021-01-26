from PyQt5.QtCore import pyqtSignal, pyqtSlot, Qt, QThread
from core.videostream import VideoStream
from core.WebcamVideoStream import WebcamVideoStream

import numpy as np

class MainWindowWorker(QThread):
    change_pixmap_signal = pyqtSignal(np.ndarray)
    def run(self):
        frame = VideoStream('http://192.168.43.8')
        while True:
            capture = frame.capture()
            try:
                self.change_pixmap_signal.emit(capture)
            except Exception as e:
                print(e)
        frame.stop()