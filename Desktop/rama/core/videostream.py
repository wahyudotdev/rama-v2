import cv2
import urllib.request
from threading import Thread
import numpy as np
class VideoStream(object):
    def __init__(self, url):
        try:
            # ESP32
            # self.stream = urllib.request.urlopen('http://127.0.0.1:8000/video_feed')
            # Raspberry
            self.stream = cv2.VideoCapture(url)
            self.stream.open()
            self.total_bytes = b''
        except:
            pass
    def capture(self):
        try:
            # Using raspberry
            ret, frame = self.stream.read()
            return frame
            # Using ESP32
            # self.total_bytes += self.stream.read(1024)
            # self.b = self.total_bytes.find(b'\xff\xd9') # JPEG end
            # if not self.b == -1:
            #     self.a = self.total_bytes.find(b'\xff\xd8') # JPEG start
            #     jpg = self.total_bytes[self.a:self.b+2] # actual image
            #     self.total_bytes= self.total_bytes[self.b+2:] # other informations
            #     # decode to colored image ( another option is cv2.IMREAD_GRAYSCALE )
            #     img = cv2.imdecode(np.fromstring(jpg, dtype=np.uint8), cv2.IMREAD_COLOR)
            #     return img
        except Exception as e:
            pass    

    def stop(self):
        self.cap.release()