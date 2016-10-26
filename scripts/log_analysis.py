#
# Copy right YMSys, 2015,2016 Zhaoming Yin
#
# @brief    This script performs log analytics, as for now, 
#           only support the computation time for now.
#           
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   08/13/16 - Implementation 
#   stplaydog   08/12/16 - Creation
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

class TimerType(Enum):
    START   = 0
    END     = 1
    SUMMARY = 2 
class SetState(Enum):
    UNSET = -1
    ZERO  = 0 


class DoubleTimeSetException(Exception):
    pass
class StartTimeUnsetException(Exception):
    pass
class TimeIncompleteException(Exception):
    pass
class MalDataException(Exception):
    pass
class EndTimeShouldBeLaterThanStartTime(Exception):
    pass

class LogStats:

    def __init__(self, file):

        self.read_data          = [SetState.UNSET, SetState.UNSET, SetState.ZERO]
        self.build_model        = [SetState.UNSET, SetState.UNSET, SetState.ZERO]
        self.build_edge_list    = [SetState.UNSET, SetState.UNSET, SetState.ZERO]
        self.build_edge_listCC  = [SetState.UNSET, SetState.UNSET, SetState.ZERO]
        self.compute_truss      = [SetState.UNSET, SetState.UNSET, SetState.ZERO]
        self.compute_core       = [SetState.UNSET, SetState.UNSET, SetState.ZERO]
        self.compute_dbscan     = [SetState.UNSET, SetState.UNSET, SetState.ZERO]
        self.compute_graph_prop = [SetState.UNSET, SetState.UNSET, SetState.ZERO]
        self.done_all           = False

        for line in file:
            if line.find("Reading data..") != -1:
                self.setStartTime(self.read_data, line)
            elif line.find("Building model") != -1:
                self.setStartTime(self.build_model, line)
                self.setEndTime(self.read_data, line)
            elif line.find("Let's build edge list first") != -1:
                self.setStartTime(self.build_edge_list, line)
                self.setEndTime(self.build_model, line)
            elif line.find("Build edge list based on connected components") != -1:
                self.setStartTime(self.build_edge_listCC, line)
                self.setEndTime(self.build_edge_list, line)
            elif line.find("number of CCs in total, start processing") != -1:
                self.setEndTime(self.build_edge_listCC, line)
            elif re.search("Computing the .*th CC", line):
                self.setStartTime(self.compute_truss, line)
                if line.split(" ")[6].replace("th", "") != "0":
                    self.setEndTime(self.compute_graph_prop, line)
            elif re.search("Start performing core decomposition", line):
                self.setStartTime(self.compute_core, line)
                self.setEndTime(self.compute_truss, line)
            elif re.search("Start performing dbscan decomposition", line):
                self.setStartTime(self.compute_dbscan, line)
                self.setEndTime(self.compute_core, line)
            elif re.search("Start performing graph computations", line):
                self.setStartTime(self.compute_graph_prop, line)
                self.setEndTime(self.compute_dbscan, line)
            elif re.search("Finishing OPTKIT", line):
                self.setEndTime(self.compute_graph_prop, line)
                self.done_all = True
                
    def setStartTime(self, which_item, timeStr): 
        if which_item[TimerType.START] != SetState.UNSET:
            raise DoubleTimeSetException("Double set start time!")
        else:
            which_item[TimerType.START] = self.parseTime(timeStr)

    def setEndTime(self, which_item, timeStr): 
        if which_item[TimerType.END] != SetState.UNSET:
            raise DoubleTimeSetException("Double set end time!")
        elif which_item[TimerType.START] == SetState.UNSET:
            raise StartTimeUnsetException("Start time is not set!")
        else:
            which_item[TimerType.END]      = self.parseTime(timeStr)
            if which_item[TimerType.END] - which_item[TimerType.START] < 0:
                raise EndTimeShouldBeLaterThanStartTime("End time should be later than start time" + timeStr)
            which_item[TimerType.SUMMARY] += which_item[TimerType.END] - \
                                             which_item[TimerType.START]
            which_item[TimerType.START] = SetState.UNSET
            which_item[TimerType.END]   = SetState.UNSET

    def parseTime(self, timeStr):
        month       = timeStr.split(" ")[0][1:3]
        day         = timeStr.split(" ")[0][3:5]
        timeContent = month+","+day+","+timeStr.split(" ")[1]
        timeMicroSecond = datetime.datetime.strptime(timeContent, "%m,%d,%H:%M:%S.%f")
        return datetime.timedelta(days    = timeMicroSecond.day,    \
                                  hours   = timeMicroSecond.hour,   \
                                  minutes = timeMicroSecond.minute, \
                                  seconds = timeMicroSecond.second, \
                                  microseconds = timeMicroSecond.microsecond).total_seconds()

    def summary(self):
        if self.done_all == False:
            raise MalDataException("Experiment incomplete!")
        summaryStr = ""
        if self.read_data[TimerType.START] != SetState.UNSET or \
           self.read_data[TimerType.END] != SetState.UNSET:
            raise TimeIncompleteException("Time incompelete: [Reading data]") 
        if self.read_data[TimerType.START] != SetState.UNSET or \
           self.read_data[TimerType.END] != SetState.UNSET:
            raise TimeIncompleteException("Time incompelete: [Reading data]") 
        if self.read_data[TimerType.START] != SetState.UNSET or \
           self.read_data[TimerType.END] != SetState.UNSET:
            raise TimeIncompleteException("Time incompelete: [Reading data]") 
        if self.read_data[TimerType.START] != SetState.UNSET or \
           self.read_data[TimerType.END] != SetState.UNSET:
            raise TimeIncompleteException("Time incompelete: [Reading data]") 
        if self.read_data[TimerType.START] != SetState.UNSET or \
           self.read_data[TimerType.END] != SetState.UNSET:
            raise TimeIncompleteException("Time incompelete: [Reading data]") 
        if self.read_data[TimerType.START] != SetState.UNSET or \
           self.read_data[TimerType.END] != SetState.UNSET:
            raise TimeIncompleteException("Time incompelete: [Reading data]") 
        return str(self.read_data[TimerType.SUMMARY])          + "," + \
               str(self.build_model[TimerType.SUMMARY])        + "," + \
               str(self.build_edge_list[TimerType.SUMMARY])    + "," + \
               str(self.build_edge_listCC[TimerType.SUMMARY])  + "," + \
               str(self.compute_truss[TimerType.SUMMARY])      + "," + \
               str(self.compute_core[TimerType.SUMMARY])       + "," + \
               str(self.compute_dbscan[TimerType.SUMMARY])     + "," + \
               str(self.compute_graph_prop[TimerType.SUMMARY])

def main(argv):

    parser = argparse.ArgumentParser()
    group = parser.add_mutually_exclusive_group()
    group.add_argument("-f", "--file", action="store_true")
    group.add_argument("-d", "--directory", action="store_true")
    parser.add_argument("fname", help="file/directory name")
    args = parser.parse_args()

    if args.file:
        reader = open(args.fname)
        stats = LogStats(reader)
        print args.fname.replace(".log", "")+","+stats.summary()
    elif args.directory:
        os.chdir(args.fname)
        for file in glob.glob("*.*"):
            try:
                reader = open(file)
                stats = LogStats(reader)  
                print file.replace(".log", "")+","+stats.summary()
            except:
                e = sys.exc_info()
                print e

if __name__ == "__main__":
    main(sys.argv)
