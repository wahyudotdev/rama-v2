# RAMA-V2 Desktop
## Build with PyQt5

## Project structure
    rama  
    ├───core  
    ├───resource  
    ├───ui  
    -───worker  

- core :  
folder ini berisi program utama yang digunakan untuk pengambilan data kamera dan sensor  
- resource :  
folder ini berisi resource seperti gambar, dan layout tampilan Qt Designer (.ui)  
- ui :  
folder ini berisi file python untuk merender user interface  
- worker :  
semua program yang meng-inheritance dari QThread diletakkan di folder ini  

## Requirements
- pynput==1.7.2
- imutils==0.5.3
- pythonping==1.0.15
- paho_mqtt==1.5.1
- opencv-contrib-python-headless==4.4.0.44
- opencv-python==4.4.0.44
- numpy==1.20.1
- PyQt5==5.15.0
- PyQt5-sip==12.8.0
## Usage :
1. pip install -r requirements.txt
2. python -m rama

## Build executable
python -m nuitka --standalone setup.py --enable-plugin=numpy --enable-plugin=data-files --enable-plugin=multiprocessing --enable-plugin=qt-plugins --include-package-data --show-progress