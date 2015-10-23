"""

"""
import matplotlib.pyplot as plt
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import argparse
import re
import numpy as np
import os

application = "../build/AIS_Debug_build/AIS_TrackingAndDetection.app/Contents/MacOS/AIS_TrackingAndDetection"
confArg = " -conf ../DataSets/tiger1.ais_config"
resultsFile = "../Results/NAT/"
outputBaseArg = " -output " + resultsFile # OT_ST should be added to the string

gtFileName = "../DataSets/Tiger1/groundtruth_rect.txt"

NATs = [0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95]
objectThreshold = 1
stimulationThreshold = 0


def runTracking():
    for NAT in NATs:
        resultsFullDir = outputBaseArg + str(NAT)
        os.system(application + confArg + resultsFullDir + " -ot " + str(objectThreshold) + " -st " + str(stimulationThreshold) + " -nat " + str(NAT))
 
                                  
def processResults():
    results = getResults()

    plt.plot(NATs, results)
    plt.ylabel('Number of ARBs')
    plt.xlabel('NAT')
    plt.show()

def getResults():
    results = []
    for NAT in NATs:
        file = open(resultsFile + str(NAT) + "/numberOfArbs.txt", 'r')
        results.append(int(file.readlines()[-1]))
        file.close()

    return results
    

def processResultsMatchedFrames():
    results = getResultsMatchedFrames()

    plt.plot(NATs, results)
    plt.ylabel('Matched Frames')
    plt.xlabel('NAT')
    plt.show()
    
def getResultsMatchedFrames():
    results = []
    for NAT in NATs:
            #read files into Z
        results.append(numberOfMatchedFrames(resultsFile + str(NAT) + "/locations.txt"))

    return results    
    
    
    
def numberOfMatchedFrames(fileName):
    file = open(gtFileName, 'r')
    locationsGt = []
    lineNum = 0
    for line in file:
        locationsGt.append([])
        for number in re.findall("[0-9]+", line):#line.split(','):
            locationsGt[lineNum].append(int(number))
        lineNum = lineNum + 1
    file.close()


    # read from the found location file
    file = open(fileName, 'r')
    locationsFound = []
    locationsFound.append([])
    locationsFound[0] = locationsGt[0]
    lineNum = 1
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
    for i in range(0, len(locationsFound)-1):
        #print (i)
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
    for i in range(0, len(locationsFound)-1):
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
            
    return(numMatchedFrames)#Number of matched frames (higher better)
    #return(area/len(locationsFound))#Average area match (higher better)
    #return(posDiff/len(locationsFound))#Average center difference (lower better)



    
                                                        
# main            
runTracking()
processResults()
processResultsMatchedFrames()