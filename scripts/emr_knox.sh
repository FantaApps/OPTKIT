#!/bin/bash

#
# Copy right YMSys, 2015,2016 Zhaoming Yin
#
# @brief    This script runs experiment for stmodel 
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   10/10/16 - Fixed some bugs to make MR run 
#   stplaydog   10/08/16 - Run EMR experiments 

SCRIPT_HOME="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
DATA_HOME=${SCRIPT_HOME}/../data/
CONFIG=$1

# upload according files to s3
aws s3 cp ${SCRIPT_HOME}/mapper.py  s3://optkit11/
aws s3 cp ${SCRIPT_HOME}/reducer.py s3://optkit11/
aws s3 cp ${DATA_HOME}/experiment/mapreduce/${CONFIG}_CONF s3://optkit11/EMR_CONF 

# create a instance is there is none
CLUSTER_ID=`aws emr list-clusters --active | grep Id | grep -o j-.* | sed -e s/\",//`

# download results
#mkdir -p ${DATA_HOME}experiment/results/EMR/${CONFIG}/
#aws s3 sync s3://optkit11/results/${CONFIG} ${DATA_HOME}experiment/results/EMR/${CONFIG}/
#aws s3 mv s3://optkit11/results/${CONFIG} s3://optkit11/results/${CONFIG}_ANOHTER
#aws s3 rm s3://optkit11/results/${CONFIG} --recursive

# run jobs
cat emr_knox_temp.json | sed -e s/CONFIG/${CONFIG}/g | sed -e s/CONFIG/${CONFIG}/g >  emr_knox.json
aws emr add-steps --cluster-id ${CLUSTER_ID} --steps file://./emr_knox.json 

