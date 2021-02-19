import sys
from PyQt5.QtWidgets import QApplication, QWidget, QInputDialog, QLineEdit
from PyQt5.QtGui import QIcon

class SpeedWindow(QWidget):
    def __init__(self):
        super().__init__()

    def getInteger(self):
        i, okPressed = QInputDialog.getInt(self, "Enter speed","Percentage:", 0, 0, 100, 1)
        if okPressed:
            return i
    