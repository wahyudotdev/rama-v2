import paho.mqtt.client as mqtt
from time import sleep, time
from threading import Thread
from PyQt5.QtCore import pyqtSignal, pyqtSlot, Qt, QThread

class Mqtt(object):
    def __init__(self, host, on_message):
        self.host = host
        self.client = mqtt.Client()
        self.client.on_connect = self.on_connect
        self.client.on_message = on_message
        Thread(target=self.mqtt_connect, args=()).start()

    def on_connect(self, client, userdata, flags, rc):
        try:
            print("Connected")
            self.client.subscribe('rama')
        except:
            print('gagal')
            pass
    
    def mqtt_connect(self):
        self.client.connect(self.host, 1883, 3600)
        self.client.loop_forever()
        
    def disconnect(self):
        self.client.disconnect()
        sleep(0.5)
        self.client.connect(self.host, 1883, 3600)

    def publish(self, topic, payload):
            self.client.publish(topic, payload)
        