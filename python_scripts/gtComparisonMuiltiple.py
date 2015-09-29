"""
.py
@Description :
@author Helen Harman heh14@aber.ac.uk
@created 17/06/2015
"""

import argparse
import os
import re
import numpy as np
import matplotlib.pyplot as plt

parser = argparse.ArgumentParser()
parser.add_argument('file_gt', help='file to be read')
parser.add_argument('directory', help='file to be read')
args = parser.parse_args()


bestDirectoryArea = ""
bestArea = -1
bestDirectoryCenter = ""
bestCenter = 1000
bestDirectoryNumMatchedFrames = ""
bestNumMatchedFrames = -1


# read from the ground truth file
file = open(args.file_gt, 'r')
locationsGt = []
lineNum = 0

#---for x, y, width, height style---#
"""
for line in file:
    
    locationsGt.append([])
        
    for number in re.findall("[0-9.]+", line):#line.split(','):
        locationsGt[lineNum].append(float(number))
    
    lineNum = lineNum + 1
"""
#------------------------------------#

#---for postion as a poportion of the frame size (x, y, width, height) style---#
for line in file:
    if(lineNum != 0):
        locationsGt.append([])
        temp = line.split(None, 1)
        line = temp[1]
        
        for number in re.findall("[0-9.]+", line):#line.split(','):
            locationsGt[lineNum-1].append(float(number))

        locationsGt[lineNum-1][0] = int(320 * locationsGt[lineNum-1][0])
        locationsGt[lineNum-1][1] = int(240 * locationsGt[lineNum-1][1])
        locationsGt[lineNum-1][2] = int(320 * locationsGt[lineNum-1][2])
        locationsGt[lineNum-1][3] = int(240 * locationsGt[lineNum-1][3])
        
    lineNum = lineNum + 1
#-------------------------------------------------------------------------------#

file.close()
print locationsGt

dirs=[]
for root, ds, files in os.walk(args.directory):
    dirs=ds
    break

for dir in dirs:
    #os.system("python gtComparisonMuiltiple.py " + args.file_gt + " " + args.directory + "/locations.txt")
    file_found = args.directory + "/" + dir + "/locations.txt"

    # read from the found location file
    file = open(file_found, 'r')
    locationsFound = []
    #locationsFound.append([])
    #locationsFound[0] = locationsGt[0]
    #lineNum = 1
    lineNum = 0
    for line in file:
        locationsFound.append([])
        for number in re.findall("[0-9]+", line):#line.split(', '):
            locationsFound[lineNum].append(int(number))
        lineNum = lineNum + 1
    file.close()

    #fall()
    posDiff = 0
    positionDiffs = []
    # compare to ground truth
    for i in range(0, len(locationsFound)):
        pos = abs((locationsFound[i][0]+(locationsFound[i][2]/2)) - (locationsGt[i][0]+(locationsGt[i][2]/2)))
        pos = pos + abs((locationsFound[i][1]+(locationsFound[i][3]/2)) - (locationsGt[i][1]+(locationsGt[i][3]/2)))
        positionDiffs.append(pos)
        #np.insert(positionDiffs, positionDiffs.size, pos)
        posDiff = posDiff + pos

    #print posDiff
    #positionDiffsN = np.array(positionDiffs)


    # number of points belonging to A and B
    # divided by
    # all distict elements within the sets
    area = 0
    numMatchedFrames = 0
    areas = []
    for i in range(0, len(locationsFound)):
        xFound = locationsFound[i][0]
        yFound = locationsFound[i][1]
        widthFound = locationsFound[i][2]
        heightFound = locationsFound[i][3]
    
        xGt = locationsGt[i][0]
        yGt = locationsGt[i][1]
        widthGt = locationsGt[i][2]
        heightGt = locationsGt[i][3]
    
        interception = 0;
    
        #print max(xFound, xGt)
    
        maxX = max(xFound, xGt)
        minWidth = min(xFound+widthFound, xGt+widthGt)
        for j in range(maxX, minWidth):
            for k in range(max(yFound, yGt), min(yFound+heightFound, yGt+heightGt)):
                interception = interception + 1

        union = (widthFound*heightFound) + (widthGt*heightGt) - interception
    
        #print "Area : "
        #if union > 0:
        #print float(interception)/float(union)
        area = area + (float(interception)/float(union))
        areas.append(float(interception)/float(union))
        if (float(interception)/float(union)) > 0.5:
            numMatchedFrames = numMatchedFrames + 1

    print "\n"

    print "=================================================="
    print file_found
    print "Average area match (higher better): " + str(area/len(locationsFound))
    print "Number of matched frames (higher better): " + str(numMatchedFrames)
    print "Average center difference (lower better): " + str(posDiff/len(locationsFound))
    print "=================================================="

    if (area/len(locationsFound) > bestArea):
        bestDirectoryArea = file_found
        bestArea = area/len(locationsFound)
    if (numMatchedFrames > bestNumMatchedFrames):
        bestDirectoryNumMatchedFrames = file_found
        bestNumMatchedFrames = numMatchedFrames
    if (posDiff/len(locationsFound) < bestCenter):
        bestDirectoryCenter = file_found
        bestCenter = posDiff/len(locationsFound)

print "=================================================="
print "Best results : "
print "Average area match (higher better): " + str(bestArea) + " in " + bestDirectoryArea
print "Number of matched frames (higher better): " + str(bestNumMatchedFrames) + " in " + bestDirectoryNumMatchedFrames
print "Average center difference (lower better): " + str(bestCenter) + " in " + bestDirectoryCenter
print "=================================================="


