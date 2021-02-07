# RAMA-V2 Desktop
## Build with PyQt5

## Project structure
\t    rama
\t    ├───core  
\t    ├───resource
\t    ├───ui
\t    -───worker

- core :
- - folder ini berisi program utama yang digunakan untuk pengambilan data kamera dan sensor
- resource :
- - folder ini berisi resource seperti gambar, dan layout tampilan Qt Designer (.ui)
- ui :
- - folder ini berisi file python untuk merender user interface
- worker :
- - semua program yang meng-inheritance dari QThread diletakkan di folder ini

## Requirements
- OpenCV v3 or latest (can be used with opencv python package)
## Usage :
- python -m rama