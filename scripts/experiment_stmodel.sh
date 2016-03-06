#!/bin/bash

#
# Copy right YMSys, 2015,2016 Zhaoming Yin
#
# @brief    This script runs experiment for stmodel 
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   03/05/16 - Creation
#

SCRIPT_HOME="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
OPTKIT_HOME=${SCRIPT_HOME}/../src/
DATA_HOME=${SCRIPT_HOME}/../data/

for XY in 100 200 500 1000
do
    for TIME in 0 30 60 
    do
        ${OPTKIT_HOME}optkit --stmodel                               \
                             --input ${DATA_HOME}truss/ny_crime.csv  \
                             --coord ${XY} ${XY} ${TIME}
    done
done
