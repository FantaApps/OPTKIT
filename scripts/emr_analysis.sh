#!/bin/bash

#
# Copy right YMSys, 2015,2016 Zhaoming Yin
#
# @brief    This script runs experiment for stmodel 
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   10/12/16 - Creation 

SCRIPT_HOME="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
DATA_HOME=${SCRIPT_HOME}/../data/
S3_LOCAL=${DATA_HOME}/experiment/mapreduce/S3/
ANALYSIS_HOME=${DATA_HOME}/analysis/

for CITY in NY DC CHI
do
    for CRI in BUR ROB TFT
    do
        S3_DIR=s3://optkit11/${CITY}_${CRI}_RES_1 
        aws s3 sync ${S3_DIR} ${S3_LOCAL} | grep -v download 
        cat ${S3_LOCAL}/part* > ${S3_LOCAL}/out 
        python knox_analysis.py  ${S3_LOCAL}/out 
        mv $SCRIPT_HOME/tmp.png $ANALYSIS_HOME/${CITY}_${CRI}_emr.png
        rm ${S3_LOCAL}/part*
        rm ${S3_LOCAL}/out
    done
done
