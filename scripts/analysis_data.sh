#!/bin/bash

#
# Copy right YMSys, 2015,2016 Zhaoming Yin
#
# @brief    This script runs data analysis to generate latex tables and 
#           R figures.
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   08/20/16 - Add json data analytics 
#   stplaydog   08/13/16 - Creation 
#

SCRIPT_HOME="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
OPTKIT_HOME=${SCRIPT_HOME}/../src/
DATA_HOME=${SCRIPT_HOME}/../data/
ANALYSIS_HOME=${DATA_HOME}/analysis/
RESULT_HOME=${DATA_HOME}/experiments/results/

FILE_NAME=${ANALYSIS_HOME}result_`date +"%T"`
echo process log data
python log_analysis.py  -d ${RESULT_HOME} > ${ANALYSIS_HOME}tmp
echo process json data
python data_analysis.py -d ${RESULT_HOME} > ${ANALYSIS_HOME}tmp1

for COLUMN_ID in 2 3 4 5 6 7 
do
    sort -t',' -n -k ${COLUMN_ID} ${ANALYSIS_HOME}tmp   > ${FILE_NAME}_${COLUMN_ID}_log
done
rm ${ANALYSIS_HOME}tmp

for COLUMN_ID in 2 3 4 5 6 7 8 
do
    sort -t',' -n -k ${COLUMN_ID} ${ANALYSIS_HOME}tmp1   > ${FILE_NAME}_${COLUMN_ID}_json
done
rm ${ANALYSIS_HOME}tmp*
