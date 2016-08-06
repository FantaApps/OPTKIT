#!/bin/bash

#
# Copy right YMSys, 2015,2016 Zhaoming Yin
#
# @brief    This script runs experiment for stmodel 
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   08/06/16 - Parallel computing 
#   stplaydog   04/27/16 - Add upload result script 
#   stplaydog   04/24/16 - Add logger support 
#   stplaydog   04/16/16 - Add real data support 
#   stplaydog   03/05/16 - Creation
#

SCRIPT_HOME="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
OPTKIT_HOME=${SCRIPT_HOME}/../src/
DATA_HOME=${SCRIPT_HOME}/../data/

mkdir -p ${DATA_HOME}/experiments/stmodel/

rm ${SCRIPT_HOME}/process

func_run_experiment()
{
    echo START >> ${SCRIPT_HOME}/process

    local WHICH_FILE=$1
    local FILE=$2
    local XY=$3
    local TIME=$4

    echo process ${DATA_HOME}stmodel/${WHICH_FILE}/$FILE with x $XY y $XY time $TIME 

    ${OPTKIT_HOME}optkit --stmodel                               \
                         -i ${DATA_HOME}stmodel/${WHICH_FILE}/${FILE}  \
                         -o ${DATA_HOME}experiments/stmodel/${WHICH_FILE}/${WHICH_FILE}_${FILE}_${XY}_${XY}_${TIME} \
                         -c ${XY} -c ${XY} -c ${TIME} \
                         -l ${WHICH_FILE}_${XY}_${XY}_${TIME}_

    cp ${DATA_HOME}experiments/stmodel/${WHICH_FILE}/${WHICH_FILE}_${FILE}_${XY}_${XY}_${TIME}.json ${DATA_HOME}experiments/results/

    echo END >> ${SCRIPT_HOME}/process
}

#
# For real crime test data
#
for WHICH_FILE in CHI DC NY
do
    for XY in 100 200 
    do
        for TIME in 0 30
        do
            for FILE in $(ls  ${DATA_HOME}stmodel/${WHICH_FILE}/); 
            do  

                func_run_experiment ${WHICH_FILE} ${FILE} ${XY} ${TIME} & 

                while true;
                do
                    NUM_START=$((`cat ${SCRIPT_HOME}/process | grep START | wc -l`))
                    NUM_END=$((`cat ${SCRIPT_HOME}/process | grep END | wc -l`))
                    counter=$((NUM_START- NUM_END))
                    if [[ "$counter" -lt "16" ]]
                    then
                        break
                    fi
                    sleep 0.1
                done

            done
        done
    done
done
