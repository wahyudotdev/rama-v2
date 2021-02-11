import sys
import numpy as np

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import pyqtSlot
from rama.worker import VideoWorker, SensorWorker, KeyboardListenerWorker, SliderWorker
from rama.ui import Ui_MainWindow

app = QtWidgets.QApplication(sys.argv)
MainWindow = QtWidgets.QMainWindow()
ui = Ui_MainWindow()

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

# @pyqtSlot(str)
# def speed(value):
#     ui.horizontalSlider.setValue(int(value))

@pyqtSlot(bool)
def videoStatus(value):
    ui.startVideo.setText('Stop video' if value else 'Start video')

@pyqtSlot(bool)
def connectionStatus(value):
    ui.connectionState.setText('Tersambung' if value else 'Terputus')

def main():
    ui.setupUi(MainWindow)
    sensorthread = SensorWorker()
    sensorthread.rForward.connect(rForward)
    sensorthread.rBack.connect(rBack)
    sensorthread.rRight.connect(rRight)
    sensorthread.rLeft.connect(rLeft)
    sensorthread.is_connected.connect(connectionStatus)
    sensorthread.start()
    keyboardListener = KeyboardListenerWorker()
    keyboardListener.keypress_signal.connect(changeText)
    keyboardListener.start()

    # sliderthread = SliderWorker()
    # sliderthread.speed.connect(speed)
    # sliderthread.start()
    videothread = VideoWorker()
    videothread.change_pixmap_signal.connect(showVideo)
    videothread.is_started_signal.connect(videoStatus)
    videothread.start()
    ui.startVideo.clicked.connect(videothread.toggleVideo)
    # ui.horizontalSlider.valueChanged.connect(sliderthread.publishSpeed)
    MainWindow.show()
    sys.exit(app.exec_())

if __name__ == "__main__":
    main()