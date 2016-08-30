#
# Copy right YMSys, 2015,2016 Zhaoming Yin
#
# @brief    This script turns SNAP data into OPTKIT format 
#           
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   08/30/16 - Creation
#


import sys
import os, glob
import argparse
from os.path import basename

class SNAPGraph:

    def __init__(self, file):
        reader         = open(file)
        lines          = reader.readlines()
        v_map          = {}
        self.v_idx     = 0
        self.edge_list = []
        line_num       = 0

        for line in lines:
            print line
            if line.find("#") == -1:
                vets = line.strip().replace("\t", " ").split(" ")
                i    = 0 
                for v in vets:
                    if int(v) not in v_map:
                        v_map[int(v)] = self.v_idx
                        self.v_idx   += 1
                    if i != 0:
                        v_from = v_map[int(vets[i-1])]
                        v_to   = v_map[int(v)]
                        comb   = str(v_from)+","+str(v_to) if v_from < v_to else str(v_to)+","+str(v_from) 
                        self.edge_list.append(comb)
                    i += 1
        self.edge_list = list(set(self.edge_list))
             

    # now we treat all graphs as undirected
    def output(self, ofile):
        writer = open(ofile, "w")
        writer.write(str(self.v_idx)+" "+ str(len(self.edge_list))+" "+ '0\n')
        for e in self.edge_list:
            edge = e.split(",")
            writer.write(edge[0] + " "+ edge[1]+" 1\n")
            writer.write(edge[1] + " "+ edge[0]+" 1\n")
        writer.close()


def main(argv):

    parser = argparse.ArgumentParser()
    group = parser.add_mutually_exclusive_group()
    group.add_argument("-f", "--file", action="store_true")
    group.add_argument("-d", "--directory", action="store_true")
    parser.add_argument("fname", help="file/directory name")
    args = parser.parse_args()

    if args.file:
        graph = SNAPGraph(args.fname)
        ofile = args.fname.replace(".txt", ".gr")
        graph.output(ofile)
    elif args.directory:
        os.chdir(args.fname)
        for file in glob.glob("*.txt"):
            try:
                print "process", file
                graph = SNAPGraph(file)
                ofile = file.replace(".txt", ".gr")
                graph.output(ofile)
            except:
                print "Data Corruption in " + file

if __name__ == "__main__":
    main(sys.argv)
