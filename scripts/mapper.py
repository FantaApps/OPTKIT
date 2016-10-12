#!/usr/bin/env python

import sys
import os

# input comes from STDIN (standard input)
for line in sys.stdin:
    # remove leading and trailing whitespace
    line = line.strip()
    items = line.split(",")
    # split the line into words
    key = items[0]
    if key == 'time':
        continue
    t1    = items[1].split("/")
    time1 = (int(t1[0]) - 1900) * 365 + \
            int(t1[1])*30             + \
            int(t1[2])
    value = str(time1)+","+items[2]+","+items[3]
    print '%s\t%s' % (key, value)
