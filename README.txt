# README #

### About ###

This directory contains the work done for my(Helen Harman's) dissertation "Artificial Immune System for Tracking and Detecting Objects in Real-Time".

Version 1.0
Available at : https://bitbucket.org/HelenHarman/dissertation


### Directories and Files###

* heh14_FinalReport_2015.pdf
* AIS_TrackingAndDetection : The software produced during the project.
* AIS_TrackingAndDetection/html : The Doxygen output
* AIS_TrackingAndDetection/tests : The unit tests
* python_scripts : The python scripts used to produce diagrams of the network; and graphs showing how the number of ARBs in the network changes overtime.
* data : Contains the test videos and configuration files that can be loaded by AIS_TrackingAndDetection.
* staticCodeAnalysis
    * staticCodeAnalysis/StaticCodeAnalysisProject : The ConQAT eclipse project for running the static code analysis
    * staticCodeAnalysis/output : The HTML output from running the static code analysis


### How to run AIS_TrackingAndDetection ###

This application has been built and tested on OSX-10.9.5 other OS's may vary.
For OSX clicking AIS_TrackingAndDetection.app should run the application.

Dependencies include :
* OpenCV 2.4,
* GSL,
* C++11,
* Qt

This project was created and compiled using QtCreator. The AIS_TrackingAndDetection/AIS_TrackingAndDetection.pro file should be edited for your operating system.


### Running the Unit Tests ###

Copy AutoTest.h from : http://qtcreator.blogspot.co.uk/2009/10/running-multiple-unit-tests.html into external-libs/AutoTest.h

The AIS_TrackingAndDetection/tests/tests.pro file should be edited for your operating system to run the unit tests using QtCreator.


### Running the Python Scripts ###

Run the following command :
    > python createResults.py directoryContainingOutputFromAIS_TrackingAndDetection/


### How to generate the Doxygen output ###

Use the following command to generate the Doxygen HTML :
    > doxygen AIS_TrackingAndDetection/Doxygen


### Contact ###

Helen Harman (heh14@aber.ac.uk)

