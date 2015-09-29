"""
plotFrameRate.py
@Description : Plots a graph to display how the frame rate has varied over time.
@author Helen Harman heh14@aber.ac.uk
@created 21/03/2015
"""
import matplotlib.pyplot as plt
import argparse
import re
import numpy as np

parser = argparse.ArgumentParser()
parser.add_argument('file_gt', help='file to be read')
parser.add_argument('file_found', help='file to be read')
args = parser.parse_args()

# read from the ground truth file
file = open(args.file_gt, 'r')
locationsGt = []
lineNum = 0
for line in file:
    locationsGt.append([])
    for number in re.findall("[0-9]+", line):#line.split(','):
        locationsGt[lineNum].append(int(number))
    lineNum = lineNum + 1
file.close()


# read from the found location file
file = open(args.file_found, 'r')
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

print "\n"

print "=================================================="
print args.file_found
print "Average area match (higher better): " + str(area/len(locationsFound))
print "Number of matched frames (higher better): " + str(numMatchedFrames)
print "Average center difference (lower better): " + str(posDiff/len(locationsFound))
print "=================================================="

"""
plt.figure(1)
plt.subplot(211)
plt.title('Center difference')
index = np.arange(lineNum)
plt.bar(index, positionDiffs, 0.4)

plt.subplot(212)
plt.title('Area matched')
index = np.arange(lineNum)
plt.bar(index, areas, 0.4)
plt.show()
"""
"""

numOfFrames = []
numOfIterations = []
i = 0;
for line in file:
    numOfFrames.append(float(line))
    numOfIterations.append(i)
    i = i+1
file.close()

# plot the graph
plt.plot(numOfIterations, numOfFrames)
plt.ylabel('Number of Frames')
plt.xlabel('Iterations')
plt.show()
"""