
import matplotlib.pyplot as plt
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('file_name', help='file to be read')
args = parser.parse_args()

# read from the file
file = open(args.file_name, 'r')
distances = []
numOfIterations = []
i = 0;
for line in file:
    distances.append(float(line.strip()))
    numOfIterations.append(i)
    i = i+1
file.close()

# plot the graph
plt.plot(numOfIterations, distances)
plt.ylabel('Distance')
plt.xlabel('Frame')
plt.show()