"""
showResults.py
@Description : Runs all the python scripts that create the graphs for the AIS tracking and detecting experiments.
@author Helen Harman heh14@aber.ac.uk
@created 21/04/2015
"""


import os
from subprocess import Popen
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('dir_name', help='directory to be read')
args = parser.parse_args()

os.system("python createNetworkDiagram.py " + args.dir_name + "/network.txt " + args.dir_name + "/network.diag")
# Popen used so that both graphs are displayed at same time
runningCmd = Popen(["python", "plotFrameRate.py", args.dir_name + "/frameRate.txt"])
os.system("python plotNumArbs.py " + args.dir_name + "/numberOfArbs.txt")
runningCmd.terminate()