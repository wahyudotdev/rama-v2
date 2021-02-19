import sys
import numpy as np
from time import sleep
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import pyqtSlot
from rama.worker import VideoWorker, SensorWorker, ControllerWorker, ConnectionWorker
from rama.ui import Ui_MainWindow, SpeedWindow, speed_window

app = QtWidgets.QApplication(sys.argv)
MainWindow = QtWidgets.QMainWindow()
ui = Ui_MainWindow()
speedwindow = SpeedWindow()

# worker
connectionthread = None
sensorthread = None
controller = None
videothread = None

def convertCvToPixmap(img):
    return QtGui.QImage(img, img.shape[1], img.shape[0], QtGui.QImage.Format_RGB888).rgbSwapped()
  
@pyqtSlot(np.ndarray)
def showVideo(cv_image):
    ui.video.setPixmap(QtGui.QPixmap.fromImage(convertCvToPixmap(cv_image)))

@pyqtSlot(str)
def changeText(value):
    ui.direction.setText(value)

@pyqtSlot(str)
def rForward(value):
    ui.rForward.setText(value)

@pyqtSlot(str)
def rBack(value):
    ui.rBack.setText(value)

@pyqtSlot(str)
def rRight(value):
    ui.rRight.setText(value)

@pyqtSlot(str)
def rLeft(value):
    ui.rLeft.setText(value)

@pyqtSlot(bool)
def switchVideo(value):
    ui.startVideo.setText('Stop video' if value else 'Start video')

@pyqtSlot(bool)
def espStatus(value):
    ui.contollerState.setText('ONLINE' if value else 'OFFLINE')
    ui.contollerState.setMargin(5)

@pyqtSlot(str)
def espLatency(value):
    ui.latencyEsp.setText(f'ESP {value} ms')
    ui.latencyEsp.setMargin(5)

@pyqtSlot(bool)
def rpiStatus(value):
    ui.videoState.setText('ONLINE' if value else 'OFFLINE')
    ui.videoState.setMargin(5)

@pyqtSlot(str)
def rpiLatency(value):
    ui.latencyRpi.setText(f'RPi {value} ms')
    ui.latencyRpi.setMargin(5)

def setSpeed():
    speed = speedwindow.getInteger()
    if(speed != None):
        controller.change_speed(speed)
        ui.changeSpeed.setText(f'SPEED : {speed}')

def main():
    ui.setupUi(MainWindow)
    global connectionthread
    connectionthread = ConnectionWorker()
    connectionthread.signal_esp_connected.connect(espStatus)
    connectionthread.signal_esp_latency.connect(espLatency)
    connectionthread.signal_rpi_connected.connect(rpiStatus)
    connectionthread.signal_rpi_latency.connect(rpiLatency)
    connectionthread.start()

    global sensorthread
    sensorthread = SensorWorker()
    sensorthread.rForward.connect(rForward)
    sensorthread.rBack.connect(rBack)
    sensorthread.rRight.connect(rRight)
    sensorthread.rLeft.connect(rLeft)
    sensorthread.start()

    global controller
    controller = ControllerWorker()
    controller.keypress_signal.connect(changeText)
    controller.start()

    global videothread
    videothread = VideoWorker()
    videothread.change_pixmap_signal.connect(showVideo)
    videothread.is_started_signal.connect(switchVideo)
    videothread.start()

    ui.startVideo.clicked.connect(videothread.toggleVideo)
    ui.changeSpeed.clicked.connect(setSpeed)

    sleep(0.1)
    ui.changeSpeed.setText(f'SPEED : {controller.speed}')
    MainWindow.show()
    sys.exit(app.exec_())

if __name__ == "__main__":
    main()