import cv2
import urllib.request
from threading import Thread
import numpy as np
class VideoStream(object):
    def __init__(self, url):
        self.stream = urllib.request.urlopen('http://192.168.43.8')
        self.total_bytes = b''
    def capture(self):
        try:
            self.total_bytes += self.stream.read(1024)
            self.b = self.total_bytes.find(b'\xff\xd9') # JPEG end
            if not self.b == -1:
                self.a = self.total_bytes.find(b'\xff\xd8') # JPEG start
                jpg = self.total_bytes[self.a:self.b+2] # actual image
                self.total_bytes= self.total_bytes[self.b+2:] # other informations
                # decode to colored image ( another option is cv2.IMREAD_GRAYSCALE )
                img = cv2.imdecode(np.fromstring(jpg, dtype=np.uint8), cv2.IMREAD_COLOR)
                return img
        except Exception as e:
            print(e)
            pass    

    def stop(self):
        self.cap.release()