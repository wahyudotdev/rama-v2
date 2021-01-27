import sys
from multiprocessing import Process
import numpy as np
from pynput.keyboard import Listener
import logging

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import pyqtSignal, pyqtSlot, Qt, QThread
from worker.main_window_worker import MainWindowWorker
from ui.main_window import Ui_MainWindow
from core.mqtt import Mqtt


app = QtWidgets.QApplication(sys.argv)
MainWindow = QtWidgets.QMainWindow()
ui = Ui_MainWindow()


class KeyboardListener(QThread):
    keypress_signal = pyqtSignal(str)
    def run(self):
        self.mqtt = Mqtt('127.0.0.1')
        with Listener(on_press=self.on_press, on_release=self.on_release) as listener:  # Create an instance of Listener
                listener.join()  # Join the listener thread to the main thread to keep waiting for keys  
    
    def on_press(self,key):  # The function that's called when a key is pressed
            self.keypress_signal.emit(str(key))
            self.mqtt.publish(str(key))
    
    def on_release(self,key):  # The function that's called when a key is released
            print(key)


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

if __name__ == "__main__":
    ui.setupUi(MainWindow)
    thread = MainWindowWorker()
    thread.change_pixmap_signal.connect(showVideo)
    thread.start()
    keyboardListener = KeyboardListener()
    keyboardListener.keypress_signal.connect(changeText)
    keyboardListener.start()
    MainWindow.show()
    sys.exit(app.exec_())