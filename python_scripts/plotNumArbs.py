"""
plotNumArbs.py
@Description : Plots a graph to display how the number of ARBs in the network have varied over time.
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
numArbs = []
numOfIterations = []
i = 0;
for line in file:
    numArbs.append(int(line))
    numOfIterations.append(i)
    i = i+1
file.close()

# plot the graph
plt.plot(numOfIterations, numArbs)
plt.ylabel('Number of ARBs')
plt.xlabel('Iterations')
plt.show()