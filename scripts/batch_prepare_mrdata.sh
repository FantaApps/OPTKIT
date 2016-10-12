#!/bin/bash

#
# Copy right YMSys, 2015,2016 Zhaoming Yin
#
# @brief    This script runs experiment for stmodel 
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   10/12/16 - Remove redundant logic 
#   stplaydog   10/08/16 - Prepare configuration data
#   stplaydog   10/07/16 - Support for CHI and NY 
#   stplaydog   10/06/16 - Creation
#
python prepare_mrdata.py ../data/stmodel/DC/BURGLARY      ../data/stmodel/DC/BUR/ 128 
python prepare_mrdata.py ../data/stmodel/DC/ROBBERY       ../data/stmodel/DC/ROB/ 128 
python prepare_mrdata.py ../data/stmodel/DC/LARCENY_THEFT ../data/stmodel/DC/TFT/ 128 

python prepare_mrdata.py ../data/stmodel/CHI/BURGLARY ../data/stmodel/CHI/BUR/ 128 
python prepare_mrdata.py ../data/stmodel/CHI/ROBBERY  ../data/stmodel/CHI/ROB/ 128 
python prepare_mrdata.py ../data/stmodel/CHI/THEFT    ../data/stmodel/CHI/TFT/ 128 

python prepare_mrdata.py ../data/stmodel/NY/BURGLARY      ../data/stmodel/NY/BUR/ 128 
python prepare_mrdata.py ../data/stmodel/NY/ROBBERY       ../data/stmodel/NY/ROB/ 128 
python prepare_mrdata.py ../data/stmodel/NY/GRAND_LARCENY ../data/stmodel/NY/TFT/ 128 
