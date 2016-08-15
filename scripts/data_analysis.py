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


class LogStats:

    def __init__(self, file):

        with open(file) as data_file:    
            data = json.load(data_file)
        
        self.name        = basename(file)
        self.numV        = data["graph property"]["numV"] 
        self.numE        = data["graph property"]["numE"]
        self.numCC       = data["graph property"]["numCC"] 
        numDiam          = data["graph property"]["diameter"].split(",") 
        LDiam            = [float(n) for n in numDiam if n] 
        self.avgDiam     = str(numpy.average(LDiam)) 
        self.varDiam     = str(numpy.var(LDiam))
        numClu           = data["graph property"]["clusterCoeff"].split(",") 
        LClu             = [float(n) for n in numClu if n] 
        self.avgCluCoeff = str(numpy.average(LClu))
        self.varCluCoeff = str(numpy.var(LClu))

        self.clique      = reduce(self, data["graph property"]["clique"])
        self.truss       = reduce(self, data["graph property"]["truss"])


    def reduce(self, stats_str):
        stats_item = {}
        items = stats_str.split("\n")
        for item in items:
            pair = item.split(",")
            stats_item[pair[0]] += int(pair[1])
        return stats_item

    def summary(self):
        return self.name
