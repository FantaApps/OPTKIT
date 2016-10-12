#!/usr/bin/env python

#
# Copy right YMSys, 2015,2016 Zhaoming Yin
#
# @brief    This script turns SNAP data into OPTKIT format 
#           
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   10/11/16 - Bug fixing 
#   stplaydog   10/10/16 - Creation
#


import sys
import os
import math

step       = 128 
current_id = -2
id         = -1
data       = []
vet        = 0
table_temp = {0:{0:0,1:0,2:0,3:0,4:0,5:0,6:0,7:0,8:0,9:0,10:0}, \
              1:{0:0,1:0,2:0,3:0,4:0,5:0,6:0,7:0,8:0,9:0,10:0}, \
              2:{0:0,1:0,2:0,3:0,4:0,5:0,6:0,7:0,8:0,9:0,10:0}, \
              3:{0:0,1:0,2:0,3:0,4:0,5:0,6:0,7:0,8:0,9:0,10:0}, \
              4:{0:0,1:0,2:0,3:0,4:0,5:0,6:0,7:0,8:0,9:0,10:0}}
table      = table_temp

def cal_dist(event1, event2):
    t1    = event1[1] 
    x1    = event1[2]
    y1    = event1[3]

    t2    = event2[1] 
    x2    = event2[2]
    y2    = event2[3]

    dist = math.sqrt(pow(x1-x2, 2)+ pow(y1,y2, 2))
    #dist = 1
    time = abs(t1 - t2)
    tpos = int(time / 14)
    dpos = int(dist / 100)
    if tpos >4:
        if dpos > 10:
            table[4][10]+=1
        else:
            table[4][dpos]+=1
    else:
        if dpos > 10:
            table[tpos][10]+=1
        else:
            table[tpos][dpos]+=1

def cal_dist_mat(cur_id, step, data):
    i = 0
    for i in range(cur_id, len(data), step):
        for item in data:
            cal_dist(data[i], item)
    for key1 in table:
        for key2 in table:
            print str(key1)+","+str(key2)+"\t" +str(table[key1][key2])
    data  = []
    table = table_temp

for line in sys.stdin:
    line = line.strip()

    if line.find("time") != -1:
        continue
    key,value = line.split("\t", 1)
    items = value.split(",")
    id    = int(key)

    if current_id == id:
        data.append([vet, int(items[0]), int(items[1]), int(items[2])])
        vet += 1
    else:
        if current_id != -2:
            cal_dist_mat(current_id, step, data)
        current_id = id

if current_id == id:
    cal_dist_mat(current_id, step, data)
