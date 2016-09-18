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
#   stplaydog   08/27/16 - Add data plot functions 
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
        
        name_items       = basename(file).replace(".json", "").split("_")
        self.name        = name_items[2]+"_"+name_items[3]+"_"+name_items[4]
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

        self.clique      = self.reduce(data["content"]["graph property"]["clique"], True)
        self.truss       = self.reduce(data["content"]["graph property"]["truss"],  True)
        self.core        = self.reduce(data["content"]["graph property"]["dbscan"], True)
        self.dbscan      = self.reduce(data["content"]["graph property"]["core"],   True)

        self.cliqueSize  = self.reduce(data["content"]["graph property"]["clique"], False)
        self.trussSize   = self.reduce(data["content"]["graph property"]["truss"],  False)
        self.coreSize    = self.reduce(data["content"]["graph property"]["dbscan"], False)
        self.dbscanSize  = self.reduce(data["content"]["graph property"]["core"],   False)

        self.cliqueSize  = self.getSizeMean(self.clique, self.cliqueSize)
        self.trussSize   = self.getSizeMean(self.truss,  self.trussSize)
        self.coreSize    = self.getSizeMean(self.core,   self.coreSize)
        self.dbscanSize  = self.getSizeMean(self.dbscan, self.dbscanSize)


    def reduce(self, stats_str, if_freq):
        stats_item = {} 
        items = stats_str.split("\n")
        for item in items:
            if item == "":
                continue
            pair = item.split(",")
            if int(pair[0]) in stats_item:
                if if_freq:
                    stats_item[int(pair[0])] += 1 
                else:
                    stats_item[int(pair[0])] += int(pair[1])
            else:
                if if_freq:
                    stats_item[int(pair[0])] = 1 
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

    def getSizeMean(self, freq, size):
        for i in range(0, len(freq['y'])):
            size['y'][i] = float(size['y'][i]) / float(freq['y'][i])
        return size


    def plot(self, ofname):
        plt.plot(self.clique['x'], self.clique['y'], color='k', linestyle='-', marker=',', label = 'k-clique')
        plt.plot(self.truss['x'],  self.truss['y'],  color='k', linestyle='-', marker='.', label = 'k-truss')
        plt.plot(self.dbscan['x'], self.clique['y'], color='k', linestyle='-', marker='v', label = 'dbscan')
        plt.plot(self.core['x'],   self.core['y'],   color='k', linestyle='-', marker='o', label = 'k-core')
        plt.legend( loc='lower right', numpoints = 1, prop={'size':15} )
        plt.tick_params(labelsize=15)
        plt.xlabel("K", fontsize=20)
        plt.ylabel("number of cohesive subgraphs", fontsize=20)
        plt.tight_layout()
        plt.savefig(ofname)
        plt.close()

    def summary(self):
        list = [self.name,             str(self.numV),    str(self.numE), \
                str(self.numCC),       str(round(self.avgDiam,2)), str(round(self.varDiam,2)), \
                str(round(self.avgCluCoeff,2)), str(round(self.varCluCoeff,2)) ]
        return ",".join(list)

class JsonStatsCollections:

    def __init__(self, dir, prefix):
        os.chdir(dir)
        self.coll = {}
        for file in glob.glob("*.json"):
            try:
                if file.find(prefix) != -1:
                    stats = JsonStats(file)  
                    self.coll[file] = stats
            except:
                print "Data Corruption in " + file

    def plot(self, ofname, is_freq):
        colors = ['k', 'b', 'r', 'g']
        i = 0
        for c in self.coll: 
            if is_freq == False:
                plt.plot(self.coll[c].cliqueSize['x'], self.coll[c].cliqueSize['y'], color=colors[i], linestyle='--', marker=',', label = self.coll[c].name+'-clique')
                plt.plot(self.coll[c].trussSize['x'],  self.coll[c].trussSize['y'],  color=colors[i], linestyle='--', marker='.', label = self.coll[c].name+'-truss')
                plt.plot(self.coll[c].coreSize['x'],   self.coll[c].coreSize['y'],   color=colors[i], linestyle='-',  marker='v', label = self.coll[c].name+'-core')
                plt.plot(self.coll[c].dbscanSize['x'], self.coll[c].dbscanSize['y'], color=colors[i], linestyle='-',  marker='o', label = self.coll[c].name+'-dbscan')
            elif is_freq == True:
                plt.plot(self.coll[c].clique['x'], self.coll[c].clique['y'], color=colors[i], linestyle='--', marker=',', label = self.coll[c].name+'-clique')
                plt.plot(self.coll[c].truss['x'],  self.coll[c].truss['y'],  color=colors[i], linestyle='--', marker='.', label = self.coll[c].name+'-truss')
                plt.plot(self.coll[c].core['x'],   self.coll[c].core['y'],   color=colors[i], linestyle='-',  marker='v', label = self.coll[c].name+'-core')
                plt.plot(self.coll[c].dbscan['x'], self.coll[c].dbscan['y'], color=colors[i], linestyle='-',  marker='o', label = self.coll[c].name+'-dbscan')
            i += 1
        plt.legend( loc=0, numpoints = 1, prop={'size':15} )
        plt.tick_params(labelsize=15)
        plt.xlabel("K", fontsize=20)
        plt.ylabel("number of cohesive subgraphs", fontsize=20)
        plt.tight_layout()
        plt.savefig(ofname)
        plt.close()

def main(argv):

    parser = argparse.ArgumentParser()
    group = parser.add_mutually_exclusive_group()
    group.add_argument("-f", "--file", action="store_true")
    group.add_argument("-d", "--directory", action="store_true")
    group.add_argument("-p", "--prefix", action="store_true")
    parser.add_argument("fname", help="file/directory name")
    args = parser.parse_args()

    if args.file:
        stats  = JsonStats(args.fname)
        print stats.summary()
        ofname = args.fname.replace('json', '') + 'png'
        stats.plot(ofname)
    elif args.directory:
        os.chdir(args.fname)
        for file in glob.glob("*.json"):
            try:
                stats = JsonStats(file)  
                print stats.summary()
                ofname = file.replace("json", "") + "png"
                stats.plot(ofname)
            except:
                print "Data Corruption in " + file
    elif args.prefix:
        config = open(args.fname)
        lines = config.readlines()
        for line in lines:
            if line.find("directory") != -1:
                dir = line.strip().split(" ")[1]
            if line.find("prefix") != -1:
                pfx = line.strip().split(" ")[1]
        coll = JsonStatsCollections(dir, pfx)
        oname1 = dir + pfx + '.png'
        oname2 = dir + pfx + '_size.png'
        coll.plot(oname2, False)
        coll.plot(oname1, True)

if __name__ == "__main__":
    main(sys.argv)
