# RAMA-V2 Desktop

## Struktur Folder Project
    rama  
    ├─── core
    ├─── config    
    ├─── resource  
    ├─── ui  
    ├─── worker  

- core  
folder ini berisi program utama yang digunakan untuk pengambilan data kamera dan sensor 
- config  
 folder ini berisi setting untuk basestation  
- resource  
folder ini berisi resource seperti gambar, dan layout tampilan Qt Designer (.ui)  
- ui  
folder ini berisi file python untuk merender user interface  
- worker  
semua program yang meng-inheritance dari QThread diletakkan di folder ini  

## Dependensi
- pynput
- imutils
- pythonping
- paho_mqtt
- opencv-contrib-python-headless
- opencv-python
- numpy
- PyQt5
- PyQt5-sip
## Cara Penggunaan
1. pip install -r requirements.txt
2. python setup.py

## Kompilasi
1. Install nuitka terlebih dahulu untuk kompilasi program
2. Mulai kompilasi dengan terminal atau windows powershell
- Windows
```
python -m nuitka --standalone setup.py --enable-plugin=numpy --enable-plugin=data-files --enable-plugin=multiprocessing --enable-plugin=qt-plugins --include-package-data --show-progress  --windows-icon-from-ico=rama.ico --windows-disable-console  
```
- Linux
```
python -m nuitka --standalone setup.py --enable-plugin=numpy --enable-plugin=data-files --enable-plugin=multiprocessing --enable-plugin=qt-plugins --include-package-data --show-progress
```
3. Salin folder config ke folder setup.dist/rama/
4. Jalankan file setup.dist/setup.exe