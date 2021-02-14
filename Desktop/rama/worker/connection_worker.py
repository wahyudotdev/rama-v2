from rama.core.connection_status import ConnectionStatus
from rama.core.mqtt import Mqtt
from PyQt5.QtCore import pyqtSignal, QThread
from time import sleep
from rama.config import LoadConfig
class ConnectionWorker(QThread):
    signal_rpi_latency = pyqtSignal(str)
    signal_esp_latency = pyqtSignal(str)
    signal_rpi_connected = pyqtSignal(bool)
    signal_esp_connected = pyqtSignal(bool)

    esp_host = "69.69.69.69"
    rpi_host = "69.69.69.69"

    def on_message(self,client, userdata, msg):
        payload = msg.payload.decode('utf-8')
        topic = str(msg.topic)
        if(topic == 'rama/ip'):
            self.esp_host = str(payload)
            self.esp = ConnectionStatus(self.esp_host)
        if(topic == 'rama/video'):
            self.rpi = ConnectionStatus(self.rpi_host)
            self.rpi_host = str(payload)

    def on_connect(self, client, userdata, flags, rc):
        try:
            print('connection listener started')
            client.subscribe('rama/ip')
            client.subscribe('rama/video')
        except:
            print('gagal')
            pass
    def on_disconnect(self, client, userdata, rc):
        self.is_connected.emit(False)
            
    def run(self):
        config = LoadConfig()
        self.mqtt = Mqtt(config.mqtt_host, on_message=self.on_message, on_connect= self.on_connect, on_disconnect=self.on_disconnect)
        self.esp = ConnectionStatus(self.esp_host)
        self.rpi = ConnectionStatus(self.rpi_host)

        while True:
            try:
                self.signal_esp_latency.emit(str(self.esp.latency()))
                self.signal_rpi_latency.emit(str(self.rpi.latency()))
                self.signal_esp_connected.emit(self.esp.connected())
                self.signal_rpi_connected.emit(self.rpi.connected())
            except:
                pass
            sleep(1)