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

import math
import matplotlib
matplotlib.use('agg')
import matplotlib.pyplot as plt


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
        stats_item = {} 
        items = stats_str.split("\n")
        for item in items:
            pair = item.split(",")
            if int(pair[0]) in stats_item:
                stats_item[int(pair[0])] += int(pair[1])
            else:
                stats_item[int(pair[0])] = int(pair[1])
        X = [0] * len(stats_item)
        Y = [0] * len(stats_item)
        i=0
        for key in stats_item:
            X[i] = int(key)
            Y[i] = stats_item[key]
            i+=1

        return {'x':X,'y':Y} 

    def plot(self):
        # write to csv files first
        print self.clique
        print self.truss
        plt.plot(self.clique['x'], self.clique['y'], color='k', linestyle='-', marker=',', label = 'LK(2,3), delta=2')
        plt.plot(self.truss['x'],  self.truss['y'],  color='k', linestyle='-', marker='.', label = '2-OPT, delta=2')
        #plt.legend( loc='lower right', numpoints = 1, prop={'size':15} )
        #plt.tick_params(labelsize=15)
        plt.ylabel("accumulated distance", fontsize=20)
        plt.xlabel("actual # evolutionary events", fontsize=20)
        #plt.tight_layout()
        plt.savefig("med2.png")

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
        stats.plot()
    elif args.directory:
        os.chdir(args.fname)
        for file in glob.glob("*.json"):
            try:
                stats = JsonStats(file)  
                print stats.summary()
                stats.plot()
            except:
                print "Data Corruption in " + file

if __name__ == "__main__":
    main(sys.argv)
