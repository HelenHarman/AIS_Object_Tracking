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
resultsFile = "../Results/OT_ST/"
outputBaseArg = " -output " + resultsFile # OT_ST should be added to the string
gtFileName = "../DataSets/Tiger1/groundtruth_rect.txt"

objectThresholds = [0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95]
stimulationThresholds = [0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95]



def runTracking():
    for objectThreshold in objectThresholds:
        #otResults = []
        for stimulationThreshold in stimulationThresholds:
            if objectThreshold <= stimulationThreshold:
                #otResults.append(0);
                continue
            resultsFullDir = outputBaseArg + str(objectThreshold) + "_" + str(stimulationThreshold)
            os.system(application + confArg + resultsFullDir + " -nat 0 -ot " + str(objectThreshold) + " -st " + str(stimulationThreshold))
 
            #read files into Z
            #file = open(resultsFile + str(objectThreshold) + "_" + str(stimulationThreshold) + "/numberOfArbs.txt", 'r')
            #otResults.append(int(file.readlines()[-1]))
            #file.close()
            
            #print "otResults : " + str(otResults)
        #results.append(otResults)
                       
                                  
def processResults():
    results = getResults()

    fig = plt.figure()
    ax = fig.gca(projection='3d')
    
    X, Y = np.meshgrid(stimulationThresholds, objectThresholds)

    surf = ax.plot_surface(X, Y, results, rstride=1, cstride=1, cmap=cm.coolwarm,
            linewidth=0, antialiased=False)
    ax.set_zlim(0, 250)

    fig.colorbar(surf, shrink=0.5, aspect=5)
    
    ax.set_xlabel('Stimulation Threshold')
    ax.set_ylabel('Object Threshold')
    ax.set_zlabel('Number of ARBs')
    
    plt.show()

def getResults():
    results = []
    for objectThreshold in objectThresholds:
        otResults = []
        for stimulationThreshold in stimulationThresholds:
            if objectThreshold <= stimulationThreshold:
                otResults.append(0);
                continue
            #read files into Z
            file = open(resultsFile + str(objectThreshold) + "_" + str(stimulationThreshold) + "/numberOfArbs.txt", 'r')
            otResults.append(int(file.readlines()[-1]))
            file.close()
            
            print "otResults : " + str(otResults)
        results.append(otResults)
    return results
    
    
    
    
    
    
def processResultsMatchedFrames():
    results = getResultsMatchedFrames()

    fig = plt.figure()
    ax = fig.gca(projection='3d')
    
    X, Y = np.meshgrid(stimulationThresholds, objectThresholds)

    surf = ax.plot_surface(X, Y, results, rstride=1, cstride=1, cmap=cm.coolwarm,
            linewidth=0, antialiased=False)
    ax.set_zlim(0, 300)

    fig.colorbar(surf, shrink=0.5, aspect=5)
    
    ax.set_xlabel('Stimulation Threshold')
    ax.set_ylabel('Object Threshold')
    ax.set_zlabel('Average center difference')
    
    plt.show()

def getResultsMatchedFrames():
    results = []
    for objectThreshold in objectThresholds:
        otResults = []
        for stimulationThreshold in stimulationThresholds:
            if objectThreshold <= stimulationThreshold:
                otResults.append(0);
                continue
            #read files into Z
            otResults.append(numberOfMatchedFrames(resultsFile + str(objectThreshold) + "_" + str(stimulationThreshold) + "/locations.txt"))
            
            print "otResults : " + str(otResults)
        results.append(otResults)
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
            
    #return(numMatchedFrames)#Number of matched frames (higher better)
    #return(area/len(locationsFound))#Average area match (higher better)
    return(posDiff/len(locationsFound))#Average center difference (lower better)



    
                                                        
# main            
#runTracking()
#processResults()
processResultsMatchedFrames()