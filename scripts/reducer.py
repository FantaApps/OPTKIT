#
# Copy right YMSys, 2015,2016 Zhaoming Yin
#
# @brief    This script turns SNAP data into OPTKIT format 
#           
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   10/07/16 - Creation
#


from operator import itemgetter
import sys
import os

os.system("aws s3 cp s3://optkit12/optkit/prepare_graph_conf .")

reader = open("./prepare_graph_conf")
lines = reader.readlines()
for line in lines:
    items = line.split(",")
    if items[0] == 'x':
        xstep = items[1]
        xbin  = items[2]
    if items[0] == 'y':
        ystep = items[1]
        ybin  = items[2]
    if items[0] == 'z':
        zstep = items[1]
        zbin  = items[2]

current_id = None
id         = None
vet        = 0

data = []

def cal_dist(event1, event2):
    t1    = event1[1].split("/")
    time1 = (int(t1[0]) - 1900) * 365 + \
            int(t1[1])*30             + \
            int(t1[2])
    x1    = int(event1[2])
    y1    = int(event1[3])

    t2    = event2[1].split("/")
    time2 = (int(t2[0]) - 1900) * 365 + \
            int(t2[1])*30             + \
            int(t2[2])
    x2    = int(event2[2])
    y2    = int(event2[3])

    dt = abs(t1-t2)
    dx = abs(x1-x2)
    dy = abs(y1-y2)

    ret = dx + (dy/ystep)*xbin + (dz/zstep)*(xbin*ybin)
    return ret

def cal_dist_mat(cur_id, step, data):
    i = 0
    for i in range(cur_id, len(data), step):
        for item in data:
            which_bin = cal_dist(data[i], item)
            print str(which_bin)+","+data[i][0]+","+item[0]

for line in sys.stdin:
    line = line.strip()

    items = line.split(",")
    id    = items[0]

    if current_id == id:
        data.append([vet, items[1], items[2], items[3]])
        vet += 1
    else:
        if current_id:
            cal_dist_mat(cur_id, step, data)
        current_id = id

if current_id == id:
    cal_dist_mat(cur_id, step, data)
