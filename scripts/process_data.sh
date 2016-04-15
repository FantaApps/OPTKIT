#!/bin/bash

#
# Copy right YMSys, 2015,2016 Zhaoming Yin
#
# @brief    This script runs experiment for stmodel 
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   04/14/16 - Creation
#

python process_data.py ../data/stmodel/Chicago_Crimes_-_2001_to_present.csv ../data/stmodel/Chicago_Crimes_-_2001_to_present_processed.csv CHI
python process_data.py ../data/stmodel/NYPD_7_Major_Felony_Incident_Map.csv ../data/stmodel/NYPD_7_Major_Felony_Incident_Map_processed.csv NYC

echo processing 2005
python process_data.py ../data/stmodel/2005-PART_I_AND_II_CRIMES2.csv ../data/stmodel/DC_tmp.csv DC
cat ../data/stmodel/DC_tmp.csv > ../data/stmodel/DC_processed.csv

echo processing 2006
python process_data.py ../data/stmodel/2006-PART_I_AND_II_CRIMES2.csv ../data/stmodel/DC_tmp.csv DC
cat ../data/stmodel/DC_tmp.csv >> ../data/stmodel/DC_processed.csv

echo processing 2007
python process_data.py ../data/stmodel/2007-PART_I_AND_II_CRIMES2.csv ../data/stmodel/DC_tmp.csv DC
cat ../data/stmodel/DC_tmp.csv >> ../data/stmodel/DC_processed.csv

echo processing 2008
python process_data.py ../data/stmodel/2008-PART_I_AND_II_CRIMES2.csv ../data/stmodel/DC_tmp.csv DC
cat ../data/stmodel/DC_tmp.csv >> ../data/stmodel/DC_processed.csv

echo processing 2009
python process_data.py ../data/stmodel/2009-PART_I_AND_II_CRIMES2.csv ../data/stmodel/DC_tmp.csv DC
cat ../data/stmodel/DC_tmp.csv >> ../data/stmodel/DC_processed.csv

echo processing 2010
python process_data.py ../data/stmodel/2010-PART_I_AND_II_CRIMES2.csv ../data/stmodel/DC_tmp.csv DC
cat ../data/stmodel/DC_tmp.csv >> ../data/stmodel/DC_processed.csv

echo processing 2011
python process_data.py ../data/stmodel/2011-PART_I_AND_II_CRIMES2.csv ../data/stmodel/DC_tmp.csv DC
cat ../data/stmodel/DC_tmp.csv >> ../data/stmodel/DC_processed.csv

echo processing 2012
python process_data.py ../data/stmodel/2012-PART_I_AND_II_CRIMES2.csv ../data/stmodel/DC_tmp.csv DC
cat ../data/stmodel/DC_tmp.csv >> ../data/stmodel/DC_processed.csv

echo processing 2013
python process_data.py ../data/stmodel/2013-PART_I_AND_II_CRIMES2.csv ../data/stmodel/DC_tmp.csv DC
cat ../data/stmodel/DC_tmp.csv >> ../data/stmodel/DC_processed.csv

echo processing 2014
python process_data.py ../data/stmodel/2014-PART_I_AND_II_CRIMES2.csv ../data/stmodel/DC_tmp.csv DC
cat ../data/stmodel/DC_tmp.csv >> ../data/stmodel/DC_processed.csv

echo processing 2015
python process_data.py ../data/stmodel/2015-PART_I_AND_II_CRIMES2.csv ../data/stmodel/DC_tmp.csv DC
cat ../data/stmodel/DC_tmp.csv >> ../data/stmodel/DC_processed.csv
