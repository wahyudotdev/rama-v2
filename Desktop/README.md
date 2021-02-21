# RAMA-V2 Desktop
## Build with PyQt5

## Project structure
    rama  
    ├───core  
    ├───resource  
    ├───ui  
    ├───worker  

- core :  
folder ini berisi program utama yang digunakan untuk pengambilan data kamera dan sensor  
- resource :  
folder ini berisi resource seperti gambar, dan layout tampilan Qt Designer (.ui)  
- ui :  
folder ini berisi file python untuk merender user interface  
- worker :  
semua program yang meng-inheritance dari QThread diletakkan di folder ini  

## Requirements
- pynput
- imutils
- pythonping
- paho_mqtt
- opencv-contrib-python-headless
- opencv-python
- numpy
- PyQt5
- PyQt5-sip
## Usage
1. pip install -r requirements.txt
2. python setup.py

## Build executable
Install nuitka first to build executable
```
python -m nuitka --standalone setup.py --enable-plugin=numpy --enable-plugin=data-files --enable-plugin=multiprocessing --enable-plugin=qt-plugins --include-package-data --show-progress