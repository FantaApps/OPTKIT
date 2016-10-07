#!/bin/bash

#
# Copy right YMSys, 2015,2016 Zhaoming Yin
#
# @brief    This script runs experiment for stmodel 
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   10/06/16 - Creation
#
python prepare_mrdata.py ../data/stmodel/DC/BURGLARY      ../data/stmodel/DC/BUR/ 128 
python prepare_mrdata.py ../data/stmodel/DC/ROBBERY       ../data/stmodel/DC/ROB/ 128 
python prepare_mrdata.py ../data/stmodel/DC/LARCENY_THEFT ../data/stmodel/DC/TFT/ 128 
aws s3 sync ../data/stmodel/DC/BUR/ s3://optkit11/DC_BUR/
aws s3 sync ../data/stmodel/DC/ROB/ s3://optkit11/DC_ROB/
aws s3 sync ../data/stmodel/DC/TFT/ s3://optkit11/DC_TFT/

python prepare_mrdata.py ../data/stmodel/CHI/BURGLARY ../data/stmodel/CHI/BUR/ 128 
python prepare_mrdata.py ../data/stmodel/CHI/ROBBERY  ../data/stmodel/CHI/ROB/ 128 
python prepare_mrdata.py ../data/stmodel/CHI/THEFT    ../data/stmodel/CHI/TFT/ 128 
aws s3 sync ../data/stmodel/CHI/BUR/ s3://optkit11/CHI_BUR/
aws s3 sync ../data/stmodel/CHI/ROB/ s3://optkit11/CHI_ROB/
aws s3 sync ../data/stmodel/CHI/TFT/ s3://optkit11/CHI_TFT/

python prepare_mrdata.py ../data/stmodel/NY/BURGLARY      ../data/stmodel/NY/BUR/ 128 
python prepare_mrdata.py ../data/stmodel/NY/ROBBERY       ../data/stmodel/NY/ROB/ 128 
python prepare_mrdata.py ../data/stmodel/NY/GRAND_LARCENY ../data/stmodel/NY/TFT/ 128 
aws s3 sync ../data/stmodel/NY/BUR/ s3://optkit11/NY_BUR/
aws s3 sync ../data/stmodel/NY/ROB/ s3://optkit11/NY_ROB/
aws s3 sync ../data/stmodel/NY/TFT/ s3://optkit11/NY_TFT/
