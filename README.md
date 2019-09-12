# OpenCV-Random-Geometric-Shape-Generator
This module creates randomly three geometric shapes, namely circles, rectangles, and triangles. All the parameters of these shapes are selected randomly by the algorithm. This code initially was developed to generate shapes used for training a [Keras-RetinaNet](https://github.com/fizyr/keras-retinanet). Therefore, its also saves the position of the shapes as well as the size and label. The required information, including labels and names of images, is stored in a .csv file.

## Overall Code Structure

Generally, The source code consists of two main sections:

1) A C++ class named CShapeCreator, which is resposible for creating random shapes.

2) A source.cpp file, which makes an object from CShapeCreator class and sets the required parameters, and in generall manages all the procedure.

## Pre-built Binary Usage Help

A pre-built binary of the code is available [here](https://github.com/mortezajalalat/OpenCV-Random-Geometric-Shape-Generator/blob/master/Pre-Built%20Binaries.zip) for those unwilling to compile the code from scratch.

Before running the source code, a sample of algorithm output can be checked by the file named "[Output Shape Samples.png](https://github.com/mortezajalalat/OpenCV-Random-Shape-Generator/blob/master/Output%20Shape%20Samples.png)".

In order to get more detail about the source code please refer to [help file](https://github.com/mortezajalalat/OpenCV-Random-Shape-Generator/blob/master/Help.pdf) and the comments put inside the source code.

## An Easy Way for your Feedback
I gratefully accept any bug report or suggestion for improving the performance and making the code more reusable. Please feel free to contact me via m.jalalat@gmail.com E-mail.
