# Sudoku Solver via Webcam

## ScreenShots
![Preprocessing](https://github.com/cls-talha/SudokoSolver-with-opencv-Cpp-and-Pytorch/blob/linux-version/SodukuSolver%20opencv/screenshots/o2.png)

![Some more Preprocessings](https://github.com/cls-talha/SudokoSolver-with-opencv-Cpp-and-Pytorch/blob/linux-version/SodukuSolver%20opencv/screenshots/o1.png)

![Preprocessings](https://github.com/cls-talha/SudokoSolver-with-opencv-Cpp-and-Pytorch/blob/linux-version/SodukuSolver%20opencv/screenshots/2023-05-07_12-39.png)

![idk](https://github.com/cls-talha/SudokoSolver-with-opencv-Cpp-and-Pytorch/blob/linux-version/SodukuSolver%20opencv/screenshots/tease.jpg)

## Introduction
This project is a Sudoku Solver that uses deep learning techniques for digit recognition. It is built using OpenCV for image processing and PyTorch for digit classification. The solver is capable of taking an image of a Sudoku puzzle as input and outputting the solved puzzle.

###  PyTorch
PyTorch is an open-source machine learning library for Python to build and train deep learning models. Developed by Facebook's AI Research lab. PyTorch offers a high-level interface for building neural networks and supports both static and dynamic computational graphs. It also provides a wide range of pre-built modules and utilities, making it easy for non-technical users to implement advanced machine learning techniques. 
 ### Opencv(c++)
 OpenCV is an open-source computer vision and machine learning software library written in C++. It provides a wide range of functions and algorithms related to image and video processing, including object detection and motion analysis. It is used extensively in various industries, such as automotive, robotics, and security, as well as in research.

# Purpose
There are many reaons to choose this project some are listed below
- The purpose of this project is to enhance my skills in C++ and Python programming and gain experience in using deep learning for real-world problems.
- To utilize computer vision techniques in OpenCV and deep learning models in PyTorch for digit recognition.
- By completing this project, practical experience is gained in implementing computer vision techniques and building and training deep learning models.
- To impress my classmates xDD
## Structure of Project
This project is divided into 2 sub projects:
- ##### Training Digit Classifier (Directory named as "Digit Classifier")
- ##### Using model for solving Sudoku (Directory named as "SudokuSolver opencv")


#### 1) Training Digit Classifier
In this part, I trained Convolutional Neural Net(CNN) model for Digit Classification so I can recognize digits on Sudoku Board.
To run Python script it requires 
```bash
Python3 version: 3.10.11
Pytorch version: 2.0.0
```
It is preferable to use Google Colab for Deep Learning, you can also access google-colab version to train model from here:
https://colab.research.google.com/drive/1kDC7D7SepjpiCVunYCsn3VkY5p8oe5ME?usp=sharing


#### 2) Using model and solving Sudoku
In this part, I used my own trained model and some other image processing techniqures to solve Sudoku which is obtrained from camera and overly solution on current frame.

## How to Run this project
This repository contains 2 branches of same project
- linux-version Branch uses CMake to build
-  Main Branch Uses Visual Studio Solution to build

### To Run this project on Local Machine 
1. ### Clone this repository or download as Zip (from green button).

This Project requires opencv(C++) to install opencv: 
##### Windows
To use opencv on Windows you can install it via vcpkg (c++ library manager) 
- To install vcpkg follow [this](https://www.youtube.com/watch?v=wRnjahwxZ8A) tutorial
- To install opencv follow [this](https://eximia.co/hello-opencv-with-c-using-visual-studio-2017-and-vcpkg/) tutorial
##### Linux
To install opencv in arch-base Distros simply type this command in Terminal
```bash
pacman -S opencv
```
2. ### Change Directory to Build folder
##### Windows
Find build Directory Or click on "exe" file which is present in Root Directory and click on it 

##### Linux
Open Terminal and change Directory to Build and type: 
```bash
cd build
./app
```

### Credits
   "Thanks to Bilal Abid for the PNGs and Awaiz for testing code and giving me motivation throughout the project. You guys rock!"
    "Kudos to Stack Overflow, my coding lifeline!"
    "Big thanks GitHub, my project's home!"
    "Grateful to YouTube tutorials, Murtaza Hassan you are BESTEST"
    "Cheers to ChatGPT, my witty code companion!"
    
### Memes
"To add some spice while battling boredom, I took the liberty of creating memes. Enjoy!"

<iframe width="560" height="315" src="<iframe width="560" height="315" src="https://github.com/cls-talha/SudokoSolver-with-opencv-Cpp-and-Pytorch/blob/linux-version/SodukuSolver%20opencv/IShowSpeed%20Dances%20%E2%80%9COne%20Kiss%E2%80%9D%20Green%20Screen%20720p.mp4" frameborder="0" allowfullscreen></iframe>
" frameborder="0" allowfullscreen></iframe>





