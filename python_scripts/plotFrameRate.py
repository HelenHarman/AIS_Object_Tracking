"""
plotFrameRate.py
@Description : Plots a graph to display how the frame rate has varied over time.
@author Helen Harman heh14@aber.ac.uk
@created 21/03/2015
"""
import matplotlib.pyplot as plt
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('file_name', help='file to be read')
args = parser.parse_args()

# read from the file
file = open(args.file_name, 'r')
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