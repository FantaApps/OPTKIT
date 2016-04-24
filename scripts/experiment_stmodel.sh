#!/bin/bash

#
# Copy right YMSys, 2015,2016 Zhaoming Yin
#
# @brief    This script runs experiment for stmodel 
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   04/24/16 - Add logger support 
#   stplaydog   04/16/16 - Add real data support 
#   stplaydog   03/05/16 - Creation
#

SCRIPT_HOME="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
OPTKIT_HOME=${SCRIPT_HOME}/../src/
DATA_HOME=${SCRIPT_HOME}/../data/

mkdir -p ${DATA_HOME}/experiments/stmodel/

#
# For small NY crime test data
#
for XY in 100 200 
do
    for TIME in 0 30
    do
        echo process ${DATA_HOME}truss/ny_crime.csv with x $XY y $XY time $TIME
        ${OPTKIT_HOME}optkit --stmodel                               \
                             -i ${DATA_HOME}truss/ny_crime.csv  \
                             -o ${DATA_HOME}experiments/stmodel/ny_crime_${XY}_${XY}_${TIME}.json \
                             -c ${XY} -c ${XY} -c ${TIME} \
                             -l ny_crime_${XY}_${XY}_${TIME}_
    done
done

#
# For real CHI crime test data
#
for XY in 100 200 
do
    for TIME in 0 30
    do
        echo process ${DATA_HOME}truss/CHI_processed.csv with x $XY y $XY time $TIME
        ${OPTKIT_HOME}optkit --stmodel                               \
                             -i ${DATA_HOME}stmodel/CHI_processed.csv  \
                             -o ${DATA_HOME}experiments/stmodel/CHI_${XY}_${XY}_${TIME}.json \
                             -c ${XY} -c ${XY} -c ${TIME} \
                             -l CHI_${XY}_${XY}_${TIME}_
    done
done

#
# For real DC crime test data
#
for XY in 100 200 
do
    for TIME in 0 30
    do
        echo process ${DATA_HOME}truss/DC_processed.csv with x $XY y $XY time $TIME
        ${OPTKIT_HOME}optkit --stmodel                               \
                             -i ${DATA_HOME}stmodel/DC_processed.csv  \
                             -o ${DATA_HOME}experiments/stmodel/DC_${XY}_${XY}_${TIME}.json \
                             -c ${XY} -c ${XY} -c ${TIME} \
                             -l DC_${XY}_${XY}_${TIME}_
    done
done

#
# For real NYC crime test data
#
for XY in 100 200 
do
    for TIME in 0 30
    do
        echo process ${DATA_HOME}truss/NY_processed.csv with x $XY y $XY time $TIME
        ${OPTKIT_HOME}optkit --stmodel                               \
                             -i ${DATA_HOME}stmodel/NY_processed.csv  \
                             -o ${DATA_HOME}experiments/stmodel/NY_${XY}_${XY}_${TIME}.json \
                             -c ${XY} -c ${XY} -c ${TIME} \
                             -l NY_${XY}_${XY}_${TIME}_
    done
done
