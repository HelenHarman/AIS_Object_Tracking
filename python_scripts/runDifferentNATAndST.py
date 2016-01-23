"""
Runs the AIS tracking using different Network Affiliation Thresholds (NATs) and Stimulation Thresholds (STs).
Compares the results to the locations given in the Ground Truth (GT) file
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
resultsFile = "../Results/NAT_ST/"
numberOfInitialARBs = "-NIA 5"
outputBaseArg = " -output " + resultsFile # OT_ST should be added to the string

gtFileName = "../DataSets/Tiger1/groundtruth_rect.txt"

NATs = [0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95]
stimulationThresholds =[0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95]

###########################################
######       Runs AIS tracking         ####
###########################################

def runTracking():
    for NAT in NATs:
        for stimulationThreshold in stimulationThresholds:
            if NAT <= stimulationThreshold:
                continue
            resultsFullDir = outputBaseArg + str(NAT) + "_" + str(stimulationThreshold)
            os.system(application + confArg + resultsFullDir + " -ot 1 -nat " + str(NAT) + " -st " + str(stimulationThreshold))
                       
###########################################   
    
    
###########################################
######      Comparison to the GT       ####
###########################################    

##
# For each of the NAT and ST used compares the results to the GT
def processResults():
    resultsFramesMatched = []
    resultsAreaMatched = []
    resultsCenterDiff = []
    
    for NAT in NATs:
        otResultsFramesMatched = []
        otResultsAreaMatched = []
        otResultsCenterDiff = []
        for stimulationThreshold in stimulationThresholds:
            if NAT <= stimulationThreshold:
                otResultsFramesMatched.append(0);
                otResultsAreaMatched.append(0);
                otResultsCenterDiff.append(0);
                continue
            
            
            framesMatched, areaMatched, centerDiff = processSingleResult(resultsFile + str(NAT) + "_" + str(stimulationThreshold) + "/locations.txt")
            otResultsFramesMatched.append(framesMatched);
            otResultsAreaMatched.append(areaMatched);
            otResultsCenterDiff.append(centerDiff);
            
        resultsFramesMatched.append(otResultsFramesMatched)
        resultsAreaMatched.append(otResultsAreaMatched)
        resultsCenterDiff.append(otResultsCenterDiff)
        
    plotGraph(resultsFramesMatched, "Number of frames matched")
    plotGraph(resultsAreaMatched, "Average area matched")
    plotGraph(resultsCenterDiff, "Average center difference")
    

##
# Performs the comparison to the GT for one run the AIS tracking   
# Returns : Number of matched frames (higher better),  Average area match (higher better), Average center difference (lower better)   
def processSingleResult(fileName):    
    locationsGt = readGTFile()
    locationsFound = readFoundLocationsFile(fileName, locationsGt)

    posDiff = 0
    positionDiffs = []

    # number of points belonging to A and B
    # divided by
    # all distict elements within the sets
    area = 0.0
    numMatchedFrames = 0
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

        # Calculate the area of the frame that matches the GT 
        maxX = max(xFound, xGt)
        minWidth = min(xFound+widthFound, xGt+widthGt)
        for j in range(maxX, minWidth):
            for k in range(max(yFound, yGt), min(yFound+heightFound, yGt+heightGt)):
                interception = interception + 1

        union = (widthFound*heightFound) + (widthGt*heightGt) - interception

        area = area + (float(interception)/float(union))
        
        # does the frame found match the GT?
        if (float(interception)/float(union)) > 0.5:
            numMatchedFrames = numMatchedFrames + 1
          
        # calculate the ceneter difference      
        pos = abs((locationsFound[i][0]+(locationsFound[i][2]/2)) - (locationsGt[i][0]+(locationsGt[i][2]/2)))
        pos = pos + abs((locationsFound[i][1]+(locationsFound[i][3]/2)) - (locationsGt[i][1]+(locationsGt[i][3]/2)))
        positionDiffs.append(pos)
        posDiff = posDiff + pos
            
    return (numMatchedFrames), (area/len(locationsFound)),(posDiff/len(locationsFound))
 
       
##
# Stores the GT locations into an array
def readGTFile():
    file = open(gtFileName, 'r')
    locationsGt = []
    lineNum = 0
    for line in file:
        locationsGt.append([])
        for number in re.findall("[0-9]+", line):#line.split(','):
            locationsGt[lineNum].append(int(number))
        lineNum = lineNum + 1
    file.close()
    return locationsGt
  
##
# Stores the found locations into an 2D array     
def readFoundLocationsFile(fileName, locationsGt):
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
    return locationsFound   
        
        
    
def plotGraph(results, zlabel):
    fig = plt.figure()
    ax = fig.gca(projection='3d')
    
    X, Y = np.meshgrid(stimulationThresholds, NATs)

    surf = ax.plot_surface(X, Y, results, rstride=1, cstride=1, cmap=cm.coolwarm,
            linewidth=0, antialiased=False)
    ax.set_zlim(0, 300)

    fig.colorbar(surf, shrink=0.5, aspect=5)
    
    ax.set_xlabel('Stimulation Threshold')
    ax.set_ylabel('NAT')
    ax.set_zlabel(zlabel)
    
    plt.show()




###########################################

############################################################
###### Plots the end number of ARBS for each ST and NAT ####
############################################################

##
# Show a graph the results                                                             
def showEndNumberOfARBs():
    results = getResults()

    fig = plt.figure()
    ax = fig.gca(projection='3d')
    
    X, Y = np.meshgrid(stimulationThresholds, NATs)

    surf = ax.plot_surface(X, Y, results, rstride=1, cstride=1, cmap=cm.coolwarm,
            linewidth=0, antialiased=False)
    ax.set_zlim(0, 250)

    fig.colorbar(surf, shrink=0.5, aspect=5)
    
    ax.set_xlabel('Stimulation Threshold')
    ax.set_ylabel('NAT')
    ax.set_zlabel('Number of ARBs')
    
    plt.show()
    
##
# 
def getResults():
    results = []
    for NAT in NATs:
        otResults = []
        for stimulationThreshold in stimulationThresholds:
            if NAT <= stimulationThreshold: 
                otResults.append(0);
                continue
            #read files into Z
            file = open(resultsFile + str(NAT) + "_" + str(stimulationThreshold) + "/numberOfArbs.txt", 'r')
            otResults.append(int(file.readlines()[-1]))
            file.close()
            
            print "otResults : " + str(otResults)
        results.append(otResults)
    return results
    
###########################################
                                                        
# main            
#runTracking()
#showEndNumberOfARBs()
processResults()

###########################################