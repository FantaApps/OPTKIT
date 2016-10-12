#
# Copy right YMSys, 2015,2016 Zhaoming Yin
#
# @brief    This script turns SNAP data into OPTKIT format 
#           
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   10/08/16 - Creation
#
import sys
import numpy as np

class DataDescribe:

    def __init__(self, file, outfile, step):
        reader = open(file)
        writer = open(outfile, "w")
        lines  = reader.readlines()
        t_bin = []
        x_bin = []
        y_bin = []
        for line in lines:
            if line.find("time") == -1:
                items = line.split(",")
                time  = items[0].split("/")
                if int(time[0]) < 2005:
                    continue
                t     = (int(time[0])-1900)*365 + int(time[1])*30 + int(time[2])
                x     = int(items[1])
                y     = int(items[2])
                t_bin.append(t)
                x_bin.append(x)
                y_bin.append(y)
        t_min = np.percentile(t_bin, 1) 
        t_max = np.percentile(t_bin, 99) 
        x_min = np.percentile(x_bin, 1) 
        x_max = np.percentile(x_bin, 99) 
        y_min = np.percentile(y_bin, 1)
        y_max = np.percentile(y_bin, 99)
        writer.write("step," +step)
        writer.write("t,10," +str(int((t_max-t_min)/10))+"\n")
        writer.write("x,100,"+str(int((x_max-x_min)/100))+"\n")
        writer.write("y,100,"+str(int((y_max-y_min)/100))+"\n")
        reader.close()
        writer.close()

def main(argv):
    ds = DataDescribe(argv[1], argv[2], argv[3])

if __name__ == "__main__":
    main(sys.argv)



