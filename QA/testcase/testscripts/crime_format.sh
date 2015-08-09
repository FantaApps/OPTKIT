#!/bin/bash

#
# Copy right YMSys, 2015, Zhaoming Yin
#
# @brief    This script transform dr shi's format into OPTKIT graph format. 
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   08/08/15 - Creation
#

HOME=$( cd "$( dirname "${BASH_EXCHANGE[0]}" )" && cd .. && pwd )

RAW_DIR=${HOME}/../../data/CC/dr_shi_format/
EDGE_DIR=${RAW_DIR}edges/
VET_DIR=${RAW_DIR}vertices/
GRAPH_DIR=${HOME}/../../data/CC/graphs/

for EDGE_FILE in $( ls ${EDGE_DIR} );
do
    # Declare some files.
    VET_FILE=${VET_DIR}`echo ${EDGE_FILE} | sed 's/crimepair_//g'`
    GRAPH_FILE=${GRAPH_DIR}${EDGE_FILE}
    TMP_FILE=${GRAPH_DIR}tmp
    PASTE_FILE=${GRAPH_DIR}paste
   
    # Process the format
    echo processing file ${EDGE_DIR}${EDGE_FILE}
    cat ${EDGE_DIR}${EDGE_FILE} | sed -e 's/(//g' | \
        sed -e $'s/)/\\\n/g' | \
        sed -E $'s/\t//g' | \
        sed 's/,/ /g' > ${GRAPH_FILE}

    # Compute the graph meta info.
    NUM_V=`cat ${VET_FILE} | tr '0\n' ' ' | wc -w | xargs`
    NUM_E=`cat ${GRAPH_FILE} | wc -l | xargs`
    NUM_C='1'
    
    # Paste color
    for i in $(seq 1 ${NUM_E}); do echo 1; done > ${TMP_FILE}
    paste -d" " ${GRAPH_FILE} ${TMP_FILE} > ${PASTE_FILE} 
    mv ${PASTE_FILE} ${GRAPH_FILE} 
    rm ${TMP_FILE}
    
    # Insert meta info in front.
    echo -e "${NUM_V} ${NUM_E} ${NUM_C}\n$(cat ${GRAPH_FILE})" > ${GRAPH_FILE} 
done
