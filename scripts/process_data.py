#
# Copy right YMSys, 2015,2016 Zhaoming Yin
#
# @brief    This script load experiment result and put it into dynamodb 
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   04/13/16 - Creation
#

import sys
from datetime import datetime

reader = open(sys.argv[1])
writer = open(sys.argv[2], "w")
data_type = sys.argv[3]

lines = reader.readlines()


i = 0
for line in lines:
    items = line.split(",")
    if data_type == "DC" and i != 0:
        if sys.argv[1].find("2015") != -1:
            timestr = datetime.strptime(items[0].split(" ")[0], "%d/%m/%Y").strftime('%Y/%m/%d')
        else:
            timestr = datetime.strptime(items[1].split(" ")[0], "%m/%d/%Y").strftime('%Y/%m/%d') 
        writer.write(timestr+","+items[2]+","+items[3]+",1,"+items[4].strip()+"\n")
    elif data_type == "NYC":
        if len(items) > 2:
            items2 = items[2].split(" ")
            if len(items2) > 1 and i != 0:
                timestr = datetime.strptime(items[2].split(" ")[0], "%m/%d/%Y").strftime('%Y/%m/%d')
                writer.write(timestr+","+items[17]+","+items[18]+",1,"+items[12]+"\n")
    elif data_type == "CHI":
        if i != 0 and items[15] != '' and items[16] != '':
            timestr = datetime.strptime(items[2].split(" ")[0], "%m/%d/%Y").strftime('%Y/%m/%d')
            writer.write(timestr+","+items[15]+","+items[16]+",1,"+items[5]+"\n")
    i+=1
