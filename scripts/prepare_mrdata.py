#
# Copy right YMSys, 2015,2016 Zhaoming Yin
#
# @brief    This script turns SNAP data into OPTKIT format 
#           
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   10/06/16 - Creation
#


import sys
import os, glob
import argparse
from os.path import basename

class MRData:

    def __init__(self, file, outDir, numTasks):
        self.reader = open(file)
        self.writer = []
        outbase     = basename(file)
        for i in range(numTasks):
            name = outDir+"/"+outbase+"_"+str(i)
            tmp  = open(name, "w")
            self.writer.append(tmp)
        self.prepare_data()

    def prepare_data(self):
        lines = self.reader.readlines()
        for line in lines:
            for i in range(len(self.writer)):
                if line.find("time") == -1:
                    self.writer[i].write(str(i)+","+line)
                else:
                    self.writer[i].write(line)

        self.reader.close()
        for i in range(len(self.writer)):
            self.writer[i].close()

def main(argv):
    mrData = MRData(argv[1], argv[2], int(argv[3]))

if __name__ == "__main__":
    main(sys.argv)
