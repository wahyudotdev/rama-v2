import sys
from multiprocessing import Process
import numpy as np
from pynput.keyboard import Listener
from pynput import keyboard
import logging
from time import sleep, time
from threading import Thread

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import pyqtSignal, pyqtSlot, Qt, QThread
from rama.worker import VideoWorker, SensorWorker, KeyboardListenerWorker
from rama.ui import Ui_MainWindow
from rama.core import Mqtt


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
    direction = {
        'Key.up' : "MAJU",
        'Key.down': "MUNDUR",
        'Key.right': "KANAN",
        'Key.left': "KIRI"
    }
    ui.direction.setText(direction.get(value,''))

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


if __name__ == "__main__":
    ui.setupUi(MainWindow)

    sensorthread = SensorWorker()
    sensorthread.rForward.connect(rForward)
    sensorthread.rBack.connect(rBack)
    sensorthread.rRight.connect(rRight)
    sensorthread.rLeft.connect(rLeft)
    sensorthread.start()
    keyboardListener = KeyboardListenerWorker()
    keyboardListener.keypress_signal.connect(changeText)
    keyboardListener.start()
    videothread = VideoWorker()
    videothread.change_pixmap_signal.connect(showVideo)
    videothread.start()
    MainWindow.show()
    sys.exit(app.exec_())