# Sudoku Solver via Webcam

## Screenshots
![Preprocessing](https://github.com/cls-talha/SudokoSolver-with-opencv-Cpp-and-Pytorch/blob/linux-version/SodukuSolver%20opencv/screenshots/o2.png)

![More Preprocessings](https://github.com/cls-talha/SudokoSolver-with-opencv-Cpp-and-Pytorch/blob/linux-version/SodukuSolver%20opencv/screenshots/o1.png)

![Preprocessings](https://github.com/cls-talha/SudokoSolver-with-opencv-Cpp-and-Pytorch/blob/linux-version/SodukuSolver%20opencv/screenshots/2023-05-07_12-39.png)

![Meme](https://github.com/cls-talha/SudokoSolver-with-opencv-Cpp-and-Pytorch/blob/linux-version/SodukuSolver%20opencv/screenshots/tease.jpg)

## Introduction
This project is a Sudoku Solver that uses deep learning techniques for digit recognition. It is built using OpenCV for image processing and PyTorch for digit classification. The solver is capable of taking an image of a Sudoku puzzle as input and outputting the solved puzzle.

### PyTorch
PyTorch is an open-source machine learning library for Python used to build and train deep learning models. Developed by Facebook's AI Research lab, PyTorch offers a high-level interface for building neural networks and supports both static and dynamic computational graphs. It also provides a wide range of pre-built modules and utilities, making it easy for non-technical users to implement advanced machine learning techniques.

### OpenCV (C++)
OpenCV is an open-source computer vision and machine learning software library written in C++. It provides a wide range of functions and algorithms related to image and video processing, including object detection and motion analysis. It is extensively used in various industries, such as automotive, robotics, and security, as well as in research.

## Purpose
There are several reasons to choose this project, including:

- Enhancing my skills in C++ and Python programming and gaining experience in using deep learning for real-world problems.
- Utilizing computer vision techniques in OpenCV and deep learning models in PyTorch for digit recognition.
- Gaining practical experience in implementing computer vision techniques and building and training deep learning models.
- Impressing my classmates xDD

## Project Structure
This project is divided into two sub-projects:

1. **Training Digit Classifier** (Directory named as "Digit Classifier")
   
   In this part, I trained a Convolutional Neural Net (CNN) model for Digit Classification to recognize digits on the Sudoku Board. To run the Python script, the following versions are required:
   
   - Python 3 version: 3.10.11
   - PyTorch version: 2.0.0
   
   It is preferable to use Google Colab for Deep Learning. You can also access the Google Colab version to train the model from [here](https://colab.research.google.com/drive/1kDC7D7SepjpiCVunYCsn3VkY5p8oe5ME?usp=sharing).

2. **Using Model and Solving Sudoku** (Directory named as "SudokuSolver opencv")

   In this part, I used my own trained model and some other image processing techniques to solve Sudoku puzzles obtained from the camera and overlay the solution on the current frame.

## How to Run this Project
This repository contains two branches of the same project:

- `linux-version` branch uses CMake to build.
- `Main` branch uses Visual Studio Solution to build.

To run this project on your local machine, follow these steps:

1. **Clone this repository or download it as a ZIP** (using the green button above).

   This project requires OpenCV (C++). To install OpenCV:

   ###### Windows
   - Install vcpkg (C++ library manager) by following [this tutorial](https://www.youtube.com/watch?v=wRnjahwxZ8A).
   - Install OpenCV by following [this tutorial](https://eximia.co/hello-opencv-with-c-using-visual-studio-2017-and-vcpkg/).

   ###### Linux
   - Open Terminal and run the following command to install OpenCV in Arch-based distros:
     ```bash
     pacman -S opencv
     ```

2. **Change the directory to the build folder**:

   ###### Windows
   Find the build directory or click on the "exe" file present in the root directory and run it.

   ###### Linux
   Open Terminal, change the directory to the build folder, and run the following command:
   ```bash
   cd build
   ./app

### Credits
- Thanks to Bilal Abid for providing the PNGs and Awaiz for testing the code and providing motivation throughout the project. You guys rock!
- Kudos to Stack Overflow, my go-to resource for coding solutions!
- Big thanks to GitHub, my project's home!
- Grateful to YouTube tutorials, especially Murtaza Hassan, for their invaluable guidance.
- Cheers to ChatGPT, my witty code companion!

### Memes
To add some spice while battling boredom, I took the liberty of creating memes. Enjoy!

![Meme](https://github.com/cls-talha/SudokoSolver-with-opencv-Cpp-and-Pytorch/blob/linux-version/SodukuSolver%20opencv/screenshots/IShowSpeed-Dances-%E2%80%9COne-Kiss%E2%80%9D-Green-Screen-720p.gif)

### License
I don't give a fuck about licenses! You can do whatever you want with this project, just give credits to me. :D
