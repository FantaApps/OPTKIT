#!/bin/bash

#
# Copy right YMSys, 2015, Zhaoming Yin
#
# @brief    This script transform dr shi's format into OPTKIT graph format. 
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   08/10/15 - Creation
#

GRAPH_FILE=$1
MAP_FILE=$2
TMP_FILE1=$2_TMP1
TMP_FILE2=$2_TMP2

cat ${GRAPH_FILE} | cut -f1 -d" " | sort -n | uniq > ${MAP_FILE}
cat ${GRAPH_FILE} | cut -f2 -d" " | sort -n | uniq >> ${MAP_FILE}
cat ${MAP_FILE} | sort -n | uniq > ${TMP_FILE1}
NUM_V=`cat ${TMP_FILE1} | wc -l`
echo 1 > ${TMP_FILE2}
for i in $(seq 2 ${NUM_V}); 
do 
    echo $i >> ${TMP_FILE2}; 
done
paste -d" " ${TMP_FILE1} ${TMP_FILE2} > ${MAP_FILE}
rm ${TMP_FILE1} ${TMP_FILE2}
