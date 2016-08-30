#!/bin/bash
#
# Copy right YMSys, 2015,2016 Zhaoming Yin
#
# @brief    This script gets SNAP data 
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   08/30/16 - Creation
#

SCRIPT_HOME="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
SNAP_HOME=${SCRIPT_HOME}/../data/SNAP/

mkdir -p ${SNAP_HOME}
wget https://snap.stanford.edu/data/facebook_combined.txt.gz                         -P ${SNAP_HOME}
wget https://snap.stanford.edu/data/gplus_combined.txt.gz                            -P ${SNAP_HOME}
wget https://snap.stanford.edu/data/twitter_combined.txt.gz                          -P ${SNAP_HOME}
wget https://snap.stanford.edu/data/bigdata/communities/com-lj.ungraph.txt.gz        -P ${SNAP_HOME}
wget https://snap.stanford.edu/data/bigdata/communities/com-youtube.ungraph.txt.gz   -P ${SNAP_HOME}
wget https://snap.stanford.edu/data/bigdata/communities/com-dblp.ungraph.txt.gz      -P ${SNAP_HOME}
wget https://snap.stanford.edu/data/bigdata/communities/com-amazon.ungraph.txt.gz    -P ${SNAP_HOME}
wget https://snap.stanford.edu/data/email-Enron.txt.gz                               -P ${SNAP_HOME}
wget https://snap.stanford.edu/data/ca-HepPh.txt.gz                                  -P ${SNAP_HOME}
wget https://snap.stanford.edu/data/web-BerkStan.txt.gz                              -P ${SNAP_HOME}
wget https://snap.stanford.edu/data/amazon0601.txt.gz                                -P ${SNAP_HOME}
wget https://snap.stanford.edu/data/roadNet-CA.txt.gz                                -P ${SNAP_HOME}
wget https://snap.stanford.edu/data/as-skitter.txt.gz                                -P ${SNAP_HOME}
wget https://snap.stanford.edu/data/loc-gowalla_edges.txt.gz                         -P ${SNAP_HOME}

gunzip ${SNAP_HOME}/*.gz
