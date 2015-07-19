#!/bin/sh
#
# $Header: oggcore/OpenSys/src/app/ggoptkit/QA/testcase/testscripts/MC.sh zyin_ggoptkit/3 2015/07/18 18:43:02 zyin Exp $
#
# MC.sh
#
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#
#    NAME
#      MC.sh - <one-line expansion of the name>
#
#    DESCRIPTION
#      <short description of component this file declares/defines>
#
#    NOTES
#      <other useful comments, qualifications, etc.>
#
#    MODIFIED   (MM/DD/YY)
#    zyin        07/16/15 - change logger to a folder
#    zyin        07/07/15 - Creation
#

export HOME=/ade/zyin_ggoptkit/oggcore/OpenSys/src/app/ggoptkit/
export BIN=${HOME}src/optkit
export PROBLEM=--mc
export INPUT_FILE="--input_file ${HOME}data/MC/janc.gr"
export LOGGER_FILE="--logger ${HOME}QA/testcase/tgt_logs/"

${BIN} ${PROBLEM} ${INPUT_FILE} ${LOGGER_FILE}
