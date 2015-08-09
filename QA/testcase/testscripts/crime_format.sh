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

RAW_DIR=${HOME}/../../../data/CC/dr_shi_format/
EDGE_DIR=${RAW_DIR}edges/
VET_DIR=${RAW_DIR}vertices/
GRAPH_DIR=${HOME}/../../../data/CC/graphs/

for EDGE_FILE in $( ls ${EDGE_DIR} );
do
    VET_FILE=${VET_DIR}`echo ${EDGE_FILE} | sed 's/crimepair_//g'`
    GRAPH_FILE=${GRAPH_DIR}${EDGE_FILE}

    cat ${EDGE_DIR}${EDGE_FILE} | \ 
        sed -e 's/(//g' | \
        sed -e $'s/)/\\\n/g' | \
        sed -E $'s/\t//g' | \
        sed 's/,/ /g' > ${GRAPH_FILE}

    NUM_V=`cat ${VET_FILE} | sed -e $'s/0\n//g' | wc -l`
    NUM_E=`cat ${GRAPH_FILE} | wc -l`
    NUM_C='1'

    echo -e "${NUM_V} ${NUM_E} ${NUM_C}\n$(cat ${GRAPH_FILE})" > ${GRAPH_FILE} 
done
