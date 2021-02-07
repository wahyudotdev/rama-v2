from PyQt5.QtCore import pyqtSignal, pyqtSlot, Qt, QThread
from rama.core import VideoStream
# from rama.core import WebcamVideoStream

import numpy as np

class VideoWorker(QThread):
    change_pixmap_signal = pyqtSignal(np.ndarray)
    # start_video = pyqtSignal(bool)
    # rRight = pyqtSignal(str)
    # rLeft = pyqtSignal(str)
    # rForward = pyqtSignal(str)
    # rBack = pyqtSignal(str)
    def run(self):
        frame = VideoStream('http://127.0.0.1:8000/video_feed')
        while True:
            capture = frame.capture()
            try:
                self.change_pixmap_signal.emit(capture)
            except Exception as e:
                pass
        frame.stop()
    
    def startVideo(self):
        self.start_video.emit(true)