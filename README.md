# OpenCV-Random-Shape-Generator
This module creates randomly three geometric shapes, namely circles, rectangles, and triangles. All the parameters of these shapes are selected randomly by the algorithm. This code initially was developed to generate shapes used for training a [Keras-RetinaNet](https://github.com/fizyr/keras-retinanet). Therefore, its also saves the position of the shapes as well as the size and label. The required information, including labels and names of images, is stored in a .csv file.

In order to get more detail about the source code please refer to [help file](https://github.com/mortezajalalat/OpenCV-Random-Shape-Generator/blob/master/Help.pdf) file and the comments put inside the source code.

Generally, The source code consists of two main sections:

1) A C++ class named CShapeCreator, which is resposible for creating random shapes.

2) A source.cpp file, which makes an object from CShapeCreator class and sets the required parameters, and in generall manages all the procedure.

