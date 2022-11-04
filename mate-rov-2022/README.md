# third_ROV_ML

This repository contains algorithms for the Machine Learning and Computer Vision part of the ROV. The file `politocean_vision_tasks` contains a list of the Computer Vision tasks to perform for the competition, explained in the following.

## Line detection
In the `line detection` folder, there are algorithms to perform line detection and relative examples. The file `methods` contains a list of useful links to perform line detection. The file `hough_transform.py` contains an implementation of the Hough Transform method for line detection (no deep learning, just image processing). In particular, by specifying the name of the image in the file and by selecting a threshold for the algorithm (which determines how many lines will be selected), the script saves an image with the lines depicted. The file `webcam.py` applies the Hough Transform algorithm in real time to the images coming from the webcam.

## Evaluation of the position of the float
The folder `float_position` contains a script that allows the evaluation of the final position of the float. In particular, the function takes in input the image with the grid and the initial position of the float, then the parameters indicating the speed, the angle and the time and outputs an image showing the final position of the float in the grid.

## Detection of mort fish
The Google Colab: https://colab.research.google.com/drive/125fCriw_GCeHj1Vg1EJfDKAJ4r7V2cqY?usp=sharing contains some experiments about fish detection.


