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
resultsFile = "../Results/auto/"
outputBaseArg = " -output " + resultsFile # OT_ST should be added to the string

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
            os.system(application + confArg + resultsFullDir + " -ot " + str(objectThreshold) + " -st " + str(stimulationThreshold))
 
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
    ax.set_zlim(0, 50)

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
                                                        
# main            
runTracking()
processResults()