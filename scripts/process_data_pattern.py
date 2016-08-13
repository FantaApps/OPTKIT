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

reader = open(sys.argv[1])

lines = reader.readlines()

list = {}

for line in lines:
    if line .find("time") == -1:
        items = line.split(",")
        key =  items[4].strip().replace("/","").replace("  "," ").replace(" ", "_").replace("?", "")
        x = items[1].split(".")[0]
        y = items[2].split(".")[0]
        if len(str(x)) >= 6 and len(str(x)) < 9 and len(str(y)) >= 6 and len(str(y)) < 9:
            if key not in list:
                list[key] = []
            list[key].append(items[0]+","+x+","+y+","+items[3]+","+key+"\n")
    else:
        first_line = line

for key in list:
    writer = open(sys.argv[2]+"/"+key, "w")
    writer.write(first_line)
    for line in list[key]:
        writer.write(line)
    writer.close()
