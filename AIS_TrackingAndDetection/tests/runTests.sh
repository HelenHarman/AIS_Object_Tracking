#!/bin/sh

#  runTests.sh
#  
#
#  Created by Helen Harman on 02/03/2015.
#

/Users/helen/Qt/5.4/clang_64/bin/qmake -project "QT += testlib" "QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9" "INCLUDEPATH += /usr/local/include/" "LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_nonfree -lopencv_features2d -lopencv_calib3d -lopencv_flann -lopencv_video -L/usr/local/lib"


make clean
make

#TestImageNode.cpp
#./myTests.out