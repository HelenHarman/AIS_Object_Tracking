"""
createNetworkDiagram.py
@Description : Creates a diagram showing the AIN.
@author Helen Harman heh14@aber.ac.uk
@created 21/03/2015
"""
import argparse
import os

parser = argparse.ArgumentParser()
parser.add_argument('file_name', help='file to be read')
parser.add_argument('output_file_name', help='file to be written')
args = parser.parse_args()

# read in the network
file = open(args.file_name, 'r')
nodes = []
links = {}
linkStartId = 97
for line in file:
    splitLine = line.split(":")
    splitLine[0]
    nodes.append(int(splitLine[0]))
    
    splitLine = splitLine[1].split(",")
    links[nodes[len(nodes)-1]] = []
    #print splitLine
    for node in splitLine :
        if '\n' not in node :
            if nodes[len(nodes)-1] < int(node.strip()):
                links[nodes[len(nodes)-1]].append(chr(int(node.strip()) + linkStartId));
file.close()

# write out the diag file
dirName = os.path.dirname(args.file_name)
file = open(args.output_file_name, 'w')
file.write("blockdiag { \n")

for node in nodes: # create each node
    #file.write(chr(int(node) + linkStartId) + " [height = 40, width = 40, label = \"\", background = \"" + os.getcwd() + "/" + dirName  + "/" + str(node) + ".png\"];\n")
    file.write(chr(int(node) + linkStartId) + " [height = 40, width = 40, label = \"\", background = \"" + dirName  + "/" + str(node) + ".png\"];\n")

for key in links: # add the links between the nodes
    for node in links[key]:
        file.write(chr(int(key) + linkStartId) + " -> " + str(node) + "[dir = none];\n") #C -> A;

file.write("}")
file.close()

# run blockgiag to produce the diagram
os.system("blockdiag " + args.output_file_name)
