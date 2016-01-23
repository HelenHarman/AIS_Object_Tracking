# README #

### About ###

This repository contains the code for “Artificial Immune System for Tracking and Detecting Objects in Real-Time".


### Directories and Files###

* AIS_TrackingAndDetection 
* AIS_TrackingAndDetection/html : The Doxygen output
* AIS_TrackingAndDetection/tests : The unit tests
* python_scripts 
* DataSets : Contains the test videos and configuration files that can be loaded by AIS_TrackingAndDetection.

### How to run AIS_TrackingAndDetection ###

This application has been built and tested on OSX-10.9.5 other OS's may vary.


Dependencies include :
* OpenCV 2.4,
* GSL,
* C++11,
* Qt

This project was created and compiled using QtCreator. The AIS_TrackingAndDetection/AIS_TrackingAndDetection.pro file should be edited for your operating system.




### Python Scripts ###
The python scripts are used to run the AIS tracking on multiple threshold values, perform a comparison to the GT, and to plot graphs of the results.

To run of different NAT and ST values use :

	> python runDifferentNATAndST.py

(Note : before running the application(if you are not using OS-X) you will need to edit the application path within the python script.)


Dependencies include :
* numpy
* matplotlib
* mplot3d (http://matplotlib.org/1.3.0/mpl_toolkits/mplot3d/index.html#toolkit-mplot3d-index)

### How to generate the Doxygen output ###

Use the following command to generate the Doxygen HTML :

    > doxygen AIS_TrackingAndDetection/Doxygen


### Contact ###

Helen Harman (heh14@aber.ac.uk)

