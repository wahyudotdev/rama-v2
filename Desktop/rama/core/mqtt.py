import paho.mqtt.client as mqtt
from time import sleep, time
from threading import Thread
from PyQt5.QtCore import pyqtSignal, pyqtSlot, Qt, QThread

class Mqtt(object):

    def __init__(self, host):
        self.host = host
        self.client = mqtt.Client()
        self.client.on_connect = self.on_connect
        self.client.on_message = self.on_message
        Thread(target=self.start, args=()).start()

    def on_connect(self, client, userdata, flags, rc):
        try:
            print("Connected")
        except:
            print('gagal')
            pass

    def on_message(self,client, userdata, msg):
        payload = msg.payload.decode('utf-8')
        print(payload)

    def start(self):
        self.client.connect(self.host, 1883, 3600)
        self.client.loop_forever()

    def publish(self, payload):
        direction = {
        'Key.up' : "{\"dir\":1}",
        'Key.down': "{\"dir\":3}",
        'Key.right': "{\"dir\":2}",
        'Key.left': "{\"dir\":4}"
        }
        self.client.publish('controller', direction.get(payload,'IDLE'))