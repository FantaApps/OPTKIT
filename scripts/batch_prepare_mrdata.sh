#!/bin/bash

#
# Copy right YMSys, 2015,2016 Zhaoming Yin
#
# @brief    This script runs experiment for stmodel 
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   10/07/16 - Support for CHI and NY 
#   stplaydog   10/06/16 - Creation
#
python prepare_mrdata.py ../data/stmodel/DC/BURGLARY      ../data/stmodel/DC/BUR/ 128 
python prepare_mrdata.py ../data/stmodel/DC/ROBBERY       ../data/stmodel/DC/ROB/ 128 
python prepare_mrdata.py ../data/stmodel/DC/LARCENY_THEFT ../data/stmodel/DC/TFT/ 128 
aws s3 sync ../data/stmodel/DC/BUR/ s3://optkit11/DC_BUR/
aws s3 sync ../data/stmodel/DC/ROB/ s3://optkit11/DC_ROB/
aws s3 sync ../data/stmodel/DC/TFT/ s3://optkit11/DC_TFT/
rm ../data/stmodel/DC/BUR/*
rm ../data/stmodel/DC/ROB/*
rm ../data/stmodel/DC/TFT/*
python process_data_conf.py ../data/stmodel/DC/BURGLARY      ../data/experiment/mapreduce/DC_BUR_CONF
python process_data_conf.py ../data/stmodel/DC/ROBBERY       ../data/experiment/mapreduce/DC_ROB_CONF
python process_data_conf.py ../data/stmodel/DC/LARCENY_THEFT ../data/experiment/mapreduce/DC_TFT_CONF

python prepare_mrdata.py ../data/stmodel/CHI/BURGLARY ../data/stmodel/CHI/BUR/ 128 
python prepare_mrdata.py ../data/stmodel/CHI/ROBBERY  ../data/stmodel/CHI/ROB/ 128 
python prepare_mrdata.py ../data/stmodel/CHI/THEFT    ../data/stmodel/CHI/TFT/ 128 
aws s3 sync ../data/stmodel/CHI/BUR/ s3://optkit11/CHI_BUR/
aws s3 sync ../data/stmodel/CHI/ROB/ s3://optkit11/CHI_ROB/
aws s3 sync ../data/stmodel/CHI/TFT/ s3://optkit11/CHI_TFT/
rm ../data/stmodel/CHI/BUR/*
rm ../data/stmodel/CHI/ROB/*
rm ../data/stmodel/CHI/TFT/*
python process_data_conf.py ../data/stmodel/CHI/BURGLARY      ../data/experiment/mapreduce/CHI_BUR_CONF
python process_data_conf.py ../data/stmodel/CHI/ROBBERY       ../data/experiment/mapreduce/CHI_ROB_CONF
python process_data_conf.py ../data/stmodel/CHI/THEFT         ../data/experiment/mapreduce/CHI_TFT_CONF

python prepare_mrdata.py ../data/stmodel/NY/BURGLARY      ../data/stmodel/NY/BUR/ 128 
python prepare_mrdata.py ../data/stmodel/NY/ROBBERY       ../data/stmodel/NY/ROB/ 128 
python prepare_mrdata.py ../data/stmodel/NY/GRAND_LARCENY ../data/stmodel/NY/TFT/ 128 
aws s3 sync ../data/stmodel/NY/BUR/ s3://optkit11/NY_BUR/
aws s3 sync ../data/stmodel/NY/ROB/ s3://optkit11/NY_ROB/
aws s3 sync ../data/stmodel/NY/TFT/ s3://optkit11/NY_TFT/
rm ../data/stmodel/NY/BUR/*
rm ../data/stmodel/NY/ROB/*
rm ../data/stmodel/NY/TFT/*
python process_data_conf.py ../data/stmodel/NY/BURGLARY      ../data/experiment/mapreduce/NY_BUR_CONF
python process_data_conf.py ../data/stmodel/NY/ROBBERY       ../data/experiment/mapreduce/NY_ROB_CONF
python process_data_conf.py ../data/stmodel/NY/GRAND_LARCENY ../data/experiment/mapreduce/NY_TFT_CONF

