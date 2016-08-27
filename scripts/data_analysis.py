#
# Copy right YMSys, 2015,2016 Zhaoming Yin
#
# @brief    This script performs data analytics
#           1) it can list:
#              name, numV, numE, numCC, avgDiam, varDiam, avgCluCoeff, varCluCoeff
#           2) it can draw distribution of 
#              clique, truss
#           
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   08/20/16 - Implementation 
#   stplaydog   08/07/16 - Creation
#


import sys
import json
import numpy
import datetime
import time
import argparse
from enum import Enum
import glob, os
import re
from os.path import basename

from ggplot import *
import pandas as pd


class JsonStats:

    def __init__(self, file):

        with open(file) as data_file:    
            data = json.load(data_file)
        
        self.name        = basename(file).replace(".json", "")
        self.numV        = data["content"]["graph property"]["numV"] 
        self.numE        = data["content"]["graph property"]["numE"]
        self.numCC       = data["content"]["graph property"]["numCC"] 
        numDiam          = data["content"]["graph property"]["diameter"].split(",") 
        LDiam            = [float(n) for n in numDiam if n] 
        self.avgDiam     = str(numpy.average(LDiam)) 
        self.varDiam     = str(numpy.var(LDiam))
        numClu           = data["content"]["graph property"]["clusterCoeff"].split(",") 
        LClu             = [float(n) for n in numClu if n] 
        self.avgCluCoeff = str(numpy.average(LClu))
        self.varCluCoeff = str(numpy.var(LClu))

        self.clique      = self.reduce(data["content"]["graph property"]["clique"])
        self.truss       = self.reduce(data["content"]["graph property"]["truss"])


    def reduce(self, stats_str):
        stats_item = [[0,0], [10,0], [50,0], [100,0], [500,0]]
        items = stats_str.split("\n")
        for item in items:
            pair = item.split(",")
            if int(pair[0]) > 0 and int(pair[0]) < 10:
                stats_item[0][1] += int(pair[1])
            else:
                for i in range(5):
                    if int(pair[0]) > stats_item[i-1][0] and \
                       int(pair[0]) < stats_item[i][0]:
                           stats_item[i][1] += int(pair[1])
        return stats_item

    def plot(self):
        

    def summary(self):
        list = [self.name,             str(self.numV),    str(self.numE), \
                str(self.numCC),       str(self.avgDiam), str(self.varDiam), \
                str(self.avgCluCoeff), str(self.varCluCoeff)]
        return ",".join(list)

def main(argv):

    parser = argparse.ArgumentParser()
    group = parser.add_mutually_exclusive_group()
    group.add_argument("-f", "--file", action="store_true")
    group.add_argument("-d", "--directory", action="store_true")
    parser.add_argument("fname", help="file/directory name")
    args = parser.parse_args()

    if args.file:
        stats  = JsonStats(args.fname)
        print stats.summary()
    elif args.directory:
        os.chdir(args.fname)
        for file in glob.glob("*.json"):
            print "process: " + file
            try:
                stats = JsonStats(file)  
                print stats.summary()
            except:
                print "Data Corruption in " + file

if __name__ == "__main__":
    main(sys.argv)
