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

S3_DIR=$1
SEQ_FILE=$2

aws s3 sync ${S3_DIR} ${S3_LOCAL} 
cat ${S3_LOCAL}/part* > ${S3_LOCAL}/out 

python knox_analysis.py  ${S3_LOCAL}/out ${SEQ_FILE} 

rm ${S3_LOCAL}/part*
rm ${S3_LOCAL}/out
