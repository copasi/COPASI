#!/bin/bash

# the script uses COPASISE to convert an SBML model to a CPS file

COPASISE=$1
FILENAME=$2
OUTFILE=$3
LOGFILE=$4

if [ -e $COPASISE ];then
  if [ -e $FILENAME ];then
    $COPASISE --importSBML ${FILENAME} -s ${OUTFILE} 2>&1 | sed '1,4d' > ${LOGFILE}
  fi
fi
