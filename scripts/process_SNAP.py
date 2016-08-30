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
import argparse
from os.path import basename

class SNAPGraph:

    def __init__(self, file):
        reader         = open(file)
        lines          = reader.readlines()
        v_map          = {}
        self.v_idx     = 0
        self.edge_list = []

        for line in lines:
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
                        comb   = [v_from, v_to] if v_from < v_to else [v_to, v_from] 
                        if comb not in self.edge_list:
                            edge_list.add(comb)

    # now we treat all graphs as undirected
    def output(self, ofile):
        writer = open(ofile, "w")
        writer.write(str(self.v_idx)+" "+ str(len(self.edge_list))+" "+ '0')
        for e in self.edge_list:
            writer.write(str(e[0]) + " " + str(e[1]) + "\n")
            writer.write(str(e[1]) + " " + str(e[0]) + "\n")
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
                graph = SNAPGraph(args.fname)
                ofile = args.fname.replace(".txt", ".gr")
            except:
                print "Data Corruption in " + file

if __name__ == "__main__":
    main(sys.argv)
                                                                                                                                                                                                                                                             73,1          Bot

