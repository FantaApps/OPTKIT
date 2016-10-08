#!/bin/bash

#
# Copy right YMSys, 2015,2016 Zhaoming Yin
#
# @brief    This script runs experiment for stmodel 
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   10/08/16 - Run EMR experiments 

SCRIPT_HOME="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
DATA_HOME=${SCRIPT_HOME}/../data/
CONFIG=$1
SEQ=$2

# upload according files to s3
aws s3 cp ${SCRIPT_HOME}/mapper.py  s3://optkit11/
aws s3 cp ${SCRIPT_HOME}/reducer.py s3://optkit11/
aws s3 cp ${DATA_HOME}/experiment/mapreduce/${CONFIG}_CONF s3://optkit11/ 

# create a instance is there is none
CLUSTER_ID=`aws emr list-clusters --active | grep Id | grep -o j-.* | sed -e s/\",//`

# run jobs
aws emr add-steps \
--cluster-id ${CLUSTER_ID} \
--steps Type=STREAMING,\
Name='Streaming Program',\
ActionOnFailure=CONTINUE,\
Args=[-files,s3://optkit11/mapper.py,s3://optkit11/reducer.py,\
-mapper,mapper.py,\
-reducer,reducer.py,\
-input,s3://optkit11/${CONFIG},\
-output,s3://optkit11/results/${SEQ}]

# download results
mkdir -p ${DATA_HOME}experiment/results/EMR/${CONFIG}/
asw s3 sync s3://optkit11/results/${SEQ} ${DATA_HOME}experiment/results/EMR/${CONFIG}/ 
