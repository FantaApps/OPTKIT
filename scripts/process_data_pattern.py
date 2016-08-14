#
# Copy right YMSys, 2015,2016 Zhaoming Yin
#
# @brief    1) This script do some sanity check of the data, and remove the
#              corrupted data;
#           2) This script separate difffernt crime types.
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   08/06/16 - Additional data bug fix 
#   stplaydog   07/31/16 - Creation
#

import sys
from datetime import datetime
from subprocess import call

reader = open(sys.argv[1])

lines = reader.readlines()

list = {}

for line in lines:
    if line .find("time") == -1:
        items = line.split(",")
        key =  items[4].strip().replace("/","").replace("  "," ").replace(" ", "_").replace("?", "")
        x = items[1].split(".")[0]
        y = items[2].split(".")[0]
        if len(str(x)) >= 6 and len(str(x)) < 9 and len(str(y)) >= 6 and len(str(y)) < 9 and int(x) >0 and int(y)>0:
            if key not in list:
                list[key] = []
            list[key].append(items[0]+","+x+","+y+","+items[3]+","+key+"\n")
    else:
        first_line = line

for key in list:
    file = sys.argv[2]+"/"+key
    writer = open(file, "w")
    writer.write(first_line)
    for line in list[key]:
        writer.write(line)
    writer.close()

    call(["sort", "-t,", "-n", "-k", "2", file, "-o", file+".sort"])

    reader = open(file+".sort")
    writer = open(file, "w")
    dup_count = 0

    pred       = []
    pred_line  = []
    pred_count = 0 
    for line in reader.readlines():
        cur = line.split(",")
        if len(pred) != 0:
            if pred[0] != cur[0] or pred[1] != cur[1] or pred[2] != cur[2]:
                if pred_count >= 2:
                    writer.write(pred_line.replace(",1", ","+str(pred_count)))
                else:
                    writer.write(pred_line)
                pred_count = 1 
            else:
                dup_count  += 1
                pred_count += 1
        pred      = cur
        pred_line = line
    writer.close()
    print file, "has ", str(dup_count), " duplications"
    call(["rm", file+".sort"])
