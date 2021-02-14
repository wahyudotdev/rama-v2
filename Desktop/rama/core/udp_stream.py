import cv2
import socket
import pickle
import imutils
import numpy as np

class UdpStream(object):
    frame_info = None
    buffer = None
    max_length = 65540
    def __init__(self, url):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind((url, 5000))
        print("-> waiting for connection")

    def capture(self):
        try:
            frame = None
            data, address = self.sock.recvfrom(self.max_length)
            if len(data) < 100:
                frame_info = pickle.loads(data)

                if frame_info:
                    nums_of_packs = frame_info["packs"]

                    for i in range(nums_of_packs):
                        data, address = self.sock.recvfrom(self.max_length)
                        if i == 0:
                            buffer = data
                        else:
                            buffer += data
                    frame = np.frombuffer(buffer, dtype=np.uint8)
                    frame = frame.reshape(frame.shape[0], 1)
                    frame = cv2.imdecode(frame, cv2.IMREAD_COLOR)
                    # frame = cv2.imdecode(frame, cv2.IMREAD_REDUCED_COLOR_2)
                    frame = cv2.flip(frame, 1)
                    frame = imutils.resize(frame, width=800)
                    return frame
        except:
            pass